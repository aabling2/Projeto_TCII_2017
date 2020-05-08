/********************************************************************************
** Form generated from reading UI file 'setinput.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETINPUT_H
#define UI_SETINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_SetInput
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QRadioButton *bot_cam1;
    QRadioButton *bot_vid1;
    QGroupBox *groupBox_2;
    QRadioButton *bot_vid2;
    QRadioButton *bot_cam2;
    QPushButton *pushButton;

    void setupUi(QDialog *SetInput)
    {
        if (SetInput->objectName().isEmpty())
            SetInput->setObjectName(QStringLiteral("SetInput"));
        SetInput->setEnabled(true);
        SetInput->resize(220, 206);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/Objectif-photo-Logo-1.png"), QSize(), QIcon::Normal, QIcon::On);
        SetInput->setWindowIcon(icon);
        buttonBox = new QDialogButtonBox(SetInput);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(41, 170, 171, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(SetInput);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 201, 61));
        bot_cam1 = new QRadioButton(groupBox);
        bot_cam1->setObjectName(QStringLiteral("bot_cam1"));
        bot_cam1->setGeometry(QRect(10, 30, 82, 17));
        bot_cam1->setCheckable(true);
        bot_cam1->setChecked(true);
        bot_cam1->setAutoRepeat(false);
        bot_vid1 = new QRadioButton(groupBox);
        bot_vid1->setObjectName(QStringLiteral("bot_vid1"));
        bot_vid1->setGeometry(QRect(110, 30, 82, 17));
        groupBox_2 = new QGroupBox(SetInput);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 70, 201, 61));
        bot_vid2 = new QRadioButton(groupBox_2);
        bot_vid2->setObjectName(QStringLiteral("bot_vid2"));
        bot_vid2->setGeometry(QRect(110, 30, 82, 17));
        bot_cam2 = new QRadioButton(groupBox_2);
        bot_cam2->setObjectName(QStringLiteral("bot_cam2"));
        bot_cam2->setGeometry(QRect(10, 30, 82, 17));
        bot_cam2->setCheckable(true);
        bot_cam2->setChecked(true);
        pushButton = new QPushButton(SetInput);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(57, 140, 155, 23));
        groupBox_2->raise();
        groupBox->raise();
        buttonBox->raise();
        pushButton->raise();

        retranslateUi(SetInput);
        QObject::connect(buttonBox, SIGNAL(accepted()), SetInput, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SetInput, SLOT(reject()));

        QMetaObject::connectSlotsByName(SetInput);
    } // setupUi

    void retranslateUi(QDialog *SetInput)
    {
        SetInput->setWindowTitle(QApplication::translate("SetInput", "Entrada", 0));
        groupBox->setTitle(QApplication::translate("SetInput", "Escolha de entrada 1", 0));
        bot_cam1->setText(QApplication::translate("SetInput", "C\303\242mera 1", 0));
        bot_vid1->setText(QApplication::translate("SetInput", "Simula\303\247\303\243o 1", 0));
        groupBox_2->setTitle(QApplication::translate("SetInput", "Escolha de entrada 2", 0));
        bot_vid2->setText(QApplication::translate("SetInput", "Simula\303\247\303\243o 2", 0));
        bot_cam2->setText(QApplication::translate("SetInput", "C\303\242mera 2", 0));
        pushButton->setText(QApplication::translate("SetInput", "Selecionar videos ...", 0));
    } // retranslateUi

};

namespace Ui {
    class SetInput: public Ui_SetInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETINPUT_H
