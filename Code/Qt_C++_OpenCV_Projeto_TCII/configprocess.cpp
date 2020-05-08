#include "configprocess.h"
#include "ui_configprocess.h"
#include <QDebug>
#include <QApplication>
#include <QFileDialog>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#define pi 3.14159

using namespace cv;
using namespace std;

Mat mat1Original_copy, mat1Backg_copy, mat2Original_copy, mat2Backg_copy, mat2Mask_copy;
Mat mat1Original, mat1Backg, mat1Subt, mat1Proc, mat1Lim1, mat1Lim2, mat1LimSum, mat1Open, mat1Close;
Mat mat2Original, mat2Backg, mat2Subt, mat2Proc, mat2Lim1, mat2Lim2, mat2LimSum, mat2Open, mat2Close,
        mat2Mask;
QImage img1Original, img1Background, img1Subt, img1Process, img1Lim1, img1Lim2, img1LimSum, img1Open, img1Close;
QImage img2Original, img2Background, img2Subt, img2Process, img2Lim1, img2Lim2, img2LimSum, img2Open, img2Close, imgMask;
uchar bot_camera = 2;

//Variables settings
int C_size_Gaussian, C_size_Open, C_size_Close;
int C_size_Gaussian2, C_size_Open2, C_size_Close2;
int C_Rmin, C_Gmin, C_Bmin, C_Rmax, C_Gmax, C_Bmax, C_Rmin2, C_Gmin2, C_Bmin2, C_Rmax2, C_Gmax2, C_Bmax2;
int C_Rmin3, C_Gmin3, C_Bmin3, C_Rmax3, C_Gmax3, C_Bmax3, C_Rmin4, C_Gmin4, C_Bmin4, C_Rmax4, C_Gmax4, C_Bmax4;
float C_ratio_part = 0.0;

ConfigProcess::ConfigProcess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigProcess)
{
    ui->setupUi(this);

    mat1Original_copy = imread("temp/img1Original.jpg");
    mat1Backg_copy = imread("temp/img1Background.jpg");
    mat2Original_copy = imread("temp/img2Original.jpg");
    mat2Backg_copy = imread("temp/img2Background.jpg");
    mat2Mask_copy = imread("temp/imgMask.jpg");

    //Read info
    FILE *load_data;
    load_data = fopen("config/process.txt", "r");

    fscanf(load_data, "size_Gaussian = %d;\n", &C_size_Gaussian);
    fscanf(load_data, "size_Open = %d;\n", &C_size_Open);
    fscanf(load_data, "size_Close = %d;\n", &C_size_Close);

    fscanf(load_data, "size_Gaussian2 = %d;\n", &C_size_Gaussian2);
    fscanf(load_data, "size_Open2 = %d;\n", &C_size_Open2);
    fscanf(load_data, "size_Close2 = %d;\n", &C_size_Close2);

    fscanf(load_data, "Bmin = %d;\n", &C_Bmin);
    fscanf(load_data, "Gmin = %d;\n", &C_Gmin);
    fscanf(load_data, "Rmin = %d;\n", &C_Rmin);
    fscanf(load_data, "Bmax = %d;\n", &C_Bmax);
    fscanf(load_data, "Gmax = %d;\n", &C_Gmax);
    fscanf(load_data, "Rmax = %d;\n", &C_Rmax);

    fscanf(load_data, "Bmin2 = %d;\n", &C_Bmin2);
    fscanf(load_data, "Gmin2 = %d;\n", &C_Gmin2);
    fscanf(load_data, "Rmin2 = %d;\n", &C_Rmin2);
    fscanf(load_data, "Bmax2 = %d;\n", &C_Bmax2);
    fscanf(load_data, "Gmax2 = %d;\n", &C_Gmax2);
    fscanf(load_data, "Rmax2 = %d;\n", &C_Rmax2);

    fscanf(load_data, "Bmin3 = %d;\n", &C_Bmin3);
    fscanf(load_data, "Gmin3 = %d;\n", &C_Gmin3);
    fscanf(load_data, "Rmin3 = %d;\n", &C_Rmin3);
    fscanf(load_data, "Bmax3 = %d;\n", &C_Bmax3);
    fscanf(load_data, "Gmax3 = %d;\n", &C_Gmax3);
    fscanf(load_data, "Rmax3 = %d;\n", &C_Rmax3);

    fscanf(load_data, "Bmin4 = %d;\n", &C_Bmin4);
    fscanf(load_data, "Gmin4 = %d;\n", &C_Gmin4);
    fscanf(load_data, "Rmin4 = %d;\n", &C_Rmin4);
    fscanf(load_data, "Bmax4 = %d;\n", &C_Bmax4);
    fscanf(load_data, "Gmax4 = %d;\n", &C_Gmax4);
    fscanf(load_data, "Rmax4 = %d;\n", &C_Rmax4);

    if(C_ratio_part == 0.0)
        fscanf(load_data, "Ratio_part = %f; \n", &C_ratio_part);

    fclose(load_data);

    ui->label_Rmin->setNum(0);
    ui->label_Gmin->setNum(0);
    ui->label_Bmin->setNum(0);
    ui->label_Rmax->setNum(0);
    ui->label_Gmax->setNum(0);
    ui->label_Bmax->setNum(0);
    ui->label_Rmin2->setNum(0);
    ui->label_Gmin2->setNum(0);
    ui->label_Bmin2->setNum(0);
    ui->label_Rmax2->setNum(0);
    ui->label_Gmax2->setNum(0);
    ui->label_Bmax2->setNum(0);

    ui->bot_cam1->click();

}

