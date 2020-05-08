/********************************************************************************
** Form generated from reading UI file 'configinputs.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGINPUTS_H
#define UI_CONFIGINPUTS_H

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

class Ui_ConfigInputs
{
public:
    QGroupBox *groupBox_3;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_angle;
    QLineEdit *lineEdit_offset;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox_4;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_5;
    QLineEdit *lineEdit_width;
    QLineEdit *lineEdit_length;
    QLineEdit *lineEdit_dist_ref;
    QLineEdit *lineEdit_height;
    QLabel *label_13;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_14;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_2;
    QLabel *label_12;
    QLineEdit *lineEdit_size_part;
    QLabel *label_17;
    QPushButton *pushButton_2;

    void setupUi(QDialog *ConfigInputs)
    {
        if (ConfigInputs->objectName().isEmpty())
            ConfigInputs->setObjectName(QStringLiteral("ConfigInputs"));
        ConfigInputs->resize(340, 300);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/Objectif-photo-Logo-1.png"), QSize(), QIcon::Normal, QIcon::On);
        ConfigInputs->setWindowIcon(icon);
        groupBox_3 = new QGroupBox(ConfigInputs);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 60, 318, 71));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 20, 141, 16));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 40, 141, 16));
        lineEdit_angle = new QLineEdit(groupBox_3);
        lineEdit_angle->setObjectName(QStringLiteral("lineEdit_angle"));
        lineEdit_angle->setGeometry(QRect(240, 20, 41, 20));
        lineEdit_angle->setAlignment(Qt::AlignCenter);
        lineEdit_offset = new QLineEdit(groupBox_3);
        lineEdit_offset->setObjectName(QStringLiteral("lineEdit_offset"));
        lineEdit_offset->setGeometry(QRect(240, 40, 41, 20));
        lineEdit_offset->setAlignment(Qt::AlignCenter);
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(290, 24, 47, 13));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(290, 44, 47, 13));
        groupBox_4 = new QGroupBox(ConfigInputs);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 130, 318, 111));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 80, 141, 16));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 60, 141, 16));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 40, 141, 16));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 20, 141, 16));
        lineEdit_width = new QLineEdit(groupBox_4);
        lineEdit_width->setObjectName(QStringLiteral("lineEdit_width"));
        lineEdit_width->setGeometry(QRect(240, 20, 41, 20));
        lineEdit_width->setAlignment(Qt::AlignCenter);
        lineEdit_length = new QLineEdit(groupBox_4);
        lineEdit_length->setObjectName(QStringLiteral("lineEdit_length"));
        lineEdit_length->setGeometry(QRect(240, 40, 41, 20));
        lineEdit_length->setAlignment(Qt::AlignCenter);
        lineEdit_dist_ref = new QLineEdit(groupBox_4);
        lineEdit_dist_ref->setObjectName(QStringLiteral("lineEdit_dist_ref"));
        lineEdit_dist_ref->setGeometry(QRect(240, 60, 41, 20));
        lineEdit_dist_ref->setAlignment(Qt::AlignCenter);
        lineEdit_height = new QLineEdit(groupBox_4);
        lineEdit_height->setObjectName(QStringLiteral("lineEdit_height"));
        lineEdit_height->setGeometry(QRect(240, 80, 41, 20));
        lineEdit_height->setAlignment(Qt::AlignCenter);
        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(290, 24, 47, 13));
        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(290, 84, 47, 13));
        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(290, 64, 47, 13));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(290, 44, 47, 13));
        buttonBox = new QDialogButtonBox(ConfigInputs);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(-10, 260, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox_2 = new QGroupBox(ConfigInputs);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 11, 318, 51));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 20, 141, 16));
        lineEdit_size_part = new QLineEdit(groupBox_2);
        lineEdit_size_part->setObjectName(QStringLiteral("lineEdit_size_part"));
        lineEdit_size_part->setGeometry(QRect(240, 20, 41, 20));
        lineEdit_size_part->setAlignment(Qt::AlignCenter);
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(290, 24, 47, 13));
        pushButton_2 = new QPushButton(ConfigInputs);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(14, 264, 75, 23));
        groupBox_4->raise();
        groupBox_3->raise();
        buttonBox->raise();
        groupBox_2->raise();
        pushButton_2->raise();

        retranslateUi(ConfigInputs);
        QObject::connect(buttonBox, SIGNAL(accepted()), ConfigInputs, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ConfigInputs, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConfigInputs);
    } // setupUi

    void retranslateUi(QDialog *ConfigInputs)
    {
        ConfigInputs->setWindowTitle(QApplication::translate("ConfigInputs", "Configura\303\247\303\265es de entrada", 0));
        groupBox_3->setTitle(QApplication::translate("ConfigInputs", "Limites da c\303\242mera 2", 0));
        label_3->setText(QApplication::translate("ConfigInputs", "\303\202ngulo ", 0));
        label_4->setText(QApplication::translate("ConfigInputs", "Recuo", 0));
        label->setText(QApplication::translate("ConfigInputs", "\302\272", 0));
        label_2->setText(QApplication::translate("ConfigInputs", "px", 0));
        groupBox_4->setTitle(QApplication::translate("ConfigInputs", "Refer\303\252ncias da esteira", 0));
        label_8->setText(QApplication::translate("ConfigInputs", "Altura refer\303\252ncia", 0));
        label_7->setText(QApplication::translate("ConfigInputs", "Dist\303\242ncia refer\303\252ncia", 0));
        label_6->setText(QApplication::translate("ConfigInputs", "Comprimento", 0));
        label_5->setText(QApplication::translate("ConfigInputs", "Largura", 0));
        label_13->setText(QApplication::translate("ConfigInputs", "mm", 0));
        label_15->setText(QApplication::translate("ConfigInputs", "mm", 0));
        label_16->setText(QApplication::translate("ConfigInputs", "mm", 0));
        label_14->setText(QApplication::translate("ConfigInputs", "mm", 0));
        groupBox_2->setTitle(QApplication::translate("ConfigInputs", "Dados pe\303\247as", 0));
        label_12->setText(QApplication::translate("ConfigInputs", "Tamanho da pe\303\247a padr\303\243o", 0));
        label_17->setText(QApplication::translate("ConfigInputs", "mm", 0));
        pushButton_2->setText(QApplication::translate("ConfigInputs", "Padr\303\243o", 0));
    } // retranslateUi

};

namespace Ui {
    class ConfigInputs: public Ui_ConfigInputs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGINPUTS_H
