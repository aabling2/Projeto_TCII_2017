#include "enterconfig.h"
#include "ui_enterconfig.h"

EnterConfig::EnterConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnterConfig)
{
    ui->setupUi(this);
}

EnterConfig::~EnterConfig()
{
    delete ui;
}
