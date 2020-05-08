#ifndef INFOABOUT_H
#define INFOABOUT_H

#include <QDialog>

namespace Ui {
class InfoAbout;
}

class InfoAbout : public QDialog
{
    Q_OBJECT

public:
    explicit InfoAbout(QWidget *parent = 0);
    ~InfoAbout();

private slots:
    void on_bot_ok_clicked();

private:
    Ui::InfoAbout *ui;
};

#endif // INFOABOUT_H
