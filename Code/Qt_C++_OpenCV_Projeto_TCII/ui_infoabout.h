/********************************************************************************
** Form generated from reading UI file 'infoabout.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOABOUT_H
#define UI_INFOABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InfoAbout
{
public:
    QPushButton *bot_ok;
    QPlainTextEdit *plainTextEdit;
    QLabel *label;

    void setupUi(QDialog *InfoAbout)
    {
        if (InfoAbout->objectName().isEmpty())
            InfoAbout->setObjectName(QStringLiteral("InfoAbout"));
        InfoAbout->resize(434, 323);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/Objectif-photo-Logo-1.png"), QSize(), QIcon::Normal, QIcon::On);
        InfoAbout->setWindowIcon(icon);
        InfoAbout->setStyleSheet(QStringLiteral(""));
        bot_ok = new QPushButton(InfoAbout);
        bot_ok->setObjectName(QStringLiteral("bot_ok"));
        bot_ok->setGeometry(QRect(340, 290, 75, 23));
        plainTextEdit = new QPlainTextEdit(InfoAbout);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setEnabled(true);
        plainTextEdit->setGeometry(QRect(10, 100, 411, 181));
        QFont font;
        font.setPointSize(10);
        plainTextEdit->setFont(font);
        plainTextEdit->setAutoFillBackground(false);
        plainTextEdit->setReadOnly(true);
        label = new QLabel(InfoAbout);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 10, 361, 81));
        label->setStyleSheet(QStringLiteral("image: url(:/images/images/LOGO - UNISC.png);"));

        retranslateUi(InfoAbout);

        QMetaObject::connectSlotsByName(InfoAbout);
    } // setupUi

    void retranslateUi(QDialog *InfoAbout)
    {
        InfoAbout->setWindowTitle(QApplication::translate("InfoAbout", "Sobre", 0));
        bot_ok->setText(QApplication::translate("InfoAbout", "OK", 0));
        plainTextEdit->setPlainText(QApplication::translate("InfoAbout", "        Trabalho de conclus\303\243o - Gradua\303\247\303\243o em Engenharia El\303\251trica\n"
"\n"
"SISTEMA DE VIS\303\203O COMPUTACIONAL PARA INSPE\303\207\303\203O MULTIPE\303\207AS    \n"
"               EM LINHA DE PRODU\303\207\303\203O UTILIZANDO OPENCV\n"
"\n"
"\n"
"Ano: 2017\n"
"Aluno: Augusto Abling\n"
"Orientador: Prof. Me. Adriano Jos\303\251 Bombardieri", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InfoAbout: public Ui_InfoAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOABOUT_H
