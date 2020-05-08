#include "setinput.h"
#include "ui_setinput.h"
#include <QFileDialog>

SetInput::SetInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetInput)
{
    ui->setupUi(this);

    ui->bot_cam1->click();
    ui->bot_cam2->click();

}

SetInput::~SetInput()
{
    delete ui;
}

void SetInput::on_bot_cam1_clicked()
{
    capture1 = "USB0";
}

void SetInput::on_bot_cam2_clicked()
{
    capture2 = "USB2";
}

void SetInput::on_bot_vid1_clicked()
{
    capture1 = "videos/Cam1_video.avi";
}

void SetInput::on_bot_vid2_clicked()
{
    capture2 = "videos/Cam2_video.avi";
}


void SetInput::on_pushButton_clicked()
{
    capture1 = QFileDialog::getOpenFileName(
                this,
                tr("Selecionar video 1"),
                "Cam1_video.avi",
                tr("AVI (*avi)"));

    capture2 = QFileDialog::getOpenFileName(
                this,
                tr("Selecionar video 2"),
                "Cam2_video.avi",
                tr("AVI (*avi)"));
}

void SetInput::on_buttonBox_rejected()
{
    capture1 = "CANCELED";
    capture2 = "CANCELED";
}
