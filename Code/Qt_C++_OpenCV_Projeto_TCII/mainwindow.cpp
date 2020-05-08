#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include "configinputs.h"
#include "configprocess.h"
#include "setinput.h"
#include "addpartdefault.h"
#include "infoabout.h"

#include <dirent.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#define pi 3.14159
#define screen1 "Imagem Webcam 1"
#define screen2 "Imagem Processada 1"
#define screen3 "Imagem Webcam 2"
#define screen4 "Imagem Processada 2"
#define screen5 "Limiar RGB"
#define num_max_parts   10              //Maximum number of parts to register in image
#define num_max_default   9             //Maximum number of standard parts
#define num_inspections 1               //Times to do the inspections
#define f_correct 0.96                   //Correction factor to apply at the distance between camera2 and object
#define h_correct 35                    //Height of the object to correct distance

using namespace cv;
using namespace std;

Scalar ImgAvgColor(Mat imgPart);
Scalar CheckColors(Mat imgPart);
void SnapDefault(Mat imgPart);

///Capture from web camera like public variable
//VideoCapture cap1(0); //Camera 1
//VideoCapture cap2(2); //Camera 2
//VideoCapture cap1("Cam1_video.avi"); //Capture image from video recorded
//VideoCapture cap2("Cam2_video.avi"); //Capture image from video recorded
VideoCapture cap1;
VideoCapture cap2;

int key;
Mat img1, img1Gray, img1Proc, imgLoad, img1Capture, img1Backg, img1Foreg,
    img2, img2Gray, img2Proc, img2Mask, img2Capture, img2Backg,  img2Foreg, img2Segm;
double cont_time_fps, avg_fps;
int cont_frames, press_times;
char screen_fps[10], screen_obj[15],label_part_def[num_max_default][25];
string label_part;
int cont_parts1, cont_parts2, cont_good_parts, cont_bad_parts, cont_nodef_parts, acumul_parts2;
int num_part[num_max_parts], num_part2[num_max_parts];
int init_part, limit_part, init_part2, limit_part2;
Scalar color_def[num_max_default], color_part, color_result, color_size;
Point   ang_line_tl, ang_line_bl, ang_line_tr, ang_line_br,
        limit_line_tl, limit_line_tr, limit_line_bl, limit_line_br;
float ratio_part;   //Ratio between image and part radius
bool first_check = 1;
bool key_pause = false;
bool key_add = false;
bool bot_reinit = false;
bool bot_ok_add = false;
string cap1_name, cap2_name;
bool first_connect = 1;

//Variables parts
int num_inspec[num_max_parts];
Scalar color[num_max_parts];
Point last_center[num_max_parts][20];
Point last_center2[num_max_parts][20];
float Psize[num_max_parts];
string screen_defect[num_max_parts];
string screen_label[num_max_parts];
Point coord2[num_max_parts];

//Variables settings
int size_Gaussian, size_Open, size_Close;
int size_Gaussian2, size_Open2, size_Close2;
int Rmin, Gmin, Bmin, Rmax, Gmax, Bmax, Rmin2, Gmin2, Bmin2, Rmax2, Gmax2, Bmax2;
int Rmin3, Gmin3, Bmin3, Rmax3, Gmax3, Bmax3, Rmin4, Gmin4, Bmin4, Rmax4, Gmax4, Bmax4;

