#ifndef CONFIGINPUTS_H
#define CONFIGINPUTS_H

#include <QDialog>

namespace Ui {
class ConfigInputs;
}

class ConfigInputs : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigInputs(QWidget *parent = 0);
    ~ConfigInputs();
    int size_part;          //Real diameter of the part(millimeters)
    float mask_angle;       //Angle to make the lines in camera2 to align the conveyor
    int offset_line;        //Offset from the side of the image (pixels)
    int width_conveyor;     //Width of the conveyor to use on reading at second camera (millimeters)
    int length_conveyor;    //Length of the conveyor to use on reading at second camera (millimeters)
    int dist_ref;           //Distance between camera2 and end of length conveyor (millimeters)
    int dist_h;             //Height distance between camera2 and conveyor (millimeters)
    bool bot_ok;

private slots:
    void on_buttonBox_accepted();
    void on_pushButton_2_clicked();

    void on_buttonBox_rejected();

private:
    Ui::ConfigInputs *ui;
};

#endif // CONFIGINPUTS_H
