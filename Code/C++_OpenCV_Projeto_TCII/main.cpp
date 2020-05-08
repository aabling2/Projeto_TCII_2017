//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Term Paper - Electrical Engineering - UNISC
//Start date: 27/09/2016
//By: Augusto Abling
//Description: This program was designed for a computer vision system that inspects some parts (Dolce Gusto capsules specifically)
//  on the first camera, identifies some features to compare with a standard database, and if they are okay or not, keep tracking
//  the parts on the second camera.
//  Features to compare: Size and color.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///LIBRARIES
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <dirent.h>
#include <sstream>
#include <windows.h>

///DEFINITIONS
#define pi 3.14159
#define screen1 "Imagem Webcam 1"
#define screen2 "Imagem Processada 1"
#define screen3 "Imagem Webcam 2"
#define screen4 "Imagem Processada 2"
#define screen5 "Limiar RGB"
#define num_max_parts   10              //Maximum number of parts to register in image
#define num_max_default   5             //Maximum number of standard parts
#define num_inspections 1               //Times to do the inspections
#define size_part 53                    //Real diameter of the part(millimeters)
#define mask_angle 73.5                 //Angle to make the lines in camera2 to align the conveyor
#define offset_line 26                  //Offset from the side of the image (pixels)
#define width_conveyor 297              //Width of the conveyor to use on reading at second camera (millimeters)
#define length_conveyor 510             //Length of the conveyor to use on reading at second camera (millimeters)
#define dist_ref 420                    //Distance between camera2 and end of length conveyor (millimeters)
#define dist_h 360                      //Height distance between camera2 and conveyor (millimeters)
#define f_correct 1.0                   //Correction factor to apply at the distance between camera2 and object
#define h_correct 35                    //Height of the object to correct distance

using namespace cv;
using namespace std;

///FUNCTIONS
void LoadDataTxt();
void SaveDataTxt();
void SnapDefault(Mat imgPart, int num_obj);
void LoadDefault();
void CleanDefault();
Scalar ImgAvgColor(Mat imgPart);
Scalar CheckColors(Mat imgPart);

///VARIABLES
int key;
int thresh1, thresh2, thresh3;
int Bmin, Gmin, Rmin, Bmax, Gmax, Rmax;
Mat img1, img1Gray, img1Proc, imgLoad, img1Capture, img1Backg, img1Foreg,
    img2, img2Gray, img2Proc, img2Mask, img2Capture, img2Backg,  img2Foreg, img2Segm;
double cont_time_fps, avg_fps;
int cont_frames, press_times;
char screen_fps[10], screen_obj[15],label_part_def[num_max_default][15];
string label_part;
int cont_parts1, cont_parts2, cont_good_parts, cont_bad_parts, cont_nodef_parts, acumul_parts2;
int num_part[num_max_parts], num_part2[num_max_parts];
int init_part, limit_part, init_part2, limit_part2;
Scalar color_def[num_max_default], color_part, color_result, color_size;
float ratio_part;   //Ratio between image and part radius
bool first_check = 0;
bool key_pause = false;

///CLASS
class Parts{
    public:
        int num_inspec[num_max_parts];
        Scalar color[num_max_parts];
        Point last_center[num_max_parts][50];
        Point last_center2[num_max_parts][50];
        float Size[num_max_parts];
        string screen_defect[num_max_parts];
        string screen_label[num_max_parts];
        Point coord2[num_max_parts];
};