QTimer *timer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mkdir("config");
    mkdir("default");
    mkdir("images");
    mkdir("temp");

    //Load the name of the default parts
    LoadDefault();

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///MAIN WINDOW
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MainProcess(){

    ConfigInputs configInputs;

    if(key_add == true){
        if(bot_ok_add == true){
            first_check = 1;
            bot_ok_add = false;
        }
        key_add = false;
        key = 0;
    }

    if(first_check == 1){

        ui->TelaInfo->clear();
        ui->TelaInfo_2->clear();

        key = 0;
        press_times = 0;
        ratio_part = 0;
        cont_parts1 = 0;
        cont_parts2 = 0;
        cont_nodef_parts = 0;
        cont_bad_parts = 0;
        cont_good_parts = 0;
        acumul_parts2 = 0;
        init_part = 0;
        init_part2 = 0;
        limit_part = 0;
        limit_part2 = 0;

        //Fill the vectors on initiate state
        for(int k=0; k<num_max_parts; k++){
            num_part[k] = k;
            num_part2[k] = k;
            num_inspec[k] = NULL;
            color[k] = NULL;
            Psize[k] = NULL;
            screen_defect[k] = '\0';
            screen_label[k] = '\0';
            coord2[k] = Point(0,0);
            for(int h=19; h>=0; h--){
                last_center[k][h] = Point(0,0);
                last_center2[k][h] = Point(0,0);
            }
        }

        cap1 >> img1;
        string textInfo;
        stringstream largura, altura;
        largura << img1.cols;
        altura << img1.rows;
        textInfo = "Resolução entrada: " + largura.str() + "x" + altura.str();
        ui->TelaInfo->appendPlainText(textInfo.c_str());

        cap2 >> img2;
        largura.str("");
        altura.str("");
        largura << img2.cols;
        altura << img2.rows;
        textInfo = "Resolução entrada: " + largura.str() + "x" + altura.str() + "\n";
        ui->TelaInfo_2->appendPlainText(textInfo.c_str());

        //Read data of RGB features
        LoadConfigProcess();

        //Load the name of the default parts
        LoadDefault();

        //Load images of part default and get the average color
        LoadDefault_compare();

        FILE *readConfigIn;
        readConfigIn = fopen("config/inputs.txt", "r");
        fscanf(readConfigIn, "size_part = %d;\n", &configInputs.size_part);
        fscanf(readConfigIn, "mask_angle = %.2f;\n", &configInputs.mask_angle);
        fscanf(readConfigIn, "offset_line = %d;\n", &configInputs.offset_line);
        fscanf(readConfigIn, "width_conveyor = %d;\n", &configInputs.width_conveyor);
        fscanf(readConfigIn, "length_conveyor = %d;\n", &configInputs.length_conveyor);
        fscanf(readConfigIn, "dist_ref = %d;\n", &configInputs.dist_ref);
        fscanf(readConfigIn, "dist_h = %d;\n", &configInputs.dist_h);
        fclose(readConfigIn);

        ang_line_tl.x = (img1.rows/tan(configInputs.mask_angle*pi/180)) + configInputs.offset_line;
        ang_line_tl.y = 0;
        ang_line_bl.x= configInputs.offset_line;
        ang_line_bl.y = img1.rows;
        ang_line_tr.x = img1.cols - (img1.rows/tan(configInputs.mask_angle*pi/180)) - configInputs.offset_line;
        ang_line_tr.y = 0;
        ang_line_br.x = img1.cols - configInputs.offset_line;
        ang_line_br.y = img1.rows;
        limit_line_tl.x = (img1.rows/tan(configInputs.mask_angle*pi/180)) + configInputs.offset_line;
        limit_line_tl.y = 20;
        limit_line_tr.x = img1.cols - (img1.rows/tan(configInputs.mask_angle*pi/180)) - configInputs.offset_line;
        limit_line_tr.y = 20;
        limit_line_bl.x = configInputs.offset_line;
        limit_line_bl.y = img1.rows;
        limit_line_br.x = img1.cols - configInputs.offset_line;
        limit_line_br.y = img1.rows;

        ///Create and apply mask (limit angle) at image 2
        img2Mask = Mat::zeros(img1.size(), CV_8U);
        for(int i=limit_line_tl.y; i<limit_line_bl.y; i++){
            float x1, x2;
            x1 = (img2Mask.rows - i)/tan(configInputs.mask_angle*pi/180);
            x2 = img2Mask.cols - x1;
            line(img2Mask, Point2f(x1+configInputs.offset_line, i),
                 Point2f(x2-configInputs.offset_line, i), Scalar(255,0,0), 1, 8, 0);
        }

        //Get first image to the background image
        //cap1 >> img1Backg;
        img1Backg = imread("images/set1Background.jpg");

        //Get first image to the background image
        //cap2 >> img2Backg;
        img2Backg = imread("images/set2Background.jpg");
    }\

    //- CAMERA 1 -////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Get time to FPS
    double time_fps = (double)getTickCount();

    ///IMAGE ACQUISITION
    if(key_pause == false){
        //Image from camera to Mat
        cap1 >> img1;
        if(!img1.empty())
            img1.copyTo(img1Capture);
    }
    else{
        img1Capture.copyTo(img1);
    }

    //Frame empty at the end of the video
    if (img1.empty()){
        cap1.release();
        timer->stop();
        ui->TelaInfo_2->clear();
        ui->statusBar->showMessage("Fim do processamento de imagens!");
        return;
    }

    ///PRE-PROCESSING
    //Do a simple background subtraction
    absdiff(img1, img1Backg, img1Foreg);

    ///Low-pass filters
    GaussianBlur(img1Foreg, img1Proc, Size(size_Gaussian,size_Gaussian), 0, 0, BORDER_DEFAULT);

    ///SEGMENTATION
    Mat img1Segm;
    //THRESHOLD BY COLOR
    inRange(img1Proc, Scalar(Bmin, Gmin, Rmin), Scalar(Bmax, Gmax, Rmax), img1Segm);
    inRange(img1Proc, Scalar(Bmin2, Gmin2, Rmin2), Scalar(Bmax2, Gmax2, Rmax2), img1Proc);
    //inRange(img1Proc, Scalar(Bmin, Gmin, Rmin), Scalar(Bmax, Gmax, Rmax), img1Proc);

    add(img1Segm, img1Proc, img1Segm);

    //DILATION AND EROSION
    //Apply opening that is erosion followed by dilation to to remove noise
    morphologyEx(img1Segm, img1Segm, MORPH_OPEN, Mat(), Point(-1,-1), size_Open, BORDER_DEFAULT);
    //Apply closing that is dilation followed by erosion to fill the holes
    morphologyEx(img1Segm, img1Segm, MORPH_CLOSE, Mat(), Point(-1,-1), size_Close, BORDER_DEFAULT);
    //dilate(img1Segm, img1Segm, Mat(), Point(-1,-1), 2, BORDER_DEFAULT);
    erode(img1Segm, img1Segm, Mat(), Point(-1,-1), 3, BORDER_DEFAULT);

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

    if(first_check != 1){
        if(key == ' ')
            key_add = true;

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
                    color[num_part[k]] = color[num_part[k+1]];
                    Psize[num_part[k]] = Psize[num_part[k+1]];
                    num_inspec[num_part[k]] = num_inspec[num_part[k+1]];
                    screen_defect[num_part[k]] = screen_defect[num_part[k+1]];
                    screen_label[num_part[k]] = screen_label[num_part[k+1]];
                    for(int h=19; h>=0; h--){
                        last_center[num_part[k]][h] = last_center[num_part[k+1]][h];
                    }
                }
                //Define the first position to the last and clean data of vectors
                num_part[num_max_parts-1] = init_part;
                color[num_part[contours.size()]] = NULL;
                Psize[num_part[contours.size()]] = NULL;
                num_inspec[num_part[contours.size()]] = NULL;
                screen_defect[num_part[contours.size()]] = '\0';
                screen_label[num_part[contours.size()]] = '\0';
                for(int h=19; h>=0; h--){
                    last_center[num_part[contours.size()]][h] = Point(0,0);
                }
            }
            limit_part = contours.size();

            //Inspection of the parts
            if(boundRect[num_part[i]].tl().y > 10 && boundRect[num_part[i]].br().y < (img1.rows - 10)
               && num_inspec[num_part[i]] < num_inspections){

                //Verify the scale if is ok
                if((radius[num_part[i]]<(configInputs.size_part/ratio_part)-3) ||
                   (radius[num_part[i]]>(configInputs.size_part/ratio_part)+3)){
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
                    screen_defect[num_part[i]] = "OK";
                    screen_label[num_part[i]] = label_part;
                    Psize[num_part[i]] = radius[num_part[i]]*ratio_part;
                    color[num_part[i]] = Scalar(0,255,0);
                    cont_good_parts++;
                    cont_parts1++;
                    //Write results
                    string textInfo;
                    stringstream text_part, text_label;
                    text_part << num_part[i]+1;
                    text_label << label_part;
                    textInfo = "Peça " + text_part.str() + " - (OK) = " + text_label.str();
                    ui->TelaInfo->appendPlainText(textInfo.c_str());

                }
                else if(color_size == Scalar(0,0,255) && color_result == Scalar(0,255,0)) {
                    screen_defect[num_part[i]] = "Size";
                    screen_label[num_part[i]] = "?";
                    color[num_part[i]] = Scalar(0,0,255);
                    cont_bad_parts++;
                    cont_parts1++;
                    //Write results
                    string textInfo;
                    stringstream text_part, text_label;
                    text_part << num_part[i]+1;
                    text_label << label_part;
                    textInfo = "Peça " + text_part.str() + " - (ERRO) = Tamanho";
                    ui->TelaInfo->appendPlainText(textInfo.c_str());
                }
                else if(color_size == Scalar(0,255,0) && color_result == Scalar(0,0,255)) {
                    screen_defect[num_part[i]] = "Color";
                    screen_label[num_part[i]] = "?";
                    color[num_part[i]] = Scalar(0,0,255);
                    cont_bad_parts++;
                    cont_parts1++;
                    //Write results
                    string textInfo;
                    stringstream text_part, text_label;
                    text_part << num_part[i]+1;
                    text_label << label_part;
                    textInfo = "Peça " + text_part.str() + " - (ERRO) = Cor";
                    ui->TelaInfo->appendPlainText(textInfo.c_str());
                }
                else if(color_size == Scalar(0,0,255) && color_result == Scalar(0,0,255)) {
                    screen_defect[num_part[i]] = "Size/Color";
                    screen_label[num_part[i]] = "?";
                    color[num_part[i]] = Scalar(0,0,255);
                    cont_bad_parts++;
                    cont_parts1++;
                    //Write results
                    string textInfo;
                    stringstream text_part, text_label;
                    text_part << num_part[i]+1;
                    text_label << label_part;
                    textInfo = "Peça " + text_part.str() + " - (ERRO) = Tamanho/Cor";
                    ui->TelaInfo->appendPlainText(textInfo.c_str());
                }
                else if(color_size == Scalar(0,0,255) && color_result == Scalar(0,0,0)) {
                    screen_defect[num_part[i]] = "Size/No ref.";
                    screen_label[num_part[i]] = "?";
                    color[num_part[i]] = Scalar(0,0,255);
                    cont_bad_parts++;
                    cont_parts1++;
                    //Write results
                    string textInfo;
                    stringstream text_part, text_label;
                    text_part << num_part[i]+1;
                    text_label << label_part;
                    textInfo = "Peça " + text_part.str() + " - (ERRO) = Tamanho/Sem referência";
                    ui->TelaInfo->appendPlainText(textInfo.c_str());
                }
                else if(color_size == Scalar(0,255,0) && color_result == Scalar(0,0,0)) {
                    screen_defect[num_part[i]] = "No ref.";
                    screen_label[num_part[i]] = "?";
                    color[num_part[i]] = Scalar(0,0,0);
                    cont_nodef_parts++;
                    cont_parts1++;
                    //Write results
                    string textInfo;
                    stringstream text_part, text_label;
                    text_part << num_part[i]+1;
                    text_label << label_part;
                    textInfo = "Peça " + text_part.str() + " - (ERRO) = Sem referência";
                    ui->TelaInfo->appendPlainText(textInfo.c_str());
                }
                num_inspec[num_part[i]]++;
                //Save scale of the part
                Psize[num_part[i]] = radius[num_part[i]]*ratio_part;
            }
            else if(num_inspec[num_part[i]] == 0 && boundRect[num_part[i]].br().y > (img1.rows - 10)){
                screen_defect[num_part[i]] = "No def.";
                screen_label[num_part[i]] = "?";
                color[num_part[i]] = Scalar(0,0,0);
                cont_nodef_parts++;
                num_inspec[num_part[i]]++;
                cont_parts1++;
            }
            else if(num_inspec[num_part[i]] == num_inspections){
                num_inspec[num_part[i]]++;
            }

            //Take picture from the parts
            if(key_add == true && boundRect[num_part[i]].tl().y > 10 && center[num_part[i]].y < (img1.rows-10)){
                Mat imgRect(img1, Rect(boundRect[num_part[i]].tl(), boundRect[num_part[i]].br()));
                SnapDefault(imgRect);
            }
            //Save last center of objects to get trajectory
            if(boundRect[num_part[i]].tl().y > 10){
                for(int j=19; j>=0; j--){
                    //Draw trajectory
                    //drawMarker(img1, last_center[num_part[i]][j], color[num_part[i]], MARKER_CROSS, 5, 1, 8);
                    if(j!=0)
                        last_center[num_part[i]][j] = last_center[num_part[i]][j-1];
                    else
                        last_center[num_part[i]][j] = center[num_part[i]];
                }
            }

            //Define boundRect with the size of the inspection
            if(Psize[num_part[i]] != NULL && Psize[num_part[i]] > (configInputs.size_part - 20)){
                boundRect[num_part[i]].y = center[num_part[i]].y - (Psize[num_part[i]]/ratio_part);
                boundRect[num_part[i]].x = center[num_part[i]].x - (Psize[num_part[i]]/ratio_part);
                boundRect[num_part[i]].height = 2 * Psize[num_part[i]]/ratio_part;
                boundRect[num_part[i]].width = 2 * Psize[num_part[i]]/ratio_part;
            }

            ///PARTS RESULTS
            if(boundRect[num_part[i]].tl().y > 10 && center[num_part[i]].y < (img1.rows-10)){
                //Draw rectangles and center points
                rectangle(img1, boundRect[num_part[i]].tl(), boundRect[num_part[i]].br(), color[num_part[i]], 1, 8, 0 );
                drawMarker(img1, center[num_part[i]], color[num_part[i]], MARKER_CROSS, radius[num_part[i]]/2, 1, 8);
                //Draw object number
                if(cont_parts1>0){
                    sprintf(screen_obj, "%d", num_part[i]+1);
                    putText(img1, screen_obj, center[num_part[i]], FONT_HERSHEY_PLAIN, 2, color[num_part[i]], 2, 8);
                }
                //Draw Result
                putText(img1, screen_defect[num_part[i]], Point(boundRect[num_part[i]].tl().x, boundRect[num_part[i]].br().y)
                        , FONT_HERSHEY_PLAIN, 1, color[num_part[i]], 1, 8);
                putText(img1, screen_label[num_part[i]], Point(boundRect[num_part[i]].tl().x, boundRect[num_part[i]].tl().y+12)
                        , FONT_HERSHEY_PLAIN, 1, 0, 1, 8);
                //Draw Size at the part
                if(Psize[num_part[i]] != NULL){
                    sprintf(screen_obj, "Size: %.fmm", (Psize[num_part[i]]));
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

        if(key_add == true){
            AddPartDefault addPartDef;
            addPartDef.setModal(true);
            addPartDef.show();
            addPartDef.exec();

            bot_ok_add = addPartDef.bot_ok;
            press_times = 0;
        }
    }

    //- CAMERA 2 -////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///IMAGE ACQUISITION
    if(key_pause == false){
        //Image from camera to Mat
        cap2 >> img2;
        if(!img2.empty())
            img2.copyTo(img2Capture);
    }
    else{
        img2Capture.copyTo(img2);
    }
    //Frame empty at the end of the video
    if (img2.empty()){
        cap2.release();
        ui->TelaInfo_2->clear();
        ui->statusBar->showMessage("Fim do processamento de imagens!");
        return;
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
    inRange(img2Proc, Scalar(Bmin3, Gmin3, Rmin3), Scalar(Bmax3, Gmax3, Rmax3), img2Segm);
    inRange(img2Proc, Scalar(Bmin4, Gmin4, Rmin4), Scalar(Bmax4, Gmax4, Rmax4), img2Proc);
    //Add first image thresholded to second
    add(img2Segm, img2Proc, img2Segm);

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
    if(first_check == 1){
        for(int k=0; k<num_max_parts; k++){
            if(contours2.size() < num_max_parts)
                num_part[k] = contours2.size()+ k;
            else
                num_part[k] = (contours2.size() + k) - (num_max_parts-1);
        }
        first_check = 0;
    }

    if(contours2.size() > 0)
        ui->TelaInfo_2->clear();

    for(int i=0; i<contours2.size(); i++ ) {

        //Approximate contours to polygons + get bounding rects + center
        approxPolyDP( Mat(contours2[i]), contours_poly2[num_part2[i]], 3, true );
        boundRect2[num_part2[i]] = boundingRect( Mat(contours_poly2[num_part2[i]]) );
        minEnclosingCircle( (Mat)contours_poly2[num_part2[i]], center2[num_part2[i]], radius2[num_part2[i]] );

        //Break this detection, there some point wrong
        if(radius2[num_part2[i]] < 10){
           break;
        }

        //Get the right number of the parts
        if(contours2.size()<limit_part2){
            //Save which is the first position
            init_part2 = num_part2[0];
            if(center2[num_part2[i]].y > (img2.rows/2)){
                //Move positions and your data
                for(int k=0; k<(num_max_parts-1); k++){
                    num_part2[k] = num_part2[k+1];
                    color[num_part2[k]] = color[num_part2[k+1]];
                    for(int h=19; h>=0; h--){
                        last_center2[num_part2[k]][h] = last_center2[num_part2[k+1]][h];
                    }
                }
                //Define the first position to the last and clean data of vectors
                num_part2[num_max_parts-1] = init_part2;
                for(int h=19; h>=0; h--){
                    last_center2[num_part2[num_max_parts-1]][h] = Point(0,0);
                }
            }
        }
        limit_part2 = contours2.size();

        //Calculate the real coordinate of the parts in millimeters
        float x1, x2;
        x1 = (img2.rows - center2[num_part2[i]].y)/tan(configInputs.mask_angle*pi/180);
        x2 = img2.cols - x1;
        coord2[num_part2[i]].x = ((center2[num_part2[i]].x - (x1 + configInputs.offset_line))
                                    * configInputs.width_conveyor)
                                    / ((x2-configInputs.offset_line) - (x1+configInputs.offset_line));

        int pix_h_correct = (h_correct - (h_correct * center2[num_part2[i]].y / img2.rows))
                             * (((x2-configInputs.offset_line) - (x1+configInputs.offset_line))
                             / configInputs.width_conveyor);
        x1 = (img2.rows - ((center2[num_part2[i]].y) + pix_h_correct))
             /tan(configInputs.mask_angle*pi/180);
        x2 = img2.cols - x1;
        int dist_a = sqrt(pow(configInputs.dist_ref, 2) - pow(configInputs.dist_h, 2));
        int dist_focal = (((img2.cols-configInputs.offset_line)- configInputs.offset_line)
                          * configInputs.dist_ref) / configInputs.width_conveyor;   //F = ( P x D ) / W
        int dist_obj = ((configInputs.width_conveyor * dist_focal)
                        / ((x2-configInputs.offset_line) - (x1+configInputs.offset_line))) / f_correct;  //D' = ( W x F ) / P'
        int dist_b = sqrt(pow(dist_obj, 2) - pow(configInputs.dist_h, 2)) - dist_a;
        coord2[num_part2[i]].y = configInputs.length_conveyor - dist_b + h_correct;

        //Calculate the scale to use on ellipses
        float ratio_widht2 = 0.06;
        float ratio_height2 = 0.04;
        float ell_width, ell_height;
        if(Psize[num_part2[i]] != NULL){
            ell_width = Psize[num_part2[i]]/1.9 + (ratio_widht2*center2[num_part2[i]].y);
            ell_height = Psize[num_part2[i]]/4.6 + (ratio_height2*center2[num_part2[i]].y);
        }
        else{
            ell_width = configInputs.size_part/1.9 + (ratio_widht2*center2[num_part2[i]].y);
            ell_height = configInputs.size_part/4.6 + (ratio_height2*center2[num_part2[i]].y);
        }

        //Increase number of object
        if(boundRect2[num_part2[i]].tl().y > limit_line_tl.y){
            if(num_part2[contours2.size()-1] == num_max_parts)
                acumul_parts2 = num_max_parts;
            if(num_part2[i]+1 > cont_parts2)
                cont_parts2 = acumul_parts2 + num_part2[i]+1;
        }

        //Save last center of objects to get trajectory
        if(boundRect2[num_part2[i]].tl().y > limit_line_tl.y){
            for(int j=19; j>=0; j--){
                //Draw trajectory
                //drawMarker(img2, parts.last_center2[num_part2[i]][j], parts.color[num_part2[i]], MARKER_CROSS, 5, 1, 8);
                if(j!=0)
                    last_center2[num_part2[i]][j] = last_center2[num_part2[i]][j-1];
                else
                    last_center2[num_part2[i]][j] = center2[num_part2[i]];
            }
        }

        ///PARTS RESULTS
        if(boundRect2[num_part2[i]].tl().y > limit_line_tl.y &&
                center2[num_part2[i]].y < (limit_line_bl.y-10)){
            //Draw ellipses, rectangles and center points at the part
            drawMarker(img2, Point(center2[num_part2[i]].x, center2[num_part2[i]].y)
                       , color[num_part2[i]], MARKER_CROSS, radius2[num_part2[i]]/3, 1, 8);
            //ellipse(img2, center2[num_part2[i]], Size(ell_width, ell_height), 0, 0, 360, parts.color[num_part2[i]], 1, 8);
            rectangle(img2, boundRect2[num_part2[i]].tl(), boundRect2[num_part2[i]].br(), color[num_part2[i]], 1, 8, 0 );
            drawMarker(img2, Point(center2[num_part2[i]].x, center2[num_part2[i]].y + pix_h_correct)
                       , Scalar(255,0,0), MARKER_TRIANGLE_DOWN, radius2[num_part2[i]]/3, 1, 8);
            //Draw object number
            if(cont_parts2>0){
                sprintf(screen_obj, "%d", num_part2[i]+1);
                putText(img2, screen_obj, center2[num_part2[i]], FONT_HERSHEY_PLAIN, 1.2, color[num_part2[i]], 2, 8);
            }
            //Draw Coordinates of the part
            string textInfo2;
            stringstream text_part, text_coordx, text_coordy;
            text_part << num_part2[i]+1;
            text_coordx << (float) coord2[num_part2[i]].x;
            text_coordy << (float) coord2[num_part2[i]].y;
            textInfo2 = "Peça " + text_part.str() + " - "
                        + "X:" + text_coordx.str() + " " + "Y:" + text_coordy.str();
            ui->TelaInfo_2->appendPlainText(textInfo2.c_str());
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///GENERAL RESULTS
    ///-Camera 1
    //Draw limits
    line(img1, Point(10, 10), Point(img1.cols - 10, 10), Scalar(100,100,100), 2, LINE_4, 0);
    line(img1, Point(10, img1.rows - 10), Point(img1.cols - 10, img1.rows - 10), Scalar(100,100,100), 2, LINE_4, 0);

    //Draw number of objects
    ui->label_good->setNum(cont_good_parts);
    ui->label_bad->setNum(cont_bad_parts);
    ui->label_nodef->setNum(cont_nodef_parts);
    ui->label_objects->setNum(cont_parts1);
    //Show the results at the screen
    cv::resize(img1, img1, Size(550,412), 0, 0, INTER_CUBIC);
    cvtColor(img1, img1, CV_BGR2RGB);
    QImage qImage((uchar*)img1.data, img1.cols, img1.rows, img1.step, QImage::Format_RGB888);
    ui->ScreenResult_1->setPixmap(QPixmap::fromImage(qImage));

    ///-Camera 2
    //Draw limits
    line(img2, ang_line_tl, ang_line_bl, Scalar(255,0,0), 2, LINE_4, 0);
    line(img2, ang_line_tr, ang_line_br, Scalar(255,0,0), 2, LINE_4, 0);
    line(img2, limit_line_tl, limit_line_tr, Scalar(100,100,100), 2, LINE_4, 0);
    line(img2, limit_line_bl, limit_line_br, Scalar(100,100,100), 2, LINE_4, 0);
    //Draw number of objects
    ui->label_objects_2->setNum(cont_parts2);
    //Show the results at the screen
    cv::resize(img2, img2, Size(550,412), 0, 0, INTER_CUBIC);
    cvtColor(img2, img2, CV_BGR2RGB);
    QImage qImage2((uchar*)img2.data, img2.cols, img2.rows, img2.step, QImage::Format_RGB888);
    ui->ScreenResult_2->setPixmap(QPixmap::fromImage(qImage2));

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
    ui->statusBar->showMessage(screen_fps);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::LoadConfigProcess(){
    FILE *load_data;

    //Read info
    load_data = fopen("config/process.txt", "r");

    fscanf(load_data, "size_Gaussian = %d;\n", &size_Gaussian);
    fscanf(load_data, "size_Open = %d;\n", &size_Open);
    fscanf(load_data, "size_Close = %d;\n", &size_Close);

    fscanf(load_data, "size_Gaussian2 = %d;\n", &size_Gaussian2);
    fscanf(load_data, "size_Open2 = %d;\n", &size_Open2);
    fscanf(load_data, "size_Close2 = %d;\n", &size_Close2);

    fscanf(load_data, "Bmin = %d;\n", &Bmin);
    fscanf(load_data, "Gmin = %d;\n", &Gmin);
    fscanf(load_data, "Rmin = %d;\n", &Rmin);
    fscanf(load_data, "Bmax = %d;\n", &Bmax);
    fscanf(load_data, "Gmax = %d;\n", &Gmax);
    fscanf(load_data, "Rmax = %d;\n", &Rmax);

    fscanf(load_data, "Bmin2 = %d;\n", &Bmin2);
    fscanf(load_data, "Gmin2 = %d;\n", &Gmin2);
    fscanf(load_data, "Rmin2 = %d;\n", &Rmin2);
    fscanf(load_data, "Bmax2 = %d;\n", &Bmax2);
    fscanf(load_data, "Gmax2 = %d;\n", &Gmax2);
    fscanf(load_data, "Rmax2 = %d;\n", &Rmax2);

    fscanf(load_data, "Bmin3 = %d;\n", &Bmin3);
    fscanf(load_data, "Gmin3 = %d;\n", &Gmin3);
    fscanf(load_data, "Rmin3 = %d;\n", &Rmin3);
    fscanf(load_data, "Bmax3 = %d;\n", &Bmax3);
    fscanf(load_data, "Gmax3 = %d;\n", &Gmax3);
    fscanf(load_data, "Rmax3 = %d;\n", &Rmax3);

    fscanf(load_data, "Bmin4 = %d;\n", &Bmin4);
    fscanf(load_data, "Gmin4 = %d;\n", &Gmin4);
    fscanf(load_data, "Rmin4 = %d;\n", &Rmin4);
    fscanf(load_data, "Bmax4 = %d;\n", &Bmax4);
    fscanf(load_data, "Gmax4 = %d;\n", &Gmax4);
    fscanf(load_data, "Rmax4 = %d;\n", &Rmax4);

    if(ratio_part == 0.0)
        fscanf(load_data, "Ratio_part = %f; \n", &ratio_part);

    fclose(load_data);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::LoadDefault(){

    //Clear images of parts - default
    ui->PartDef_1->clear();
    ui->PartDef_2->clear();
    ui->PartDef_3->clear();
    ui->PartDef_4->clear();
    ui->PartDef_5->clear();
    ui->PartDef_6->clear();
    ui->PartDef_7->clear();
    ui->PartDef_8->clear();
    ui->PartDef_9->clear();

    QPixmap imgRect1("default/part_default1.jpg");
    ui->PartDef_1->setPixmap(imgRect1.scaled(100,100));
    QPixmap imgRect2("default/part_default2.jpg");
    ui->PartDef_2->setPixmap(imgRect2.scaled(100,100));
    QPixmap imgRect3("default/part_default3.jpg");
    ui->PartDef_3->setPixmap(imgRect3.scaled(100,100));
    QPixmap imgRect4("default/part_default4.jpg");
    ui->PartDef_4->setPixmap(imgRect4.scaled(100,100));
    QPixmap imgRect5("default/part_default5.jpg");
    ui->PartDef_5->setPixmap(imgRect5.scaled(100,100));
    QPixmap imgRect6("default/part_default6.jpg");
    ui->PartDef_6->setPixmap(imgRect6.scaled(100,100));
    QPixmap imgRect7("default/part_default7.jpg");
    ui->PartDef_7->setPixmap(imgRect7.scaled(100,100));
    QPixmap imgRect8("default/part_default8.jpg");
    ui->PartDef_8->setPixmap(imgRect8.scaled(100,100));
    QPixmap imgRect9("default/part_default9.jpg");
    ui->PartDef_9->setPixmap(imgRect9.scaled(100,100));

    FILE *load_data;
    load_data = fopen("default/labels.txt", "r");
    for(int j=0; j<num_max_default; j++){
        const char *c_label;
        string read_part_label = "Part ";
        stringstream read_num_part;
        read_num_part << j+1;
        read_part_label = read_part_label + read_num_part.str() + " = %s \n";
        c_label = read_part_label.c_str();
        fscanf(load_data, c_label, &label_part_def[j]);
    }
    fclose(load_data);

    //Clear name parts - default
    ui->NameDef_1->clear();
    ui->NameDef_2->clear();
    ui->NameDef_3->clear();
    ui->NameDef_4->clear();
    ui->NameDef_5->clear();
    ui->NameDef_6->clear();
    ui->NameDef_7->clear();
    ui->NameDef_8->clear();
    ui->NameDef_9->clear();

    //Names parts - default
    if(!imgRect1.isNull())
        ui->NameDef_1->setText(label_part_def[0]);
    if(!imgRect2.isNull())
        ui->NameDef_2->setText(label_part_def[1]);
    if(!imgRect3.isNull())
        ui->NameDef_3->setText(label_part_def[2]);
    if(!imgRect4.isNull())
        ui->NameDef_4->setText(label_part_def[3]);
    if(!imgRect5.isNull())
        ui->NameDef_5->setText(label_part_def[4]);
    if(!imgRect6.isNull())
        ui->NameDef_6->setText(label_part_def[5]);
    if(!imgRect7.isNull())
        ui->NameDef_7->setText(label_part_def[6]);
    if(!imgRect8.isNull())
        ui->NameDef_8->setText(label_part_def[7]);
    if(!imgRect9.isNull())
        ui->NameDef_9->setText(label_part_def[8]);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::LoadDefault_compare(){

    ConfigInputs configInputs;

    float avg_size_def = 0.0;
    int num_obj = 0;

    string textInfo;
    stringstream text_size;
    text_size << configInputs.size_part;
    textInfo = "Tamanho padrão: " + text_size.str() + "mm \n";
    ui->TelaInfo->appendPlainText(textInfo.c_str());

    for(int i=0; i<num_max_default; i++){
        string file_name_number = "default/part_default";
        stringstream num_picture;
        num_picture << i+1;
        file_name_number = file_name_number + num_picture.str() + ".jpg";

        const char *file_name_test = file_name_number.c_str();
        FILE *file_test;
        file_test = fopen(file_name_test, "r");
        if(!file_test){
            color_def[i] = Scalar(0,0,0);
            string textInfo;
            stringstream text_part;
            text_part << i+1;
            textInfo = "Padrão " + text_part.str() + ": "  + "não encontrado";
            ui->TelaInfo->appendPlainText(textInfo.c_str());
            fclose(file_test);
        }
        else{
            imgLoad = imread(file_name_number);
            color_def[i] = ImgAvgColor(imgLoad);
            avg_size_def = (2.*configInputs.size_part/((imgLoad.rows+imgLoad.cols)/2.));
            ratio_part = ratio_part+avg_size_def;
            num_obj++;
            string textInfo;
            stringstream text_part, text_color;
            text_part << i+1;
            text_color << color_def[i];
            textInfo = "Padrão " + text_part.str() + ": Cor média "  + text_color.str();
            ui->TelaInfo->appendPlainText(textInfo.c_str());

            fclose(file_test);
        }
    }
    if(num_obj != 0)
        ratio_part = ratio_part/num_obj;

    ui->TelaInfo->appendPlainText("\n");
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
                color_test = color_diff[3];
                label_part = '\0';
                label_part = label_part_def[i];
                color_result = Scalar(0,255,0);
            }
        }
    }

    if(color_result != Scalar(0,255,0))
        color_result = Scalar(0,0,255);

    return color_result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SnapDefault(Mat imgPart){

    press_times++;

    string file_name_number = "temp/part_default";
    stringstream num_picture;
    num_picture << press_times;
    file_name_number = file_name_number + num_picture.str() + ".jpg";
    imwrite(file_name_number, imgPart);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ACTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_actionSair_triggered(){

    cap1.release();
    cap2.release();
    ui->statusBar->showMessage("End of image processing!");

    close();
}

void MainWindow::on_actionIniciar_triggered(){

    if(bot_reinit == false){
        SetInput setInput;
        setInput.setModal(true);
        setInput.exec();

        cap1_name = (setInput.capture1).toStdString();
        cap2_name = (setInput.capture2).toStdString();
    }
    bot_reinit = false;

    if(cap1_name == "CANCELED")
        return;
    else if(cap1_name == "USB0")
        cap1.open(0);
    else
        cap1.open(cap1_name);

    if(cap2_name == "CANCELED")
        return;
    else if(cap2_name == "USB2")
        cap2.open(2);
    else
        cap2.open(cap2_name);

    ui->ScreenResult_1->clear();
    ui->ScreenResult_2->clear();
    ui->TelaInfo->clear();
    ui->TelaInfo_2->clear();
    ui->label_good->clear();
    ui->label_bad->clear();
    ui->label_nodef->clear();
    ui->label_objects->clear();
    ui->label_objects_2->clear();

    LoadDefault();

    timer = new QTimer(this);

    if(!cap1.isOpened()){
        ui->ScreenResult_1->setText("Camera 1 não está conectada ou o vídeo não foi encontrado!\n");
        cap1.release();
        cap2.release();
    }
    if(!cap2.isOpened()){
        ui->ScreenResult_2->setText("Camera 2 não está conectada ou o vídeo não foi encontrado!\n");
        cap2.release();
        cap1.release();
    }
    if(cap1.isOpened() && cap2.isOpened()){
        key_pause = 0;
        first_check = 1;
        if(first_connect == 1)
            connect(timer, SIGNAL(timeout()), this, SLOT(MainProcess()));//Process loop
        timer->start(20);
        ui->statusBar->showMessage("Processamento iniciado com sucesso!");
        first_connect = 0;
    }
}

void MainWindow::on_actionPararContinuar_triggered(){

    if(!img1.empty() || !img2.empty()){
        if(key_pause == false)
            key_pause = true;

        else if(key_pause == true)
            key_pause = false;
    }
}

void MainWindow::on_actionCaptura_da_tela_triggered(){

    Mat img_cvt;
    QString filename;

    if(!img1.empty()){
        //Save image camera 1
        filename = QFileDialog::getSaveFileName(
                    this,
                    tr("Salvar arquivo câmera 1"),
                    "Img1.jpg",
                    tr("JPEG (*jpg)"));
        if(!filename.isEmpty()){
            cvtColor(img1, img_cvt, COLOR_RGB2BGR);
            imwrite(filename.toStdString(), img_cvt);
        }
    }

    if(!img2.empty()){
        //Save image camera 2
        filename = QFileDialog::getSaveFileName(
                    this,
                    tr("Salvar arquivo câmera 2"),
                    "Img2.jpg",
                    tr("JPEG (*jpg)"));
        if(!filename.isEmpty()){
            cvtColor(img2, img_cvt, COLOR_RGB2BGR);
            imwrite(filename.toStdString(), img_cvt);
        }
    }
    if(img1.empty() || img2.empty()){
        QMessageBox::information(this,
                          tr("Captura vazia"),
                          tr("Sem imagens para salvar!"));
    }
}

void MainWindow::on_actionConfigura_es_de_entrada_triggered(){

    ConfigInputs configInputs;
    configInputs.setModal(true);
    configInputs.exec();

    if(configInputs.bot_ok == 1){
        first_check = 1;
    }
}

void MainWindow::on_actionConfigura_es_de_processamento_triggered(){

    bool pause_test;

    imwrite("temp/img1Original.jpg", img1Capture);
    imwrite("temp/img2Original.jpg", img2Capture);
    imwrite("temp/imgMask.jpg", img2Mask);
    imwrite("temp/img1Background.jpg", img1Backg);
    imwrite("temp/img2Background.jpg", img2Backg);

    if(key_pause == 1)
        pause_test = 1;

    key_pause = 1;

    ConfigProcess configProcess;
    configProcess.setModal(true);
    configProcess.showMaximized();
    configProcess.exec();

    remove("temp/img1Original.jpg");
    remove("temp/img2Original.jpg");
    remove("temp/img1Background.jpg");
    remove("temp/img2Background.jpg");
    remove("temp/imgMask.jpg");

    LoadConfigProcess();

    if(pause_test == 0)
        key_pause = 0;

}

void MainWindow::on_actionAdicionar_pe_as_padr_es_triggered(){

    if(!img1.empty() && !img2.empty()){
        key = ' ';
    }
    else{
        qDebug()<<"teste";

        AddPartDefault addPartDef;
        addPartDef.setModal(true);
        addPartDef.show();
        addPartDef.exec();

        LoadDefault();
    }
}
void MainWindow::on_actionSobre_triggered(){

    InfoAbout infoAbout;
    infoAbout.setModal(true);
    infoAbout.show();
    infoAbout.exec();
}
void MainWindow::on_actionReiniciar_triggered(){

    if(!img1.empty() || !img2.empty()){
        bot_reinit = true;

        on_actionEncerrar_triggered();
        on_actionIniciar_triggered();
    }
}
void MainWindow::on_actionEncerrar_triggered(){

    if(!img1.empty()){
        cap1.release();
        img1.release();
    }

    if(!img2.empty()){
        cap2.release();
        img2.release();
    }

    if(!bot_reinit){
        cap1_name = '\0';
        cap2_name = '\0';
    }

    ui->ScreenResult_1->clear();
    ui->ScreenResult_2->clear();
    ui->TelaInfo->clear();
    ui->TelaInfo_2->clear();
    ui->label_good->clear();
    ui->label_bad->clear();
    ui->label_nodef->clear();
    ui->label_objects->clear();
    ui->label_objects_2->clear();

    LoadDefault();

    timer->stop();
    first_connect = 1;

    ui->statusBar->showMessage("Processamento encerrado!");

}
