#include "infoabout.h"
#include "ui_infoabout.h"

InfoAbout::InfoAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoAbout)
{
    ui->setupUi(this);
}

InfoAbout::~InfoAbout()
{
    delete ui;
}

void InfoAbout::on_bot_ok_clicked()
{
    close();
}