ConfigProcess::~ConfigProcess()
{
    delete ui;
}

void ConfigProcess::MainProcess(int index){

    mat1Original_copy.copyTo(mat1Original);
    mat1Backg_copy.copyTo(mat1Backg);
    mat2Original_copy.copyTo(mat2Original);
    mat2Backg_copy.copyTo(mat2Backg);
    mat2Mask_copy.copyTo(mat2Mask);

    if(bot_camera == 0){
        ///PRE-PROCESSING
        //Do a simple background subtraction
        absdiff(mat1Original, mat1Backg, mat1Subt);
        ///Low-pass filters
        GaussianBlur(mat1Subt, mat1Proc, Size(C_size_Gaussian,C_size_Gaussian), 0, 0, BORDER_DEFAULT);

        ///SEGMENTATION
        //THRESHOLD BY COLOR
        inRange(mat1Proc, Scalar(C_Bmin, C_Gmin, C_Rmin), Scalar(C_Bmax, C_Gmax, C_Rmax), mat1Lim1);
        inRange(mat1Proc, Scalar(C_Bmin2, C_Gmin2, C_Rmin2), Scalar(C_Bmax2, C_Gmax2, C_Rmax2), mat1Lim2);
        add(mat1Lim1, mat1Lim2, mat1LimSum);

        //DILATION AND EROSION
        //Apply opening that is erosion followed by dilation to to remove noise
        morphologyEx(mat1LimSum, mat1Open, MORPH_OPEN, Mat(), Point(-1,-1), C_size_Open, BORDER_DEFAULT);
        //Apply closing that is dilation followed by erosion to fill the holes
        morphologyEx(mat1Open, mat1Close, MORPH_CLOSE, Mat(), Point(-1,-1), C_size_Close, BORDER_DEFAULT);
        //dilate(img1Segm, img1Segm, Mat(), Point(-1,-1), 2, BORDER_DEFAULT);
        erode(mat1Close, mat1Close, Mat(), Point(-1,-1), 3, BORDER_DEFAULT);

        //Convert Mats to QImages
        cvtColor(mat1Original, mat1Original, COLOR_BGR2RGB);
        cv::resize(mat1Original, mat1Original, Size(550,412), 0, 0, INTER_CUBIC);
        img1Original = QImage((uchar*) mat1Original.data, mat1Original.cols,
                                           mat1Original.rows, mat1Original.step, QImage::Format_RGB888);
        cvtColor(mat1Backg, mat1Backg, COLOR_BGR2RGB);
        cv::resize(mat1Backg, mat1Backg, Size(550,412), 0, 0, INTER_CUBIC);
        img1Background = QImage((uchar*) mat1Backg.data, mat1Backg.cols,
                                           mat1Backg.rows, mat1Backg.step, QImage::Format_RGB888);
        cvtColor(mat1Subt, mat1Subt, COLOR_BGR2RGB);
        cv::resize(mat1Subt, mat1Subt, Size(550,412), 0, 0, INTER_CUBIC);
        img1Subt = QImage((uchar*) mat1Subt.data, mat1Subt.cols,
                                           mat1Subt.rows, mat1Subt.step, QImage::Format_RGB888);
        cvtColor(mat1Proc, mat1Proc, COLOR_BGR2RGB);
        cv::resize(mat1Proc, mat1Proc, Size(550,412), 0, 0, INTER_CUBIC);
        img1Process = QImage((uchar*) mat1Proc.data, mat1Proc.cols,
                                           mat1Proc.rows, mat1Proc.step, QImage::Format_RGB888);
        cv::resize(mat1Lim1, mat1Lim1, Size(550,412), 0, 0, INTER_CUBIC);
        img1Lim1 = QImage((uchar*) mat1Lim1.data, mat1Lim1.cols,
                                           mat1Lim1.rows, mat1Lim1.step, QImage::Format_Indexed8);
        cv::resize(mat1Lim2, mat1Lim2, Size(550,412), 0, 0, INTER_CUBIC);
        img1Lim2 = QImage((uchar*) mat1Lim2.data, mat1Lim2.cols,
                                           mat1Lim2.rows, mat1Lim2.step, QImage::Format_Indexed8);
        cv::resize(mat1LimSum, mat1LimSum, Size(550,412), 0, 0, INTER_CUBIC);
        img1LimSum = QImage((uchar*) mat1LimSum.data, mat1LimSum.cols,
                                           mat1LimSum.rows, mat1LimSum.step, QImage::Format_Indexed8);
        cv::resize(mat1Open, mat1Open, Size(550,412), 0, 0, INTER_CUBIC);
        img1Open = QImage((uchar*) mat1Open.data, mat1Open.cols,
                                           mat1Open.rows, mat1Open.step, QImage::Format_Indexed8);
        cv::resize(mat1Close, mat1Close, Size(550,412), 0, 0, INTER_CUBIC);
        img1Close = QImage((uchar*) mat1Close.data, mat1Close.cols,
                                           mat1Close.rows, mat1Close.step, QImage::Format_Indexed8);

        if(index == 0)
            ui->label_Original->setPixmap(QPixmap::fromImage(img1Original));
        else if(index == 1)
        ui->label_Fundo->setPixmap(QPixmap::fromImage(img1Background));
        else if(index == 2)
        ui->label_Subt->setPixmap(QPixmap::fromImage(img1Subt));
        else if(index == 3)
        ui->label_Proc->setPixmap(QPixmap::fromImage(img1Process));
        else if(index == 4)
        ui->label_Limiar1->setPixmap(QPixmap::fromImage(img1Lim1));
        else if(index == 5)
        ui->label_Limiar2->setPixmap(QPixmap::fromImage(img1Lim2));
        else if(index == 6)
        ui->label_Soma->setPixmap(QPixmap::fromImage(img1LimSum));
        else if(index == 7)
        ui->label_Open->setPixmap(QPixmap::fromImage(img1Open));
        else if(index == 8)
        ui->label_Close->setPixmap(QPixmap::fromImage(img1Close));

        else if(index == 9)
        ui->label_Original_2->setPixmap(QPixmap::fromImage(img1Original));
        else if(index == 10)
        ui->label_Fundo_2->setPixmap(QPixmap::fromImage(img1Background));
        else if(index == 11)
        ui->label_Subt_2->setPixmap(QPixmap::fromImage(img1Subt));
        else if(index == 12)
        ui->label_Proc_2->setPixmap(QPixmap::fromImage(img1Process));
        else if(index == 13)
        ui->label_Limiar1_2->setPixmap(QPixmap::fromImage(img1Lim1));
        else if(index == 14)
        ui->label_Limiar2_2->setPixmap(QPixmap::fromImage(img1Lim2));
        else if(index == 15)
        ui->label_Soma_2->setPixmap(QPixmap::fromImage(img1LimSum));
        else if(index == 16)
        ui->label_Open_2->setPixmap(QPixmap::fromImage(img1Open));
        else if(index == 17)
        ui->label_Close_2->setPixmap(QPixmap::fromImage(img1Close));
    }

    if(bot_camera == 1){
        ///PRE-PROCESSING
        //Do a simple background subtraction
        absdiff(mat2Original, mat2Backg, mat2Subt);
        //Add the mask of limits
        mat2Subt.copyTo(mat2Proc, mat2Mask);
        ///Low-pass filters
        GaussianBlur(mat2Proc, mat2Proc, Size(C_size_Gaussian2,C_size_Gaussian2), 0, 0, BORDER_DEFAULT);

        ///SEGMENTATION
        //THRESHOLD BY COLOR
        inRange(mat2Proc, Scalar(C_Bmin3, C_Gmin3, C_Rmin3), Scalar(C_Bmax3, C_Gmax3, C_Rmax3), mat2Lim1);
        inRange(mat2Proc, Scalar(C_Bmin4, C_Gmin4, C_Rmin4), Scalar(C_Bmax4, C_Gmax4, C_Rmax4), mat2Lim2);
        add(mat2Lim1, mat2Lim2, mat2LimSum);

        //DILATION AND EROSION
        //Apply opening that is erosion followed by dilation to to remove noise
        morphologyEx(mat2LimSum, mat2Open, MORPH_OPEN, Mat(), Point(-1,-1), C_size_Open2, BORDER_DEFAULT);
        //Apply closing that is dilation followed by erosion to fill the holes
        morphologyEx(mat2Open, mat2Close, MORPH_CLOSE, Mat(), Point(-1,-1), C_size_Close2, BORDER_DEFAULT);
        //dilate(img1Segm, img1Segm, Mat(), Point(-1,-1), 2, BORDER_DEFAULT);
        erode(mat2Close, mat2Close, Mat(), Point(-1,-1), 3, BORDER_DEFAULT);

        //Convert Mats to QImages
        cvtColor(mat2Original, mat2Original, COLOR_BGR2RGB);
        cv::resize(mat2Original, mat2Original, Size(550,412), 0, 0, INTER_CUBIC);
        img2Original = QImage((uchar*) mat2Original.data, mat2Original.cols,
                                           mat2Original.rows, mat2Original.step, QImage::Format_RGB888);
        cvtColor(mat2Backg, mat2Backg, COLOR_BGR2RGB);
        cv::resize(mat2Backg, mat2Backg, Size(550,412), 0, 0, INTER_CUBIC);
        img2Background = QImage((uchar*) mat2Backg.data, mat2Backg.cols,
                                           mat2Backg.rows, mat2Backg.step, QImage::Format_RGB888);
        cvtColor(mat2Subt, mat2Subt, COLOR_BGR2RGB);
        cv::resize(mat2Subt, mat2Subt, Size(550,412), 0, 0, INTER_CUBIC);
        img2Subt = QImage((uchar*) mat2Subt.data, mat2Subt.cols,
                                           mat2Subt.rows, mat2Subt.step, QImage::Format_RGB888);
        cvtColor(mat2Proc, mat2Proc, COLOR_BGR2RGB);
        cv::resize(mat2Proc, mat2Proc, Size(550,412), 0, 0, INTER_CUBIC);
        img2Process = QImage((uchar*) mat2Proc.data, mat2Proc.cols,
                                           mat2Proc.rows, mat2Proc.step, QImage::Format_RGB888);
        cv::resize(mat2Lim1, mat2Lim1, Size(550,412), 0, 0, INTER_CUBIC);
        img2Lim1 = QImage((uchar*) mat2Lim1.data, mat2Lim1.cols,
                                           mat2Lim1.rows, mat2Lim1.step, QImage::Format_Indexed8);
        cv::resize(mat2Lim2, mat2Lim2, Size(550,412), 0, 0, INTER_CUBIC);
        img2Lim2 = QImage((uchar*) mat2Lim2.data, mat2Lim2.cols,
                                           mat2Lim2.rows, mat2Lim2.step, QImage::Format_Indexed8);
        cv::resize(mat2LimSum, mat2LimSum, Size(550,412), 0, 0, INTER_CUBIC);
        img2LimSum = QImage((uchar*) mat2LimSum.data, mat2LimSum.cols,
                                           mat2LimSum.rows, mat2LimSum.step, QImage::Format_Indexed8);
        cv::resize(mat2Open, mat2Open, Size(550,412), 0, 0, INTER_CUBIC);
        img2Open = QImage((uchar*) mat2Open.data, mat2Open.cols,
                                           mat2Open.rows, mat2Open.step, QImage::Format_Indexed8);
        cv::resize(mat2Close, mat2Close, Size(550,412), 0, 0, INTER_CUBIC);
        img2Close = QImage((uchar*) mat2Close.data, mat2Close.cols,
                                           mat2Close.rows, mat2Close.step, QImage::Format_Indexed8);

        if(index == 0)
            ui->label_Original->setPixmap(QPixmap::fromImage(img2Original));
        else if(index == 1)
        ui->label_Fundo->setPixmap(QPixmap::fromImage(img2Background));
        else if(index == 2)
        ui->label_Subt->setPixmap(QPixmap::fromImage(img2Subt));
        else if(index == 3)
        ui->label_Proc->setPixmap(QPixmap::fromImage(img2Process));
        else if(index == 4)
        ui->label_Limiar1->setPixmap(QPixmap::fromImage(img2Lim1));
        else if(index == 5)
        ui->label_Limiar2->setPixmap(QPixmap::fromImage(img2Lim2));
        else if(index == 6)
        ui->label_Soma->setPixmap(QPixmap::fromImage(img2LimSum));
        else if(index == 7)
        ui->label_Open->setPixmap(QPixmap::fromImage(img2Open));
        else if(index == 8)
        ui->label_Close->setPixmap(QPixmap::fromImage(img2Close));

        if(index == 9)
        ui->label_Original_2->setPixmap(QPixmap::fromImage(img2Original));
        else if(index == 10)
        ui->label_Fundo_2->setPixmap(QPixmap::fromImage(img2Background));
        else if(index == 11)
        ui->label_Subt_2->setPixmap(QPixmap::fromImage(img2Subt));
        else if(index == 12)
        ui->label_Proc_2->setPixmap(QPixmap::fromImage(img2Process));
        else if(index == 13)
        ui->label_Limiar1_2->setPixmap(QPixmap::fromImage(img2Lim1));
        else if(index == 14)
        ui->label_Limiar2_2->setPixmap(QPixmap::fromImage(img2Lim2));
        else if(index == 15)
        ui->label_Soma_2->setPixmap(QPixmap::fromImage(img2LimSum));
        else if(index == 16)
        ui->label_Open_2->setPixmap(QPixmap::fromImage(img2Open));
        else if(index == 17)
        ui->label_Close_2->setPixmap(QPixmap::fromImage(img2Close));

    }

}

