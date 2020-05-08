#ifndef SETINPUT_H
#define SETINPUT_H

#include <QDialog>

namespace Ui {
class SetInput;
}

class SetInput : public QDialog
{
    Q_OBJECT

public:
    explicit SetInput(QWidget *parent = 0);
    ~SetInput();
    QString capture1;
    QString capture2;

private slots:
    void on_bot_cam1_clicked();
    void on_bot_cam2_clicked();
    void on_bot_vid1_clicked();
    void on_bot_vid2_clicked();

    void on_pushButton_clicked();

    void on_buttonBox_rejected();

private:
    Ui::SetInput *ui;
};

#endif // SETINPUT_H
