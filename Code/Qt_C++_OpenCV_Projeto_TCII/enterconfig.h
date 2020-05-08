#ifndef ENTERCONFIG_H
#define ENTERCONFIG_H

#include <QDialog>

namespace Ui {
class EnterConfig;
}

class EnterConfig : public QDialog
{
    Q_OBJECT

public:
    explicit EnterConfig(QWidget *parent = 0);
    ~EnterConfig();

private:
    Ui::EnterConfig *ui;
};

#endif // ENTERCONFIG_H