void ConfigProcess::on_tabWidget_currentChanged(int index)
{
    UpdateProcess();
}

void ConfigProcess::on_tabWidget_2_currentChanged(int index)
{
    UpdateProcess();
}

void ConfigProcess::on_bot_cam1_clicked()
{
    bot_camera = 0;

    if(C_size_Gaussian == 1)
        ui->filter1->click();
    else if(C_size_Gaussian == 3)
        ui->filter3->click();
    else if(C_size_Gaussian == 5)
        ui->filter5->click();
    else if(C_size_Gaussian == 7)
        ui->filter7->click();
    else if(C_size_Gaussian == 9)
        ui->filter9->click();
    else if(C_size_Gaussian == 11)
        ui->filter11->click();
    else if(C_size_Gaussian == 13)
        ui->filter13->click();
    else if(C_size_Gaussian == 15)
        ui->filter15->click();
    else if(C_size_Gaussian == 17)
        ui->filter17->click();
    else if(C_size_Gaussian == 19)
        ui->filter19->click();
    else if(C_size_Gaussian == 21)
        ui->filter21->click();
    else if(C_size_Gaussian == 23)
        ui->filter23->click();

    if(C_size_Open == 1)
        ui->open1->click();
    else if(C_size_Open == 2)
        ui->open2->click();
    else if(C_size_Open == 3)
        ui->open3->click();
    else if(C_size_Open == 4)
        ui->open4->click();
    else if(C_size_Open == 5)
        ui->open5->click();
    else if(C_size_Open == 6)
        ui->open6->click();
    else if(C_size_Open == 7)
        ui->open7->click();
    else if(C_size_Open == 8)
        ui->open8->click();
    else if(C_size_Open == 9)
        ui->open9->click();
    else if(C_size_Open == 10)
        ui->open10->click();
    else if(C_size_Open == 11)
        ui->open11->click();
    else if(C_size_Open == 12)
        ui->open12->click();

    if(C_size_Close == 1)
        ui->close1->click();
    else if(C_size_Close == 2)
        ui->close2->click();
    else if(C_size_Close == 3)
        ui->close3->click();
    else if(C_size_Close == 4)
        ui->close4->click();
    else if(C_size_Close == 5)
        ui->close5->click();
    else if(C_size_Close == 6)
        ui->close6->click();
    else if(C_size_Close == 7)
        ui->close7->click();
    else if(C_size_Close == 8)
        ui->close8->click();
    else if(C_size_Close == 9)
        ui->close9->click();
    else if(C_size_Close == 10)
        ui->close10->click();
    else if(C_size_Close == 11)
        ui->close11->click();
    else if(C_size_Close == 12)
        ui->close12->click();

    ui->Slider_Rmin->setValue(C_Rmin);
    ui->Slider_Gmin->setValue(C_Gmin);
    ui->Slider_Bmin->setValue(C_Bmin);
    ui->Slider_Rmax->setValue(C_Rmax);
    ui->Slider_Gmax->setValue(C_Gmax);
    ui->Slider_Bmax->setValue(C_Bmax);
    ui->Slider_Rmin_2->setValue(C_Rmin2);
    ui->Slider_Gmin_2->setValue(C_Gmin2);
    ui->Slider_Bmin_2->setValue(C_Bmin2);
    ui->Slider_Rmax_2->setValue(C_Rmax2);
    ui->Slider_Gmax_2->setValue(C_Gmax2);
    ui->Slider_Bmax_2->setValue(C_Bmax2);

    UpdateProcess();

}

