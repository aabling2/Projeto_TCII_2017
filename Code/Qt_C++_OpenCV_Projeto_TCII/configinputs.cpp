#include "configinputs.h"
#include "ui_configinputs.h"

/*
#define num_max_parts   10              //Maximum number of parts to register in image
#define size_part 53                    //Real diameter of the part(millimeters)
#define mask_angle 73.5                 //Angle to make the lines in camera2 to align the conveyor
#define offset_line 26                  //Offset from the side of the image (pixels)
#define width_conveyor 297              //Width of the conveyor to use on reading at second camera (millimeters)
#define length_conveyor 510             //Length of the conveyor to use on reading at second camera (millimeters)
#define dist_ref 420                    //Distance between camera2 and end of length conveyor (millimeters)
#define dist_h 360                      //Height distance between camera2 and conveyor (millimeters)
#define f_correct 1.0                   //Correction factor to apply at the distance between camera2 and object
#define h_correct 35                    //Height of the object to correct distance
*/
//Variables to compare changes
int C_size_part;
float C_mask_angle;
int C_offset_line;
int C_width_conveyor;
int C_length_conveyor;
int C_dist_ref;
int C_dist_h;
bool C_bot_ok;

ConfigInputs::ConfigInputs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigInputs)
{
    ui->setupUi(this);

    FILE *readConfigIn;
    readConfigIn = fopen("config/inputs.txt", "r");
    fscanf(readConfigIn, "size_part = %d;\n", &size_part);
    fscanf(readConfigIn, "mask_angle = %f;\n", &mask_angle);
    fscanf(readConfigIn, "offset_line = %d;\n", &offset_line);
    fscanf(readConfigIn, "width_conveyor = %d;\n", &width_conveyor);
    fscanf(readConfigIn, "length_conveyor = %d;\n", &length_conveyor);
    fscanf(readConfigIn, "dist_ref = %d;\n", &dist_ref);
    fscanf(readConfigIn, "dist_h = %d;\n", &dist_h);
    fclose(readConfigIn);

    ui->lineEdit_size_part->setText(QString::number(size_part));
    ui->lineEdit_angle->setText(QString::number(mask_angle));
    ui->lineEdit_offset->setText(QString::number(offset_line));
    ui->lineEdit_width->setText(QString::number(width_conveyor));
    ui->lineEdit_length->setText(QString::number(length_conveyor));
    ui->lineEdit_dist_ref->setText(QString::number(dist_ref));
    ui->lineEdit_height->setText(QString::number(dist_h));

    //Save data to compare
    C_size_part = size_part;
    C_mask_angle = mask_angle;
    C_offset_line = offset_line;
    C_width_conveyor = width_conveyor;
    C_length_conveyor = length_conveyor;
    C_dist_ref = dist_ref;
    C_dist_h = dist_h;

}

ConfigInputs::~ConfigInputs()
{
    delete ui;
}

void ConfigInputs::on_buttonBox_accepted()
{
    size_part = ui->lineEdit_size_part->text().toInt();
    mask_angle = ui->lineEdit_angle->text().toFloat();
    offset_line = ui->lineEdit_offset->text().toInt();
    width_conveyor = ui->lineEdit_width->text().toInt();
    length_conveyor = ui->lineEdit_length->text().toInt();
    dist_ref = ui->lineEdit_dist_ref->text().toInt();
    dist_h = ui->lineEdit_height->text().toInt();

    if(size_part!=C_size_part || mask_angle!=C_mask_angle
            || offset_line!=C_offset_line || width_conveyor!=C_width_conveyor
            || length_conveyor!=C_length_conveyor || dist_ref!=C_dist_ref
            || dist_h!= C_dist_h)
        bot_ok = 1;
    else
        bot_ok = 0;

    if(bot_ok == 1){
        FILE *saveConfigIn;
        saveConfigIn = fopen("config/inputs.txt", "w");
        fprintf(saveConfigIn, "size_part = %d;\n", size_part);
        fprintf(saveConfigIn, "mask_angle = %.2f;\n", mask_angle);
        fprintf(saveConfigIn, "offset_line = %d;\n", offset_line);
        fprintf(saveConfigIn, "width_conveyor = %d;\n", width_conveyor);
        fprintf(saveConfigIn, "length_conveyor = %d;\n", length_conveyor);
        fprintf(saveConfigIn, "dist_ref = %d;\n", dist_ref);
        fprintf(saveConfigIn, "dist_h = %d;\n", dist_h);
        fclose(saveConfigIn);
    }
}

void ConfigInputs::on_pushButton_2_clicked()
{
    size_part = 53;
    mask_angle = 73.5;
    offset_line = 26;
    width_conveyor = 297;
    length_conveyor = 510;
    dist_ref = 420;
    dist_h = 360;

    ui->lineEdit_size_part->setText(QString::number(size_part));
    ui->lineEdit_angle->setText(QString::number(mask_angle));
    ui->lineEdit_offset->setText(QString::number(offset_line));
    ui->lineEdit_width->setText(QString::number(width_conveyor));
    ui->lineEdit_length->setText(QString::number(length_conveyor));
    ui->lineEdit_dist_ref->setText(QString::number(dist_ref));
    ui->lineEdit_height->setText(QString::number(dist_h));

}

void ConfigInputs::on_buttonBox_rejected()
{
    bot_ok = 0;
}