///MAIN PROGRAM
int main(){

  while(key != 27){

    system("cls");
    cout <<"Image processing started."<< endl <<endl;

    //Start class Parts
    Parts parts;

    mkdir("photo_parts");
    press_times = 0;
    ratio_part = 0;
    cont_parts1 = 0;
    cont_parts2 = 0;
    cont_nodef_parts = 0;
    cont_bad_parts = 0;
    cont_good_parts = 0;
    acumul_parts2 = 0;

    //Fill the vectors
    for(int k=0; k<num_max_parts; k++){
        num_part[k] = k;
        num_part2[k] = k;
        parts.num_inspec[k] = NULL;
    }

    ///Capture from web camera
    //VideoCapture cap1(0); //Camera 1
    //VideoCapture cap2(2); //Camera 2
    VideoCapture cap1("Cam1_video.avi"); //Capture image from video recorded
    VideoCapture cap2("Cam2_video.avi"); //Capture image from video recorded

    if(!cap1.isOpened() || !cap2.isOpened()){
        cout<<"Camera is not connected!" <<endl;
        break;
    }

    cap1 >> img1;
    cout<<"Image Size: " <<img1.cols <<"x" <<img1.rows <<endl;

    //Create windows
    namedWindow(screen2, WINDOW_AUTOSIZE);
    namedWindow(screen4, WINDOW_AUTOSIZE);
    namedWindow(screen1, WINDOW_AUTOSIZE);
    namedWindow(screen3, WINDOW_AUTOSIZE);
    //namedWindow(screen5, WINDOW_FREERATIO);

    //Load images of part default and get the average color
    LoadDefault();

    //Read data and create TrackBar to RGB features
    LoadDataTxt();

    //Variables of limit lines for camera 2
    Point   ang_line_tl, ang_line_bl, ang_line_tr, ang_line_br,
            limit_line_tl, limit_line_tr, limit_line_bl, limit_line_br;
    ang_line_tl.x = (img1.rows/tan(mask_angle*pi/180)) + offset_line;               ang_line_tl.y = 0;
    ang_line_bl.x= offset_line;                                                     ang_line_bl.y = img1.rows;
    ang_line_tr.x = img1.cols - (img1.rows/tan(mask_angle*pi/180)) - offset_line;   ang_line_tr.y = 0;
    ang_line_br.x = img1.cols - offset_line;                                        ang_line_br.y = img1.rows;
    limit_line_tl.x = (img1.rows/tan(mask_angle*pi/180)) + offset_line;             limit_line_tl.y = 20;
    limit_line_tr.x = img1.cols - (img1.rows/tan(mask_angle*pi/180)) - offset_line; limit_line_tr.y = 20;
    limit_line_bl.x = offset_line;                                                  limit_line_bl.y = img1.rows;
    limit_line_br.x = img1.cols - offset_line;                                      limit_line_br.y = img1.rows;

    ///Create and apply mask (limit angle) at image 2
    img2Mask = Mat::zeros(img1.size(), CV_8U);
    for(int i=limit_line_tl.y; i<limit_line_bl.y; i++){
        float x1, x2;
        x1 = (img2Mask.rows - i)/tan(mask_angle*pi/180);
        x2 = img2Mask.cols - x1;
        line(img2Mask, Point2f(x1+offset_line, i), Point2f(x2-offset_line, i), Scalar(255,0,0), 1, 8, 0);
    }

    for (;;){

        //- CAMERA 1 -////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Get time to FPS
        double time_fps = (double)getTickCount();

        ///IMAGE ACQUISITION
        if(key_pause == false){
            //Image from camera to Mat
            cap1 >> img1;
            img1.copyTo(img1Capture);
        }
        else{
            img1Capture.copyTo(img1);
        }

        //Frame empty at the end of the video
        if (img1.empty()){
            SaveDataTxt();
            cap1.release();
            cap2.release();
            destroyAllWindows();
            cout <<endl <<"End of image processing."<< endl;
            return 0;
        }
/*        //Resize image for better frame
        resize(img1, img1, Size(640,480), 0, 0, INTER_CUBIC);
*/
        //Get first image to the background image
        if(first_check!=1){
            //cap1 >> img1Backg;
            img1Backg = imread("photo_parts/Img1Background.jpg");
        }

        ///PRE-PROCESSING
        //Do a simple background subtraction
        absdiff(img1, img1Backg, img1Foreg);

        ///Convert image type
//        cvtColor(img1, img1Gray, COLOR_RGB2GRAY, 1);

        ///Low-pass filters
        //blur(img1Gray, img1Proc, Size(7,7));
        //medianBlur(img1Gray, img1Proc, 9);
        GaussianBlur(img1Foreg, img1Proc, Size(7,7), 0, 0, BORDER_DEFAULT);
        //bilateralFilter(img1Gray, img1Proc, 9, 20, 20);

        ///SEGMENTATION
        //THRESHOLD
        //Apply threshold
        Mat img1Segm;
//        threshold(img1Proc, img1Segm, thresh1, 255, CV_THRESH_BINARY_INV);

        //THRESHOLD BY COLOR
        inRange(img1Proc, Scalar(0, 45, 0), Scalar(255, 255, 255), img1Segm);
        inRange(img1Proc, Scalar(54, 0, 0), Scalar(177, 26, 86), img1Proc);
        //inRange(img1Proc, Scalar(Bmin, Gmin, Rmin), Scalar(Bmax, Gmax, Rmax), img1Proc);

        //imshow(screen2, img1Proc);

        add(img1Segm, img1Proc, img1Segm);

        //DILATION AND EROSION
        //Apply opening that is erosion followed by dilation to to remove noise
        morphologyEx(img1Segm, img1Segm, MORPH_OPEN, Mat(), Point(-1,-1), 1, BORDER_DEFAULT);
        //Apply closing that is dilation followed by erosion to fill the holes
        morphologyEx(img1Segm, img1Segm, MORPH_CLOSE, Mat(), Point(-1,-1), 7, BORDER_DEFAULT);
        //dilate(img1Segm, img1Segm, Mat(), Point(-1,-1), 2, BORDER_DEFAULT);
        erode(img1Segm, img1Segm, Mat(), Point(-1,-1), 3, BORDER_DEFAULT);

        imshow(screen2, img1Segm);

        ///RECOGNITION AND INTERPRETATION
        //POLYGONAL APPROXIMATION
        vector<Rect> boundRect( num_max_parts );
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        vector<vector<Point> > contours_poly( num_max_parts );
        vector<Point2f> center( num_max_parts );
        vector<float> radius( num_max_parts );

        //Find contours
        findContours(img1Segm, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        if(first_check != 0){

            for(int i=0; i<contours.size(); i++ ){

                //Approximate contours to polygons + get bounding rects + center
                approxPolyDP( Mat(contours[i]), contours_poly[num_part[i]], 3, true );
                boundRect[num_part[i]] = boundingRect( Mat(contours_poly[num_part[i]]) );
                minEnclosingCircle( (Mat)contours_poly[num_part[i]], center[num_part[i]], radius[num_part[i]] );


               //Get the right number of the parts
                if(contours.size()<limit_part){
                    //Save which is the first position
                    init_part = num_part[0];
                    //Move positions and your data
                    for(int k=0; k<(num_max_parts-1); k++){
                        num_part[k] = num_part[k+1];
                        parts.color[num_part[k]] = parts.color[num_part[k+1]];
                        parts.Size[num_part[k]] = parts.Size[num_part[k+1]];
                        parts.num_inspec[num_part[k]] = parts.num_inspec[num_part[k+1]];
                        parts.screen_defect[num_part[k]] = parts.screen_defect[num_part[k+1]];
                        parts.screen_label[num_part[k]] = parts.screen_label[num_part[k+1]];
                        for(int h=19; h>=0; h--){
                            parts.last_center[num_part[k]][h] = parts.last_center[num_part[k+1]][h];
                        }
                    }
                    //Define the first position to the last and clean data of vectors
                    num_part[num_max_parts-1] = init_part;
                    parts.color[num_part[contours.size()]] = NULL;
                    parts.Size[num_part[contours.size()]] = NULL;
                    parts.num_inspec[num_part[contours.size()]] = NULL;
                    parts.screen_defect[num_part[contours.size()]] = '\0';
                    parts.screen_label[num_part[contours.size()]] = '\0';
                    for(int h=19; h>=0; h--){
                        parts.last_center[num_part[contours.size()]][h] = Point(0,0);
                    }
                }
                limit_part = contours.size();

                //Inspection of the parts
                if(boundRect[num_part[i]].tl().y > 10 && boundRect[num_part[i]].br().y < (img1.rows - 10)
                   && parts.num_inspec[num_part[i]] < num_inspections){

                    //Verify the scale if is ok
                    if((radius[num_part[i]]<(size_part/ratio_part)-3) ||
                       (radius[num_part[i]]>(size_part/ratio_part)+3)){
                        color_size = Scalar(0,0,255);
                    }
                    else{
                        color_size = Scalar(0,255,0);
                    }
                    //Verify the color
                    //Pick a rect from the part
                    Mat imgRect(img1, Rect(boundRect[num_part[i]].tl(), boundRect[num_part[i]].br()));
                    //Get the average color of the part
                    color_part = ImgAvgColor(imgRect);
                    //Compare color of the part with the default
                    color_result = CheckColors(imgRect);

                    //Compare results
                    if(color_size == Scalar(0,255,0) && color_result == Scalar(0,255,0)){
                        parts.screen_defect[num_part[i]] = "OK";
                        parts.screen_label[num_part[i]] = label_part;
                        parts.Size[num_part[i]] = radius[num_part[i]]*ratio_part;
                        parts.color[num_part[i]] = Scalar(0,255,0);
                        cont_good_parts++;
                        cont_parts1++;
                    }
                    else if(color_size == Scalar(0,0,255) && color_result == Scalar(0,255,0)) {
                        parts.screen_defect[num_part[i]] = "Size";
                        parts.screen_label[num_part[i]] = "?";
                        parts.color[num_part[i]] = Scalar(0,0,255);
                        cont_bad_parts++;
                        cont_parts1++;
                    }
                    else if(color_size == Scalar(0,255,0) && color_result == Scalar(0,0,255)) {
                        parts.screen_defect[num_part[i]] = "Color";
                        parts.screen_label[num_part[i]] = "?";
                        parts.color[num_part[i]] = Scalar(0,0,255);
                        cont_bad_parts++;
                        cont_parts1++;
                    }
                    else if(color_size == Scalar(0,0,255) && color_result == Scalar(0,0,255)) {
                        parts.screen_defect[num_part[i]] = "Size/Color";
                        parts.screen_label[num_part[i]] = "?";
                        parts.color[num_part[i]] = Scalar(0,0,255);
                        cont_bad_parts++;
                        cont_parts1++;
                    }
                    else if(color_size == Scalar(0,0,255) && color_result == Scalar(0,0,0)) {
                        parts.screen_defect[num_part[i]] = "Size/No ref.";
                        parts.screen_label[num_part[i]] = "?";
                        parts.color[num_part[i]] = Scalar(0,0,255);
                        cont_bad_parts++;
                        cont_parts1++;
                    }
                    else if(color_size == Scalar(0,255,0) && color_result == Scalar(0,0,0)) {
                        parts.screen_defect[num_part[i]] = "No ref.";
                        parts.screen_label[num_part[i]] = "?";
                        parts.color[num_part[i]] = Scalar(0,0,0);
                        cont_nodef_parts++;
                        cont_parts1++;
                    }
                    parts.num_inspec[num_part[i]]++;
                    //Save scale of the part
                    parts.Size[num_part[i]] = radius[num_part[i]]*ratio_part;
                }
                else if(parts.num_inspec[num_part[i]] == 0 && boundRect[num_part[i]].br().y > (img1.rows - 10)){
                    parts.screen_defect[num_part[i]] = "No def.";
                    parts.screen_label[num_part[i]] = "?";
                    parts.color[num_part[i]] = Scalar(0,0,0);
                    cont_nodef_parts++;
                    parts.num_inspec[num_part[i]]++;
                    cont_parts1++;
                }
                else if(parts.num_inspec[num_part[i]] == num_inspections){
                    parts.num_inspec[num_part[i]]++;
                }

                //Take picture from the part
                if(key == ' ' && boundRect[num_part[i]].tl().y > 10 && center[num_part[i]].y < (img1.rows-10)){
                    Mat imgRect(img1, Rect(boundRect[num_part[i]].tl(), boundRect[num_part[i]].br()));
                    SnapDefault(imgRect, contours.size());
                }

                //Save last center of objects to get trajectory
                if(boundRect[num_part[i]].tl().y > 10){
                    for(int j=19; j>=0; j--){
                        //Draw trajectory
                        //drawMarker(img1, parts.last_center[num_part[i]][j], parts.color[num_part[i]], MARKER_CROSS, 5, 1, 8);
                        if(j!=0)
                            parts.last_center[num_part[i]][j] = parts.last_center[num_part[i]][j-1];
                        else
                            parts.last_center[num_part[i]][j] = center[num_part[i]];
                    }
                }

                //Define boundRect with the size of the inspection
                if(parts.Size[num_part[i]] != NULL && parts.Size[num_part[i]] > (size_part - 20)){
                    boundRect[num_part[i]].y = center[num_part[i]].y - (parts.Size[num_part[i]]/ratio_part);
                    boundRect[num_part[i]].x = center[num_part[i]].x - (parts.Size[num_part[i]]/ratio_part);
                    boundRect[num_part[i]].height = 2 * parts.Size[num_part[i]]/ratio_part;
                    boundRect[num_part[i]].width = 2 * parts.Size[num_part[i]]/ratio_part;
                }

                ///PARTS RESULTS
                if(boundRect[num_part[i]].tl().y > 10 && center[num_part[i]].y < (img1.rows-10)){
                    //Draw rectangles and center points
                    rectangle(img1, boundRect[num_part[i]].tl(), boundRect[num_part[i]].br(), parts.color[num_part[i]], 1, 8, 0 );
                    drawMarker(img1, center[num_part[i]], parts.color[num_part[i]], MARKER_CROSS, radius[num_part[i]]/2, 1, 8);
                    //Draw object number
                    if(cont_parts1>0){
                        sprintf(screen_obj, "%d", num_part[i]+1);
                        putText(img1, screen_obj, center[num_part[i]], FONT_HERSHEY_PLAIN, 2, parts.color[num_part[i]], 2, 8);
                    }
                    //Draw Result
                    putText(img1, parts.screen_defect[num_part[i]], Point(boundRect[num_part[i]].tl().x, boundRect[num_part[i]].br().y)
                            , FONT_HERSHEY_PLAIN, 1, parts.color[num_part[i]], 1, 8);
                    putText(img1, parts.screen_label[num_part[i]], Point(boundRect[num_part[i]].tl().x, boundRect[num_part[i]].tl().y+12)
                            , FONT_HERSHEY_PLAIN, 1, 0, 1, 8);
                    //Draw Size at the part
                    if(parts.Size[num_part[i]] != NULL){
                        sprintf(screen_obj, "Size: %.fmm", (parts.Size[num_part[i]]));
                        //sprintf(screen_obj, "Size: %.fmm", (radius[num_part[i]]*ratio_part));
                    }
                    else{
                        sprintf(screen_obj, "Size: %.fmm", (radius[num_part[i]]*ratio_part));
                    }
                    putText(img1, screen_obj, Point2f(boundRect[num_part[i]].tl().x, boundRect[num_part[i]].tl().y - 2)
                            , FONT_HERSHEY_PLAIN, 0.7,  Scalar(0,0,0), 1, 8);
                    //Draw Coordinates at the part
                    sprintf(screen_obj, "X:%.f Y:%.f", (center[num_part[i]].x*ratio_part/2), (center[num_part[i]].y*ratio_part/2));
                    putText(img1, screen_obj, Point2f(boundRect[num_part[i]].tl().x, boundRect[num_part[i]].tl().y + (radius[num_part[i]]*2) + 8)
                            , FONT_HERSHEY_PLAIN, 0.7,  Scalar(0,0,0), 1, 8);
                }
            }
        }

        //- CAMERA 2 -////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///IMAGE ACQUISITION
        if(key_pause == false){
            //Image from camera to Mat
            cap2 >> img2;
            img2.copyTo(img2Capture);
        }
        else{
            img2Capture.copyTo(img2);
        }
        //Frame empty at the end of the video
        if (img2.empty()){
            SaveDataTxt();
            cap1.release();
            cap2.release();
            destroyAllWindows();
            cout <<endl <<"End of image processing."<< endl;
            return 0;
        }
        //Get first image to the background image
        if(first_check!=1){
            cap2 >> img2Backg;
            //img2Backg = imread("photo_parts/img2Background.jpg");
        }

        ///PRE-PROCESSING
        //Do a simple background subtraction
        absdiff(img2, img2Backg, img2Foreg);
        //Add the mask of limits
        img2Foreg.copyTo(img2Proc, img2Mask);
        //Low-pass filter
        GaussianBlur(img2Proc, img2Proc, Size(5,5), 0, 0, BORDER_DEFAULT);

        ///SEGMENTATION
        //THRESHOLD BY COLOR
        inRange(img2Proc, Scalar(0, 83, 0), Scalar(255, 150, 95), img2Segm);
        //inRange(img2Proc, Scalar(Bmin, Gmin, Rmin), Scalar(Bmax, Gmax, Rmax), img2Segm);
        inRange(img2Proc, Scalar(83, 0, 0), Scalar(255, 46, 75), img2Proc);
        //inRange(img2Proc, Scalar(Bmin, Gmin, Rmin), Scalar(Bmax, Gmax, Rmax), img2Proc);
        //Add first image thresholded to second
        add(img2Segm, img2Proc, img2Segm);

        imshow(screen4, img2Segm);

        //DILATION AND EROSION
        //Apply opening that is erosion followed by dilation to to remove noise
        morphologyEx(img2Segm, img2Segm, MORPH_OPEN, Mat(), Point(-1,-1), 2, BORDER_DEFAULT);
        //Apply closing that is dilation followed by erosion to fill the holes
        morphologyEx(img2Segm, img2Segm, MORPH_CLOSE, Mat(), Point(-1,-1), 7, BORDER_DEFAULT);
        dilate(img2Segm, img2Segm, Mat(), Point(-1,-1), 2, BORDER_DEFAULT);

        ///RECOGNITION AND INTERPRETATION
        //Find contours
        vector<vector<Point> > contours2;
        vector<Vec4i> hierarchy2;
        vector<vector<Point> > contours_poly2( num_max_parts );
        vector<Rect> boundRect2( num_max_parts );
        vector<Point2f>center2( num_max_parts );
        vector<float>radius2( num_max_parts );

        findContours(img2Segm, contours2, hierarchy2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        //Fill the vectors in order of the parts at the conveyor
        if(first_check == 0){
            for(int k=0; k<num_max_parts; k++){
                if(contours2.size() < num_max_parts)
                    num_part[k] = contours2.size()+ k;
                else
                    num_part[k] = (contours2.size() + k) - (num_max_parts-1);
            }
            first_check = 1;
        }

        for(int i=0; i<contours2.size(); i++ ){

            //Approximate contours to polygons + get bounding rects + center
            approxPolyDP( Mat(contours2[i]), contours_poly2[num_part2[i]], 3, true );
            boundRect2[num_part2[i]] = boundingRect( Mat(contours_poly2[num_part2[i]]) );
            minEnclosingCircle( (Mat)contours_poly2[num_part2[i]], center2[num_part2[i]], radius2[num_part2[i]] );

            //Get the right number of the parts
            if(contours2.size()<limit_part2){
                //Save which is the first position
                init_part2 = num_part2[0];
                if(parts.last_center2[num_part2[i]][0].y > (img2.rows)){
                    //Move positions and your data
                    for(int k=0; k<(num_max_parts-1); k++){
                        num_part2[k] = num_part2[k+1];
                        parts.color[num_part2[k]] = parts.color[num_part2[k+1]];
                        for(int h=19; h>=0; h--){
                            parts.last_center2[num_part2[k]][h] = parts.last_center2[num_part2[k+1]][h];
                        }
                    }
                    //Define the first position to the last and clean data of vectors
                    num_part2[num_max_parts-1] = init_part2;
                    for(int h=19; h>=0; h--){
                        parts.last_center2[num_part2[num_max_parts-1]][h] = Point(0,0);
                    }
                }
            }
            limit_part2 = contours2.size();

            if(boundRect2[num_part2[i]].tl().y > limit_line_tl.y && center2[num_part2[i]].y < limit_line_bl.y){
                if(num_part2[contours2.size()-1] == num_max_parts)
                    acumul_parts2 = num_max_parts;
                cont_parts2 = acumul_parts2 + num_part2[i]+1;
            }

            //Save last center of objects to get trajectory
            if(boundRect2[num_part2[i]].tl().y > limit_line_tl.y){
                for(int j=19; j>=0; j--){
                    //Draw trajectory
                    //drawMarker(img2, parts.last_center2[num_part2[i]][j], parts.color[num_part2[i]], MARKER_CROSS, 5, 1, 8);
                    if(j!=0)
                        parts.last_center2[num_part2[i]][j] = parts.last_center2[num_part2[i]][j-1];
                    else
                        parts.last_center2[num_part2[i]][j] = center2[num_part2[i]];
                }
            }

            //Calculate the real coordinate of the parts in millimeters
            float x1, x2;
            x1 = (img2.rows - center2[num_part2[i]].y)/tan(mask_angle*pi/180);
            x2 = img2.cols - x1;
            parts.coord2[num_part2[i]].x = ((center2[num_part2[i]].x - (x1 + offset_line)) * width_conveyor)
                                            / ((x2-offset_line) - (x1+offset_line));

            int pix_h_correct = (h_correct - (h_correct * center2[num_part2[i]].y / img2.rows))
                                 * (((x2-offset_line) - (x1+offset_line)) / width_conveyor);
            x1 = (img2.rows - ((center2[num_part2[i]].y) + pix_h_correct))
                 /tan(mask_angle*pi/180);
            x2 = img2.cols - x1;
            int dist_a = sqrt(pow(dist_ref, 2) - pow(dist_h, 2));
            int dist_focal = (((img2.cols-offset_line)- offset_line) * dist_ref) / width_conveyor;   //F = ( P x D ) / W
            int dist_obj = ((width_conveyor * dist_focal) / ((x2-offset_line) - (x1+offset_line))) / f_correct;  //D' = ( W x F ) / P'
            int dist_b = sqrt(pow(dist_obj, 2) - pow(dist_h, 2)) - dist_a;
            parts.coord2[num_part2[i]].y = length_conveyor - dist_b + h_correct;

            //Calculate the scale to use on ellipses
            float ratio_widht2 = 0.06;
            float ratio_height2 = 0.04;
            float ell_width, ell_height;
            if(parts.Size[num_part2[i]] != NULL){
                ell_width = parts.Size[num_part2[i]]/1.9 + (ratio_widht2*center2[num_part2[i]].y);
                ell_height = parts.Size[num_part2[i]]/4.6 + (ratio_height2*center2[num_part2[i]].y);
            }
            else{
                ell_width = size_part/1.9 + (ratio_widht2*center2[num_part2[i]].y);
                ell_height = size_part/4.6 + (ratio_height2*center2[num_part2[i]].y);
            }

            ///PARTS RESULTS
            if(boundRect2[num_part2[i]].tl().y > limit_line_tl.y && center2[num_part2[i]].y < limit_line_bl.y){
                //Draw ellipses, rectangles and center points at the part
                drawMarker(img2, Point(center2[num_part2[i]].x, center2[num_part2[i]].y)
                           , parts.color[num_part2[i]], MARKER_CROSS, radius2[num_part2[i]]/3, 1, 8);
                //ellipse(img2, center2[num_part2[i]], Size(ell_width, ell_height), 0, 0, 360, parts.color[num_part2[i]], 1, 8);
                rectangle(img2, boundRect2[num_part2[i]].tl(), boundRect2[num_part2[i]].br(), parts.color[num_part2[i]], 1, 8, 0 );
                drawMarker(img2, Point(center2[num_part2[i]].x, center2[num_part2[i]].y + pix_h_correct)
                           , Scalar(255,0,0), MARKER_TRIANGLE_DOWN, radius2[num_part2[i]]/3, 1, 8);
                //Draw object number
                if(cont_parts1>0){
                    sprintf(screen_obj, "%d", num_part2[i]+1);
                    putText(img2, screen_obj, center2[num_part2[i]], FONT_HERSHEY_PLAIN, 1.2, parts.color[num_part2[i]], 2, 8);
                }
                //Draw Coordinates of the part
                sprintf(screen_obj, "P.%d - X:%.f Y:%.f", num_part2[i]+1, (float) parts.coord2[num_part2[i]].x, (float) parts.coord2[num_part2[i]].y);
                putText(img2, screen_obj, Point2f(10,460 - ((i+1)*15)), FONT_HERSHEY_PLAIN, .7,  parts.color[num_part2[i]], 1, 8);
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///GENERAL RESULTS
        ///-Camera 1
        //Calculate time to FPS
        time_fps = ((double)getTickCount() - time_fps)
                    /getTickFrequency();//Elapsed time in ms in a frame
        cont_time_fps = cont_time_fps + time_fps;//Counter of total elapsed time
        cont_frames++;
        if(cont_frames == 20){
            avg_fps = cont_frames/cont_time_fps;//n frames/second
            cont_frames = 0;
            cont_time_fps = 0;
        }
        //Draw FPS
        sprintf(screen_fps, "FPS: %.lf", avg_fps);
        putText(img1, screen_fps, Point2f(560,25), FONT_HERSHEY_PLAIN, 1,  Scalar(0,0,0), 1, 8);
/*        //Draw limits
        line(img1, Point(10, 10), Point(img1.cols - 10, 10), Scalar(100,100,100), 2, LINE_4, 0);
        line(img1, Point(10, img1.rows - 10), Point(img1.cols - 10, img1.rows - 10), Scalar(100,100,100), 2, LINE_4, 0);
/*        //Draw info for shortcuts
        putText(img1,"Esc - quit", Point2f(10,25), FONT_HERSHEY_PLAIN, .8,  Scalar(0,0,0), 1, 8);
        putText(img1,"space - snap parts", Point2f(10,40), FONT_HERSHEY_PLAIN, .8,  Scalar(0,0,0), 1, 8);
        putText(img1,"r - restart", Point2f(10,55), FONT_HERSHEY_PLAIN, .8,  Scalar(0,0,0), 1, 8);
        putText(img1,"c - clean data", Point2f(10,70), FONT_HERSHEY_PLAIN, .8,  Scalar(0,0,0), 1, 8);
        putText(img1,"p - pause video", Point2f(10,85), FONT_HERSHEY_PLAIN, .8,  Scalar(0,0,0), 1, 8);
        putText(img1,"o - continue video", Point2f(10,100), FONT_HERSHEY_PLAIN, .8,  Scalar(0,0,0), 1, 8);
*/        //Draw number of objects
        sprintf(screen_obj, "Bad: %d", cont_bad_parts);
        putText(img1, screen_obj, Point2f(10,400), FONT_HERSHEY_PLAIN, 1,  Scalar(0,0,0), 1, 8);
        sprintf(screen_obj, "Good: %d", cont_good_parts);
        putText(img1, screen_obj, Point2f(10,420), FONT_HERSHEY_PLAIN, 1,  Scalar(0,0,0), 1, 8);
        sprintf(screen_obj, "No def.: %d", cont_nodef_parts);
        putText(img1, screen_obj, Point2f(10,440), FONT_HERSHEY_PLAIN, 1,  Scalar(0,0,0), 1, 8);
        sprintf(screen_obj, "Objects: %d", cont_parts1);
        putText(img1, screen_obj, Point2f(10,460), FONT_HERSHEY_PLAIN, 1,  Scalar(0,0,0), 1, 8);
        //Show the results at the screen
        imshow(screen1, img1);

        ///-Camera 2
        //Draw limits
        //line(img2, ang_line_tl, ang_line_bl, Scalar(255,0,0), 2, LINE_4, 0);
        //line(img2, ang_line_tr, ang_line_br, Scalar(255,0,0), 2, LINE_4, 0);
        //line(img2, limit_line_tl, limit_line_tr, Scalar(0,0,255), 2, LINE_4, 0);
        //line(img2, limit_line_bl, limit_line_br, Scalar(0,0,255), 10, LINE_4, 0);
        //Draw number of objects
        sprintf(screen_obj, "Objects: %d", cont_parts2);
        putText(img2, screen_obj, Point2f(10,460), FONT_HERSHEY_PLAIN, 1,  Scalar(0,0,0), 1, 8);
        //Show the results at the screen
        imshow(screen3, img2);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //Update screens and get key if pressed
        key = waitKey(10);
        //Key to exit ou reset
        if(key == 27 || key == 'r')
            break; //27 - ESC
        //Key to clean database of part default
        if(key == 'c')
            CleanDefault();
        //Key to pause video
        if(key == 'p')
            key_pause = true;   //Pause video
        //Key to continue video video
        if(key == 'o')
            key_pause = false;  //Continue video
        if(key == 'f'){
            imwrite("Img1.jpg", img1);
            imwrite("Img2.jpg", img2);
        }
    }
    SaveDataTxt();
    cap1.release();
    cap2.release();
    destroyAllWindows();
    cout <<endl <<"End of image processing."<< endl;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LoadDataTxt(){
    FILE *load_data;

    //Read info
    load_data = fopen("Database.txt", "r");
    fscanf(load_data, "Threshold cam 1 = %d;\n", &thresh1);
    fscanf(load_data, "Threshold cam 2 = %d;\n", &thresh2);
    fscanf(load_data, "Threshold cam 3 = %d;\n", &thresh3);
    fscanf(load_data, "Bmin = %d;\n", &Bmin);
    fscanf(load_data, "Gmin = %d;\n", &Gmin);
    fscanf(load_data, "Rmin = %d;\n", &Rmin);
    fscanf(load_data, "Bmax = %d;\n", &Bmax);
    fscanf(load_data, "Gmax = %d;\n", &Gmax);
    fscanf(load_data, "Rmax = %d;\n", &Rmax);

    //Track bar for image
    createTrackbar("Thresh1", screen1, &thresh1, 255);
    //createTrackbar("Thresh2", screen3, &thresh2, 255);
    //createTrackbar("Thresh3", screen3, &thresh3, 255);
    createTrackbar("Bmin", screen5, &Bmin, 255);
    createTrackbar("Gmin", screen5, &Gmin, 255);
    createTrackbar("Rmin", screen5, &Rmin, 255);
    createTrackbar("Bmax", screen5, &Bmax, 255);
    createTrackbar("Gmax", screen5, &Gmax, 255);
    createTrackbar("Rmax", screen5, &Rmax, 255);

    if(ratio_part == 0.0)
        fscanf(load_data, "Ratio_part = %f; \n", &ratio_part);

    load_data = fopen("photo_parts/Data_parts.txt", "r");
    for(int j=0; j<num_max_default; j++){
        const char *c_label;
        string read_part_label = "Part ";
        stringstream read_num_part;
        read_num_part << j+1;
        read_part_label = read_part_label + read_num_part.str() + " : %s \n";
        c_label = read_part_label.c_str();
        fscanf(load_data, c_label, &label_part_def[j]);
    }

    fclose(load_data);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SaveDataTxt(){
    FILE *save_data;

    save_data = fopen("Database.txt", "w");
    fprintf(save_data, "Threshold cam 1 = %d; \n", thresh1);
    fprintf(save_data, "Threshold cam 2 = %d; \n", thresh2);
    fprintf(save_data, "Threshold cam 3 = %d; \n", thresh3);

    fprintf(save_data, "Bmin = %d; \n", Bmin);
    fprintf(save_data, "Gmin = %d; \n", Gmin);
    fprintf(save_data, "Rmin = %d; \n", Rmin);
    fprintf(save_data, "Bmax = %d; \n", Bmax);
    fprintf(save_data, "Gmax = %d; \n", Gmax);
    fprintf(save_data, "Rmax = %d; \n", Rmax);

    fprintf(save_data, "Ratio_part = %.6f; \n", ratio_part);

    fclose(save_data);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scalar ImgAvgColor(Mat imgPart){
    Scalar color_result, color_pix1, color_pix2;
    int color_sum[3];
    int calib = 4;
    int lin = imgPart.rows + calib;
    int col = imgPart.cols;
    int a, b, n_sum;

    memset(color_sum,(int)0,sizeof(int)*3);
    n_sum = 0;

    Point p;
    p.y = lin-5;
    p.x = col/2;

    color_pix1 = imgPart.at<Vec3b>(p.y, p.x); //Get pixel reference
    color_sum[0] = color_pix1.val[0];
    color_sum[1] = color_pix1.val[1];
    color_sum[2] = color_pix1.val[2];

    //Get median color of pixels doing a rhombus
    for(int i=calib; i<=(lin-(calib*2)); i++){
        if(i == calib){
            a = col/2;
            b = a;
        }
        if(i>0 && i<(lin/2)){
            a--;
            b++;
        }
        if(i>=(lin/2)){
            a++;
            b--;
        }
        n_sum++;

        color_pix1 = imgPart.at<Vec3b>(i, a);
        color_pix2 = imgPart.at<Vec3b>(i, b);
        color_sum[0] = color_sum[0] + color_pix1.val[0];
        color_sum[1] = color_sum[1] + color_pix1.val[1];
        color_sum[2] = color_sum[2] + color_pix1.val[2];
/*
        //Draw rhombus
        Point losang1, losang2;
        losang1.y = i;
        losang1.x = a;
        losang2.y = i;
        losang2.x = b;
        drawMarker(imgPart, losang1, Scalar(0,255,0), MARKER_CROSS, 1, 1, 8);
        drawMarker(imgPart, losang2, Scalar(0,255,0), MARKER_CROSS, 1, 1, 8);
*/
    }
    n_sum = n_sum + 1;
    color_result.val[0] = color_sum[0]/n_sum;
    color_result.val[1] = color_sum[1]/n_sum;
    color_result.val[2] = color_sum[2]/n_sum;

    return color_result;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scalar CheckColors(Mat imgPart){

    //Compare color part with color default
    int limit_erro = 80;
    int color_diff[4];
    int color_test = 500;
    Scalar color_result;

    for(int i=0; i<=(num_max_default-1); i++){

        if(color_def[i] != Scalar(0,0,0)){
            color_diff[0] = color_def[i].val[0] - color_part.val[0];
            color_diff[1] = color_def[i].val[1] - color_part.val[1];
            color_diff[2] = color_def[i].val[2] - color_part.val[2];
            if(color_diff[0]<0)
                color_diff[0] = color_diff[0] * (-1);
            if(color_diff[1]<0)
                color_diff[1] = color_diff[1] * (-1);
            if(color_diff[2]<0)
                color_diff[2] = color_diff[2] * (-1);
            color_diff[3] = color_diff[0] + color_diff[1] + color_diff[2];

            if(color_diff[3] < limit_erro && color_diff[3] < color_test){
                cout <<"*Part " <<cont_parts1+1 <<" / default " <<i+1 <<" : OK  ";
                color_test = color_diff[3];
                label_part = '\0';
                label_part = label_part_def[i];
                color_result = Scalar(0,255,0);
            }
            else{
                cout <<"*Part " <<cont_parts1+1 <<" / default " <<i+1 <<" : ERROR  ";
            }
        //cout<<color_diff[3]<<endl;
        }
    }

    if(color_result != Scalar(0,255,0))
        color_result = Scalar(0,0,255);

    cout <<endl;
    return color_result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SnapDefault(Mat imgPart, int num_obj){
    if(press_times == 0){
        CleanDefault();
    }
    press_times++;

    string file_name_number = "photo_parts/photo_part";
    stringstream num_picture;
    num_picture << press_times;
    file_name_number = file_name_number + num_picture.str() + ".jpg";
    cout <<"Picture saved - "<< file_name_number<< endl;
    imwrite(file_name_number, imgPart);

    if(press_times == num_obj){
        FILE *save_data;
        save_data = fopen("photo_parts/Data_parts.txt", "w");
        cout <<endl;
        for(int j=0; j<num_obj; j++){
            string name_part;
            cout <<"Digit the name of the part " <<j+1 <<": ";
            getline(cin, name_part);
            fprintf(save_data, "Part %d : %s\n", j+1, name_part.c_str());
        }
        cout <<"Name of the parts saved!" <<endl;
        fclose(save_data);
        press_times=0;
    }
    cout <<flush;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LoadDefault(){

    float avg_size_def = 0.0;
    int num_obj = 0;

    cout <<"Size default: " <<size_part <<"mm" <<endl;
    for(int i=0; i<num_max_default; i++){
        string file_name_number = "photo_parts/photo_part";
        stringstream num_picture;
        num_picture << i+1;
        file_name_number = file_name_number + num_picture.str() + ".jpg";

        const char *file_name_test = file_name_number.c_str();
        FILE *file_test;
        file_test = fopen(file_name_test, "r");
        if(!file_test){
            color_def[i] = NULL;
            cout <<"Part default "<< i+1<< " not found!"<< endl;
            fclose(file_test);
        }
        else{
            imgLoad = imread(file_name_number);
            color_def[i] = ImgAvgColor(imgLoad);
            avg_size_def = (2.*size_part/((imgLoad.rows+imgLoad.cols)/2.));
            ratio_part = ratio_part+avg_size_def;
            num_obj++;
            cout <<"Part default " <<i+1 <<" : avg color " <<color_def[i] << endl;
            fclose(file_test);
        }
    }
    if(num_obj != 0)
        ratio_part = ratio_part/num_obj;

    cout <<endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CleanDefault(){
    for(int i=0; i<num_max_default; i++){
        string file_name_number = "photo_parts/photo_part";
        stringstream num_picture;
        num_picture << i+1;
        file_name_number = file_name_number + num_picture.str() + ".jpg";

        const char *file_name_test = file_name_number.c_str();
        FILE *file_test;
        file_test = fopen(file_name_test, "w");
        if(!file_test){
            fclose(file_test);
        }
        else{
            fclose(file_test);
            DeleteFile(file_name_test);
            color_def[i] = NULL;
            cout <<"Part default " <<i+1 <<" removed " << color_def[i] <<endl;
        }
    }
    cout <<"Clean database default sucessfully!" <<endl <<endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