void ConfigProcess::on_bot_cam2_clicked()
{
    bot_camera = 1;

    if(C_size_Gaussian2 == 1)
        ui->filter1->click();
    else if(C_size_Gaussian2 == 3)
        ui->filter3->click();
    else if(C_size_Gaussian2 == 5)
        ui->filter5->click();
    else if(C_size_Gaussian2 == 7)
        ui->filter7->click();
    else if(C_size_Gaussian2 == 9)
        ui->filter9->click();
    else if(C_size_Gaussian2 == 11)
        ui->filter11->click();
    else if(C_size_Gaussian2 == 13)
        ui->filter13->click();
    else if(C_size_Gaussian2 == 15)
        ui->filter15->click();
    else if(C_size_Gaussian2 == 17)
        ui->filter17->click();
    else if(C_size_Gaussian2 == 19)
        ui->filter19->click();
    else if(C_size_Gaussian2 == 21)
        ui->filter21->click();
    else if(C_size_Gaussian2 == 23)
        ui->filter23->click();

    if(C_size_Open2 == 1)
        ui->open1->click();
    else if(C_size_Open2 == 2)
        ui->open2->click();
    else if(C_size_Open2 == 3)
        ui->open3->click();
    else if(C_size_Open2 == 4)
        ui->open4->click();
    else if(C_size_Open2 == 5)
        ui->open5->click();
    else if(C_size_Open2 == 6)
        ui->open6->click();
    else if(C_size_Open2 == 7)
        ui->open7->click();
    else if(C_size_Open2 == 8)
        ui->open8->click();
    else if(C_size_Open2 == 9)
        ui->open9->click();
    else if(C_size_Open2 == 10)
        ui->open10->click();
    else if(C_size_Open2 == 11)
        ui->open11->click();
    else if(C_size_Open2 == 12)
        ui->open12->click();

    if(C_size_Close2 == 1)
        ui->close1->click();
    else if(C_size_Close2 == 2)
        ui->close2->click();
    else if(C_size_Close2 == 3)
        ui->close3->click();
    else if(C_size_Close2 == 4)
        ui->close4->click();
    else if(C_size_Close2 == 5)
        ui->close5->click();
    else if(C_size_Close2 == 6)
        ui->close6->click();
    else if(C_size_Close2 == 7)
        ui->close7->click();
    else if(C_size_Close2 == 8)
        ui->close8->click();
    else if(C_size_Close2 == 9)
        ui->close9->click();
    else if(C_size_Close2 == 10)
        ui->close10->click();
    else if(C_size_Close2 == 11)
        ui->close11->click();
    else if(C_size_Close2 == 12)
        ui->close12->click();

    ui->Slider_Rmin->setValue(C_Rmin3);
    ui->Slider_Gmin->setValue(C_Gmin3);
    ui->Slider_Bmin->setValue(C_Bmin3);
    ui->Slider_Rmax->setValue(C_Rmax3);
    ui->Slider_Gmax->setValue(C_Gmax3);
    ui->Slider_Bmax->setValue(C_Bmax3);
    ui->Slider_Rmin_2->setValue(C_Rmin4);
    ui->Slider_Gmin_2->setValue(C_Gmin4);
    ui->Slider_Bmin_2->setValue(C_Bmin4);
    ui->Slider_Rmax_2->setValue(C_Rmax4);
    ui->Slider_Gmax_2->setValue(C_Gmax4);
    ui->Slider_Bmax_2->setValue(C_Bmax4);

    UpdateProcess();

}

