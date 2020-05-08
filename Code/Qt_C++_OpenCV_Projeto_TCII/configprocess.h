#ifndef CONFIGPROCESS_H
#define CONFIGPROCESS_H

#include <QDialog>

namespace Ui {
class ConfigProcess;
}

class ConfigProcess : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigProcess(QWidget *parent = 0);
    ~ConfigProcess();

private slots:

    void on_tabWidget_currentChanged(int index);

    void on_tabWidget_2_currentChanged(int index);

    void MainProcess(int index);

    void on_bot_cam1_clicked();

    void on_bot_cam2_clicked();

    void on_bot_Default_clicked();

    void on_filter1_clicked();

    void on_filter3_clicked();

    void on_filter5_clicked();

    void on_filter7_clicked();

    void on_filter9_clicked();

    void on_filter11_clicked();

    void on_filter13_clicked();

    void on_filter15_clicked();

    void on_filter17_clicked();

    void on_filter19_clicked();

    void on_filter21_clicked();

    void on_filter23_clicked();

    void on_open1_clicked();

    void on_open2_clicked();

    void on_open3_clicked();

    void on_open4_clicked();

    void on_open5_clicked();

    void on_open6_clicked();

    void on_open7_clicked();

    void on_open8_clicked();

    void on_open9_clicked();

    void on_open10_clicked();

    void on_open11_clicked();

    void on_open12_clicked();

    void on_close1_clicked();

    void on_close2_clicked();

    void on_close3_clicked();

    void on_close4_clicked();

    void on_close5_clicked();

    void on_close6_clicked();

    void on_close7_clicked();

    void on_close8_clicked();

    void on_close9_clicked();

    void on_close10_clicked();

    void on_close11_clicked();

    void on_close12_clicked();

    void on_Slider_Rmin_valueChanged(int value);

    void on_Slider_Gmin_valueChanged(int value);

    void on_Slider_Bmin_valueChanged(int value);

    void on_Slider_Rmax_valueChanged(int value);

    void on_Slider_Gmax_valueChanged(int value);

    void on_Slider_Bmax_valueChanged(int value);

    void on_Slider_Rmin_2_valueChanged(int value);

    void on_Slider_Gmin_2_valueChanged(int value);

    void on_Slider_Bmin_2_valueChanged(int value);

    void on_Slider_Rmax_2_valueChanged(int value);

    void on_Slider_Gmax_2_valueChanged(int value);

    void on_Slider_Bmax_2_valueChanged(int value);

    void on_buttonBox_accepted();

    void UpdateProcess();

private:
    Ui::ConfigProcess *ui;
};

#endif // CONFIGPROCESS_H
