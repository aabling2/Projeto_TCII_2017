/********************************************************************************
** Form generated from reading UI file 'addpartdefault.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPARTDEFAULT_H
#define UI_ADDPARTDEFAULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddPartDefault
{
public:
    QDialogButtonBox *bot_ok;
    QPushButton *bot_add;
    QPushButton *bot_clear;
    QLabel *PartDef_5;
    QLabel *PartDef_8;
    QLabel *PartDef_9;
    QLabel *PartDef_6;
    QLabel *PartDef_7;
    QLabel *PartDef_2;
    QLabel *PartDef_3;
    QGroupBox *groupBox;
    QGroupBox *groupBox_4;
    QLabel *PartDef_4;
    QLabel *PartDef_1;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QLineEdit *NameDef_1;
    QLineEdit *NameDef_2;
    QLineEdit *NameDef_3;
    QLineEdit *NameDef_4;
    QLineEdit *NameDef_5;
    QLineEdit *NameDef_6;
    QLineEdit *NameDef_7;
    QLineEdit *NameDef_8;
    QLineEdit *NameDef_9;
    QLabel *PartCap_2;
    QLabel *PartCap_1;
    QLabel *PartCap_3;
    QLineEdit *NumDef_6;
    QLineEdit *NumDef_4;
    QLineEdit *NumDef_5;
    QLabel *PartCap_4;
    QLabel *PartCap_6;
    QLabel *PartCap_5;
    QLineEdit *NumDef_3;
    QLineEdit *NumDef_7;
    QLabel *PartCap_7;
    QLabel *PartCap_8;
    QLineEdit *NumDef_2;
    QLineEdit *NumDef_1;
    QLabel *PartCap_9;
    QLineEdit *NumDef_9;
    QLineEdit *NumDef_8;

    void setupUi(QDialog *AddPartDefault)
    {
        if (AddPartDefault->objectName().isEmpty())
            AddPartDefault->setObjectName(QStringLiteral("AddPartDefault"));
        AddPartDefault->resize(761, 541);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/Objectif-photo-Logo-1.png"), QSize(), QIcon::Normal, QIcon::On);
        AddPartDefault->setWindowIcon(icon);
        bot_ok = new QDialogButtonBox(AddPartDefault);
        bot_ok->setObjectName(QStringLiteral("bot_ok"));
        bot_ok->setGeometry(QRect(410, 500, 341, 32));
        bot_ok->setOrientation(Qt::Horizontal);
        bot_ok->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        bot_add = new QPushButton(AddPartDefault);
        bot_add->setObjectName(QStringLiteral("bot_add"));
        bot_add->setGeometry(QRect(10, 505, 75, 23));
        bot_clear = new QPushButton(AddPartDefault);
        bot_clear->setObjectName(QStringLiteral("bot_clear"));
        bot_clear->setGeometry(QRect(390, 505, 75, 23));
        PartDef_5 = new QLabel(AddPartDefault);
        PartDef_5->setObjectName(QStringLiteral("PartDef_5"));
        PartDef_5->setGeometry(QRect(520, 210, 100, 100));
        PartDef_5->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartDef_8 = new QLabel(AddPartDefault);
        PartDef_8->setObjectName(QStringLiteral("PartDef_8"));
        PartDef_8->setGeometry(QRect(520, 350, 100, 100));
        PartDef_8->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartDef_9 = new QLabel(AddPartDefault);
        PartDef_9->setObjectName(QStringLiteral("PartDef_9"));
        PartDef_9->setGeometry(QRect(640, 350, 100, 100));
        PartDef_9->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartDef_6 = new QLabel(AddPartDefault);
        PartDef_6->setObjectName(QStringLiteral("PartDef_6"));
        PartDef_6->setGeometry(QRect(640, 210, 100, 100));
        PartDef_6->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartDef_7 = new QLabel(AddPartDefault);
        PartDef_7->setObjectName(QStringLiteral("PartDef_7"));
        PartDef_7->setGeometry(QRect(400, 350, 100, 100));
        PartDef_7->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartDef_2 = new QLabel(AddPartDefault);
        PartDef_2->setObjectName(QStringLiteral("PartDef_2"));
        PartDef_2->setGeometry(QRect(520, 70, 100, 100));
        PartDef_2->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartDef_3 = new QLabel(AddPartDefault);
        PartDef_3->setObjectName(QStringLiteral("PartDef_3"));
        PartDef_3->setGeometry(QRect(640, 70, 100, 100));
        PartDef_3->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        groupBox = new QGroupBox(AddPartDefault);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(380, 6, 381, 481));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 20, 361, 451));
        groupBox_4->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
""));
        PartDef_4 = new QLabel(AddPartDefault);
        PartDef_4->setObjectName(QStringLiteral("PartDef_4"));
        PartDef_4->setGeometry(QRect(400, 210, 100, 100));
        PartDef_4->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartDef_1 = new QLabel(AddPartDefault);
        PartDef_1->setObjectName(QStringLiteral("PartDef_1"));
        PartDef_1->setGeometry(QRect(400, 70, 100, 100));
        PartDef_1->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        groupBox_2 = new QGroupBox(AddPartDefault);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 6, 381, 481));
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 20, 361, 451));
        groupBox_3->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
""));
        NameDef_1 = new QLineEdit(AddPartDefault);
        NameDef_1->setObjectName(QStringLiteral("NameDef_1"));
        NameDef_1->setGeometry(QRect(400, 45, 101, 20));
        NameDef_1->setFocusPolicy(Qt::StrongFocus);
        NameDef_1->setMaxLength(16);
        NameDef_1->setEchoMode(QLineEdit::Normal);
        NameDef_2 = new QLineEdit(AddPartDefault);
        NameDef_2->setObjectName(QStringLiteral("NameDef_2"));
        NameDef_2->setGeometry(QRect(520, 45, 101, 20));
        NameDef_2->setMaxLength(16);
        NameDef_3 = new QLineEdit(AddPartDefault);
        NameDef_3->setObjectName(QStringLiteral("NameDef_3"));
        NameDef_3->setGeometry(QRect(640, 45, 101, 20));
        NameDef_3->setMaxLength(16);
        NameDef_4 = new QLineEdit(AddPartDefault);
        NameDef_4->setObjectName(QStringLiteral("NameDef_4"));
        NameDef_4->setGeometry(QRect(400, 185, 101, 20));
        NameDef_4->setMaxLength(16);
        NameDef_5 = new QLineEdit(AddPartDefault);
        NameDef_5->setObjectName(QStringLiteral("NameDef_5"));
        NameDef_5->setGeometry(QRect(520, 185, 101, 20));
        NameDef_5->setMaxLength(16);
        NameDef_6 = new QLineEdit(AddPartDefault);
        NameDef_6->setObjectName(QStringLiteral("NameDef_6"));
        NameDef_6->setGeometry(QRect(640, 185, 101, 20));
        NameDef_6->setMaxLength(16);
        NameDef_7 = new QLineEdit(AddPartDefault);
        NameDef_7->setObjectName(QStringLiteral("NameDef_7"));
        NameDef_7->setGeometry(QRect(400, 325, 101, 20));
        NameDef_7->setMaxLength(16);
        NameDef_8 = new QLineEdit(AddPartDefault);
        NameDef_8->setObjectName(QStringLiteral("NameDef_8"));
        NameDef_8->setGeometry(QRect(520, 325, 101, 20));
        NameDef_8->setMaxLength(16);
        NameDef_9 = new QLineEdit(AddPartDefault);
        NameDef_9->setObjectName(QStringLiteral("NameDef_9"));
        NameDef_9->setGeometry(QRect(640, 325, 101, 20));
        NameDef_9->setMaxLength(16);
        PartCap_2 = new QLabel(AddPartDefault);
        PartCap_2->setObjectName(QStringLiteral("PartCap_2"));
        PartCap_2->setGeometry(QRect(140, 70, 100, 100));
        PartCap_2->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartCap_1 = new QLabel(AddPartDefault);
        PartCap_1->setObjectName(QStringLiteral("PartCap_1"));
        PartCap_1->setGeometry(QRect(20, 70, 100, 100));
        PartCap_1->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartCap_3 = new QLabel(AddPartDefault);
        PartCap_3->setObjectName(QStringLiteral("PartCap_3"));
        PartCap_3->setGeometry(QRect(260, 70, 100, 100));
        PartCap_3->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        NumDef_6 = new QLineEdit(AddPartDefault);
        NumDef_6->setObjectName(QStringLiteral("NumDef_6"));
        NumDef_6->setEnabled(false);
        NumDef_6->setGeometry(QRect(260, 185, 101, 20));
        NumDef_6->setReadOnly(true);
        NumDef_4 = new QLineEdit(AddPartDefault);
        NumDef_4->setObjectName(QStringLiteral("NumDef_4"));
        NumDef_4->setEnabled(false);
        NumDef_4->setGeometry(QRect(20, 185, 101, 20));
        NumDef_4->setReadOnly(true);
        NumDef_5 = new QLineEdit(AddPartDefault);
        NumDef_5->setObjectName(QStringLiteral("NumDef_5"));
        NumDef_5->setEnabled(false);
        NumDef_5->setGeometry(QRect(140, 185, 101, 20));
        NumDef_5->setReadOnly(true);
        PartCap_4 = new QLabel(AddPartDefault);
        PartCap_4->setObjectName(QStringLiteral("PartCap_4"));
        PartCap_4->setGeometry(QRect(20, 210, 100, 100));
        PartCap_4->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartCap_6 = new QLabel(AddPartDefault);
        PartCap_6->setObjectName(QStringLiteral("PartCap_6"));
        PartCap_6->setGeometry(QRect(260, 210, 100, 100));
        PartCap_6->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartCap_5 = new QLabel(AddPartDefault);
        PartCap_5->setObjectName(QStringLiteral("PartCap_5"));
        PartCap_5->setGeometry(QRect(140, 210, 100, 100));
        PartCap_5->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        NumDef_3 = new QLineEdit(AddPartDefault);
        NumDef_3->setObjectName(QStringLiteral("NumDef_3"));
        NumDef_3->setEnabled(false);
        NumDef_3->setGeometry(QRect(260, 45, 101, 20));
        NumDef_3->setReadOnly(true);
        NumDef_7 = new QLineEdit(AddPartDefault);
        NumDef_7->setObjectName(QStringLiteral("NumDef_7"));
        NumDef_7->setEnabled(false);
        NumDef_7->setGeometry(QRect(20, 325, 101, 20));
        NumDef_7->setReadOnly(true);
        PartCap_7 = new QLabel(AddPartDefault);
        PartCap_7->setObjectName(QStringLiteral("PartCap_7"));
        PartCap_7->setGeometry(QRect(20, 350, 100, 100));
        PartCap_7->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartCap_8 = new QLabel(AddPartDefault);
        PartCap_8->setObjectName(QStringLiteral("PartCap_8"));
        PartCap_8->setGeometry(QRect(140, 350, 100, 100));
        PartCap_8->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        NumDef_2 = new QLineEdit(AddPartDefault);
        NumDef_2->setObjectName(QStringLiteral("NumDef_2"));
        NumDef_2->setEnabled(false);
        NumDef_2->setGeometry(QRect(140, 45, 101, 20));
        NumDef_2->setReadOnly(true);
        NumDef_1 = new QLineEdit(AddPartDefault);
        NumDef_1->setObjectName(QStringLiteral("NumDef_1"));
        NumDef_1->setEnabled(false);
        NumDef_1->setGeometry(QRect(20, 45, 101, 20));
        NumDef_1->setReadOnly(true);
        PartCap_9 = new QLabel(AddPartDefault);
        PartCap_9->setObjectName(QStringLiteral("PartCap_9"));
        PartCap_9->setGeometry(QRect(260, 350, 100, 100));
        PartCap_9->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        NumDef_9 = new QLineEdit(AddPartDefault);
        NumDef_9->setObjectName(QStringLiteral("NumDef_9"));
        NumDef_9->setEnabled(false);
        NumDef_9->setGeometry(QRect(260, 325, 101, 20));
        NumDef_9->setReadOnly(true);
        NumDef_8 = new QLineEdit(AddPartDefault);
        NumDef_8->setObjectName(QStringLiteral("NumDef_8"));
        NumDef_8->setEnabled(false);
        NumDef_8->setGeometry(QRect(140, 325, 101, 20));
        NumDef_8->setReadOnly(true);
        groupBox_2->raise();
        groupBox->raise();
        bot_ok->raise();
        bot_add->raise();
        bot_clear->raise();
        PartDef_5->raise();
        PartDef_8->raise();
        PartDef_9->raise();
        PartDef_6->raise();
        PartDef_7->raise();
        PartDef_2->raise();
        PartDef_3->raise();
        PartDef_4->raise();
        PartDef_1->raise();
        NameDef_1->raise();
        NameDef_2->raise();
        NameDef_3->raise();
        NameDef_4->raise();
        NameDef_5->raise();
        NameDef_6->raise();
        NameDef_7->raise();
        NameDef_8->raise();
        NameDef_9->raise();
        PartCap_2->raise();
        PartCap_1->raise();
        PartCap_3->raise();
        NumDef_6->raise();
        NumDef_4->raise();
        NumDef_5->raise();
        PartCap_4->raise();
        PartCap_6->raise();
        PartCap_5->raise();
        NumDef_3->raise();
        NumDef_7->raise();
        PartCap_7->raise();
        PartCap_8->raise();
        NumDef_2->raise();
        NumDef_1->raise();
        PartCap_9->raise();
        NumDef_9->raise();
        NumDef_8->raise();
        QWidget::setTabOrder(bot_add, bot_clear);

        retranslateUi(AddPartDefault);
        QObject::connect(bot_ok, SIGNAL(accepted()), AddPartDefault, SLOT(accept()));
        QObject::connect(bot_ok, SIGNAL(rejected()), AddPartDefault, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddPartDefault);
    } // setupUi

    void retranslateUi(QDialog *AddPartDefault)
    {
        AddPartDefault->setWindowTitle(QApplication::translate("AddPartDefault", "Adicionar padr\303\265es", 0));
        bot_add->setText(QApplication::translate("AddPartDefault", "Adicionar", 0));
        bot_clear->setText(QApplication::translate("AddPartDefault", "Limpar", 0));
        PartDef_5->setText(QString());
        PartDef_8->setText(QString());
        PartDef_9->setText(QString());
        PartDef_6->setText(QString());
        PartDef_7->setText(QString());
        PartDef_2->setText(QString());
        PartDef_3->setText(QString());
        groupBox->setTitle(QApplication::translate("AddPartDefault", "PE\303\207AS PADR\303\225ES SALVAS", 0));
        groupBox_4->setTitle(QString());
        PartDef_4->setText(QString());
        PartDef_1->setText(QString());
        groupBox_2->setTitle(QApplication::translate("AddPartDefault", "PE\303\207AS PADR\303\225ES CAPTURADAS", 0));
        groupBox_3->setTitle(QString());
        PartCap_2->setText(QString());
        PartCap_1->setText(QString());
        PartCap_3->setText(QString());
        PartCap_4->setText(QString());
        PartCap_6->setText(QString());
        PartCap_5->setText(QString());
        PartCap_7->setText(QString());
        PartCap_8->setText(QString());
        PartCap_9->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AddPartDefault: public Ui_AddPartDefault {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPARTDEFAULT_H