void ConfigProcess::on_bot_Default_clicked()
{
    C_size_Gaussian = 3;
    C_size_Open = 1;
    C_size_Close = 7;

    C_size_Gaussian2 = 3;
    C_size_Open2 = 1;
    C_size_Close2 = 8;

    C_Rmin = 0;        C_Rmax = 255;
    C_Gmin = 45;       C_Gmax = 255;
    C_Bmin = 0;        C_Bmax = 255;

    C_Rmin2 = 0 ;      C_Rmax2 = 86;
    C_Gmin2 = 0;       C_Gmax2 = 26;
    C_Bmin2 = 54;      C_Bmax2 = 177;

    C_Rmin3 = 0;       C_Rmax3 = 96;
    C_Gmin3 = 86;      C_Gmax3 = 159;
    C_Bmin3 = 0;       C_Bmax3 = 255;

    C_Rmin4 = 0;       C_Rmax4 = 123;
    C_Gmin4 = 0;       C_Gmax4 = 53;
    C_Bmin4 = 81;      C_Bmax4 = 245;


    if(bot_camera == 0){

        ui->filter3->click();
        ui->open1->click();
        ui->close7->click();

        ui->Slider_Rmin->setValue(C_Rmin);
        ui->Slider_Gmin->setValue(C_Gmin);
        ui->Slider_Bmin->setValue(C_Bmin);
        ui->Slider_Rmax->setValue(C_Rmax);
        ui->Slider_Gmax->setValue(C_Gmax);
        ui->Slider_Bmax->setValue(C_Bmax);
        ui->Slider_Rmin_2->setValue(C_Rmin2);
        ui->Slider_Gmin_2->setValue(C_Gmin2);
        ui->Slider_Bmin_2->setValue(C_Bmin2);
        ui->Slider_Rmax_2->setValue(C_Rmax2);
        ui->Slider_Gmax_2->setValue(C_Gmax2);
        ui->Slider_Bmax_2->setValue(C_Bmax2);

    }
    if(bot_camera == 1){

        ui->filter3->click();
        ui->open1->click();
        ui->close8->click();

        ui->Slider_Rmin->setValue(C_Rmin3);
        ui->Slider_Gmin->setValue(C_Gmin3);
        ui->Slider_Bmin->setValue(C_Bmin3);
        ui->Slider_Rmax->setValue(C_Rmax3);
        ui->Slider_Gmax->setValue(C_Gmax3);
        ui->Slider_Bmax->setValue(C_Bmax3);
        ui->Slider_Rmin_2->setValue(C_Rmin4);
        ui->Slider_Gmin_2->setValue(C_Gmin4);
        ui->Slider_Bmin_2->setValue(C_Bmin4);
        ui->Slider_Rmax_2->setValue(C_Rmax4);
        ui->Slider_Gmax_2->setValue(C_Gmax4);
        ui->Slider_Bmax_2->setValue(C_Bmax4);

    }

    UpdateProcess();

}

