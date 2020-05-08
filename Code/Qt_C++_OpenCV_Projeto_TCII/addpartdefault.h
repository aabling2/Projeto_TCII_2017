#ifndef ADDPARTDEFAULT_H
#define ADDPARTDEFAULT_H

#include <QDialog>
#include <QEvent>

#define num_max_default   9             //Maximum number of standard parts

namespace Ui {
class AddPartDefault;
}

class AddPartDefault : public QDialog
{
    Q_OBJECT

public:
    explicit AddPartDefault(QWidget *parent = 0);
    ~AddPartDefault();

    bool bot_ok = false;

private slots:
    void on_bot_add_clicked();

    void on_bot_clear_clicked();

    void on_bot_ok_accepted();

    void on_bot_ok_rejected();

    void LoadDefault();

private:
    Ui::AddPartDefault *ui;

protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif // ADDPARTDEFAULT_H