//Select values
void ConfigProcess::on_filter1_clicked()
{
    if(bot_camera == 0)
        C_size_Gaussian = 1;
    if(bot_camera == 1)
        C_size_Gaussian2 = 1;

    UpdateProcess();

}

void ConfigProcess::on_filter3_clicked()
{
    if(bot_camera == 0)
        C_size_Gaussian = 3;
    if(bot_camera == 1)
        C_size_Gaussian2 = 3;

    UpdateProcess();

}

void ConfigProcess::on_filter5_clicked()
{
    if(bot_camera == 0)
        C_size_Gaussian = 5;
    if(bot_camera == 1)
        C_size_Gaussian2 = 5;

    UpdateProcess();

}

void ConfigProcess::on_filter7_clicked()
{
    if(bot_camera == 0)
        C_size_Gaussian = 7;
    if(bot_camera == 1)
        C_size_Gaussian2 = 7;

    UpdateProcess();

}

void ConfigProcess::on_filter9_clicked()
{
    if(bot_camera == 0)
        C_size_Gaussian = 9;
    if(bot_camera == 1)
        C_size_Gaussian2 = 9;

    UpdateProcess();

}

void ConfigProcess::on_filter11_clicked()
{
    if(bot_camera == 0)
        C_size_Gaussian = 11;
    if(bot_camera == 1)
        C_size_Gaussian2 = 11;

    UpdateProcess();

}

void ConfigProcess::on_filter13_clicked()
{
    if(bot_camera == 0)
        C_size_Gaussian = 13;
    if(bot_camera == 1)
        C_size_Gaussian2 = 13;

    UpdateProcess();

}

void ConfigProcess::on_filter15_clicked()
{
    if(bot_camera == 0)
        C_size_Gaussian = 15;
    if(bot_camera == 1)
        C_size_Gaussian2 = 15;

    UpdateProcess();

}

void ConfigProcess::on_filter17_clicked()
{
    if(bot_camera == 0)
        C_size_Gaussian = 17;
    if(bot_camera == 1)
        C_size_Gaussian2 = 17;

    UpdateProcess();

}

void ConfigProcess::on_filter19_clicked()
{
    if(bot_camera == 0)
        C_size_Gaussian = 19;
    if(bot_camera == 1)
        C_size_Gaussian2 = 19;

    UpdateProcess();

}

void ConfigProcess::on_filter21_clicked()
{
    if(bot_camera == 0)
        C_size_Gaussian = 21;
    if(bot_camera == 1)
        C_size_Gaussian2 = 21;

    UpdateProcess();

}

void ConfigProcess::on_filter23_clicked()
{
    if(bot_camera == 0)
        C_size_Gaussian = 23;
    if(bot_camera == 1)
        C_size_Gaussian2 = 23;

    UpdateProcess();

}

void ConfigProcess::on_open1_clicked()
{
    if(bot_camera == 0)
        C_size_Open = 1;
    if(bot_camera == 1)
        C_size_Open2 = 1;

    UpdateProcess();

}

void ConfigProcess::on_open2_clicked()
{
    if(bot_camera == 0)
        C_size_Open = 2;
    if(bot_camera == 1)
        C_size_Open2 = 2;

    UpdateProcess();

}

void ConfigProcess::on_open3_clicked()
{
    if(bot_camera == 0)
        C_size_Open = 3;
    if(bot_camera == 1)
        C_size_Open2 = 3;

    UpdateProcess();

}

void ConfigProcess::on_open4_clicked()
{
    if(bot_camera == 0)
        C_size_Open = 4;
    if(bot_camera == 1)
        C_size_Open2 = 4;

    UpdateProcess();

}

void ConfigProcess::on_open5_clicked()
{
    if(bot_camera == 0)
        C_size_Open = 5;
    if(bot_camera == 1)
        C_size_Open2 = 5;

    UpdateProcess();

}

void ConfigProcess::on_open6_clicked()
{
    if(bot_camera == 0)
        C_size_Open = 6;
    if(bot_camera == 1)
        C_size_Open2 = 6;

    UpdateProcess();

}

void ConfigProcess::on_open7_clicked()
{
    if(bot_camera == 0)
        C_size_Open = 7;
    if(bot_camera == 1)
        C_size_Open2 = 7;

    UpdateProcess();

}

void ConfigProcess::on_open8_clicked()
{
    if(bot_camera == 0)
        C_size_Open = 8;
    if(bot_camera == 1)
        C_size_Open2 = 8;

    UpdateProcess();

}

void ConfigProcess::on_open9_clicked()
{
    if(bot_camera == 0)
        C_size_Open = 9;
    if(bot_camera == 1)
        C_size_Open2 = 9;

    UpdateProcess();

}

void ConfigProcess::on_open10_clicked()
{
    if(bot_camera == 0)
        C_size_Open = 10;
    if(bot_camera == 1)
        C_size_Open2 = 10;

    UpdateProcess();

}

void ConfigProcess::on_open11_clicked()
{
    if(bot_camera == 0)
        C_size_Open = 11;
    if(bot_camera == 1)
        C_size_Open2 = 11;

    UpdateProcess();

}

void ConfigProcess::on_open12_clicked()
{
    if(bot_camera == 0)
        C_size_Open = 12;
    if(bot_camera == 1)
        C_size_Open2 = 12;

    UpdateProcess();

}

void ConfigProcess::on_close1_clicked()
{
    if(bot_camera == 0)
        C_size_Close = 1;
    if(bot_camera == 1)
        C_size_Close2 = 1;

    UpdateProcess();

}

void ConfigProcess::on_close2_clicked()
{
    if(bot_camera == 0)
        C_size_Close = 2;
    if(bot_camera == 1)
        C_size_Close2 = 2;

    UpdateProcess();

}

void ConfigProcess::on_close3_clicked()
{
    if(bot_camera == 0)
        C_size_Close = 3;
    if(bot_camera == 1)
        C_size_Close2 = 3;

    UpdateProcess();

}

void ConfigProcess::on_close4_clicked()
{
    if(bot_camera == 0)
        C_size_Close = 4;
    if(bot_camera == 1)
        C_size_Close2 = 4;

    UpdateProcess();

}

void ConfigProcess::on_close5_clicked()
{
    if(bot_camera == 0)
        C_size_Close = 5;
    if(bot_camera == 1)
        C_size_Close2 = 5;

    UpdateProcess();

}

void ConfigProcess::on_close6_clicked()
{
    if(bot_camera == 0)
        C_size_Close = 6;
    if(bot_camera == 1)
        C_size_Close2 = 6;

    UpdateProcess();

}

void ConfigProcess::on_close7_clicked()
{
    if(bot_camera == 0)
        C_size_Close = 7;
    if(bot_camera == 1)
        C_size_Close2 = 7;

    UpdateProcess();

}

void ConfigProcess::on_close8_clicked()
{
    if(bot_camera == 0)
        C_size_Close = 8;
    if(bot_camera == 1)
        C_size_Close2 = 8;

    UpdateProcess();

}

void ConfigProcess::on_close9_clicked()
{
    if(bot_camera == 0)
        C_size_Close = 9;
    if(bot_camera == 1)
        C_size_Close2 = 9;

    UpdateProcess();

}

void ConfigProcess::on_close10_clicked()
{
    if(bot_camera == 0)
        C_size_Close = 10;
    if(bot_camera == 1)
        C_size_Close2 = 10;

    UpdateProcess();

}

void ConfigProcess::on_close11_clicked()
{
    if(bot_camera == 0)
        C_size_Close = 11;
    if(bot_camera == 1)
        C_size_Close2 = 11;

    UpdateProcess();

}

void ConfigProcess::on_close12_clicked()
{
    if(bot_camera == 0)
        C_size_Close = 12;
    if(bot_camera == 1)
        C_size_Close2 = 12;

    UpdateProcess();

}

void ConfigProcess::on_Slider_Rmin_valueChanged(int value)
{
    if(bot_camera == 0)
        C_Rmin = value;
    if(bot_camera == 1)
        C_Rmin3 = value;

    UpdateProcess();

}

void ConfigProcess::on_Slider_Gmin_valueChanged(int value)
{
    if(bot_camera == 0)
        C_Gmin = value;
    if(bot_camera == 1)
        C_Gmin3 = value;

    UpdateProcess();

}

void ConfigProcess::on_Slider_Bmin_valueChanged(int value)
{
    if(bot_camera == 0)
        C_Bmin = value;
    if(bot_camera == 1)
        C_Bmin3 = value;

    UpdateProcess();

}

void ConfigProcess::on_Slider_Rmax_valueChanged(int value)
{
    if(bot_camera == 0)
        C_Rmax = value;
    if(bot_camera == 1)
        C_Rmax3 = value;

    UpdateProcess();

}


void ConfigProcess::on_Slider_Gmax_valueChanged(int value)
{
    if(bot_camera == 0)
        C_Gmax = value;
    if(bot_camera == 1)
        C_Gmax3 = value;

    UpdateProcess();

}

void ConfigProcess::on_Slider_Bmax_valueChanged(int value)
{
    if(bot_camera == 0)
        C_Bmax = value;
    if(bot_camera == 1)
        C_Bmax3 = value;

    UpdateProcess();

}

void ConfigProcess::on_Slider_Rmin_2_valueChanged(int value)
{
    if(bot_camera == 0)
        C_Rmin2 = value;
    if(bot_camera == 1)
        C_Rmin4 = value;

    UpdateProcess();

}

void ConfigProcess::on_Slider_Gmin_2_valueChanged(int value)
{
    if(bot_camera == 0)
        C_Gmin2 = value;
    if(bot_camera == 1)
        C_Gmin4 = value;

    UpdateProcess();

}

void ConfigProcess::on_Slider_Bmin_2_valueChanged(int value)
{
    if(bot_camera == 0)
        C_Bmin2 = value;
    if(bot_camera == 1)
        C_Bmin4 = value;

    UpdateProcess();

}

void ConfigProcess::on_Slider_Rmax_2_valueChanged(int value)
{
    if(bot_camera == 0)
        C_Rmax2 = value;
    if(bot_camera == 1)
        C_Rmax4 = value;

    UpdateProcess();

}

void ConfigProcess::on_Slider_Gmax_2_valueChanged(int value)
{
    if(bot_camera == 0)
        C_Gmax2 = value;
    if(bot_camera == 1)
        C_Gmax4 = value;

    UpdateProcess();

}

void ConfigProcess::on_Slider_Bmax_2_valueChanged(int value)
{
    if(bot_camera == 0)
        C_Bmax2 = value;
    if(bot_camera == 1)
        C_Bmax4 = value;

    UpdateProcess();
}

void ConfigProcess::on_buttonBox_accepted()
{
    FILE *save_data;

    save_data = fopen("config/process.txt", "w");
    fprintf(save_data, "size_Gaussian = %d; \n", C_size_Gaussian);
    fprintf(save_data, "size_Open = %d; \n", C_size_Open);
    fprintf(save_data, "size_Close = %d; \n", C_size_Close);

    fprintf(save_data, "size_Gaussian2 = %d; \n", C_size_Gaussian2);
    fprintf(save_data, "size_Open2 = %d; \n", C_size_Open2);
    fprintf(save_data, "size_Close2 = %d; \n", C_size_Close2);

    fprintf(save_data, "Bmin = %d; \n", C_Bmin);
    fprintf(save_data, "Gmin = %d; \n", C_Gmin);
    fprintf(save_data, "Rmin = %d; \n", C_Rmin);
    fprintf(save_data, "Bmax = %d; \n", C_Bmax);
    fprintf(save_data, "Gmax = %d; \n", C_Gmax);
    fprintf(save_data, "Rmax = %d; \n", C_Rmax);

    fprintf(save_data, "Bmin2 = %d; \n", C_Bmin2);
    fprintf(save_data, "Gmin2 = %d; \n", C_Gmin2);
    fprintf(save_data, "Rmin2 = %d; \n", C_Rmin2);
    fprintf(save_data, "Bmax2 = %d; \n", C_Bmax2);
    fprintf(save_data, "Gmax2 = %d; \n", C_Gmax2);
    fprintf(save_data, "Rmax2 = %d; \n", C_Rmax2);

    fprintf(save_data, "Bmin3 = %d; \n", C_Bmin3);
    fprintf(save_data, "Gmin3 = %d; \n", C_Gmin3);
    fprintf(save_data, "Rmin3 = %d; \n", C_Rmin3);
    fprintf(save_data, "Bmax3 = %d; \n", C_Bmax3);
    fprintf(save_data, "Gmax3 = %d; \n", C_Gmax3);
    fprintf(save_data, "Rmax3 = %d; \n", C_Rmax3);

    fprintf(save_data, "Bmin4 = %d; \n", C_Bmin4);
    fprintf(save_data, "Gmin4 = %d; \n", C_Gmin4);
    fprintf(save_data, "Rmin4 = %d; \n", C_Rmin4);
    fprintf(save_data, "Bmax4 = %d; \n", C_Bmax4);
    fprintf(save_data, "Gmax4 = %d; \n", C_Gmax4);
    fprintf(save_data, "Rmax4 = %d; \n", C_Rmax4);

    fprintf(save_data, "Ratio_part = %.6f; \n", C_ratio_part);

    fclose(save_data);

    bot_camera = 2;
}

void ConfigProcess::UpdateProcess(){

    if(!mat1Original_copy.empty() || !mat1Backg_copy.empty()
        || !mat2Original_copy.empty() || !mat2Backg_copy.empty()
        || !mat2Mask_copy.empty()){
        MainProcess(ui->tabWidget->currentIndex());
        MainProcess(ui->tabWidget_2->currentIndex()+9);
    }
}
