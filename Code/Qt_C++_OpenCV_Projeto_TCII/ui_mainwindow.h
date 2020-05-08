/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSair;
    QAction *actionIniciar;
    QAction *actionConfigura_es_de_entrada;
    QAction *actionConfigura_es_de_processamento;
    QAction *actionIniciar_processamento;
    QAction *actionCongelar_tela;
    QAction *actionPararContinuar;
    QAction *actionCaptura_da_tela;
    QAction *actionContinuar;
    QAction *actionAdicionar_pe_as_padr_es;
    QAction *actionSobre;
    QAction *actionReiniciar;
    QAction *actionEncerrar;
    QWidget *centralWidget;
    QGroupBox *BoxInfo;
    QPlainTextEdit *TelaInfo;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_good;
    QLabel *label_bad;
    QLabel *label_nodef;
    QLabel *label_objects;
    QLabel *PartDef_1;
    QLabel *ScreenResult_1;
    QLabel *ScreenResult_2;
    QLabel *PartDef_2;
    QLabel *PartDef_3;
    QLabel *PartDef_4;
    QLabel *PartDef_5;
    QLabel *PartDef_6;
    QLabel *PartDef_7;
    QLabel *PartDef_8;
    QLabel *PartDef_9;
    QGroupBox *BoxInfo_2;
    QPlainTextEdit *TelaInfo_2;
    QLabel *label_5;
    QLabel *label_objects_2;
    QGroupBox *BoxCam1;
    QGroupBox *BoxCam1_2;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QLineEdit *NameDef_1;
    QLineEdit *NameDef_2;
    QLineEdit *NameDef_3;
    QLineEdit *NameDef_4;
    QLineEdit *NameDef_5;
    QLineEdit *NameDef_6;
    QLineEdit *NameDef_7;
    QLineEdit *NameDef_8;
    QLineEdit *NameDef_9;
    QMenuBar *menuBar;
    QMenu *menuArquivo;
    QMenu *menuConfigura_es;
    QMenu *menuSobre;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1366, 768);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/Objectif-photo-Logo-1.png"), QSize(), QIcon::Normal, QIcon::On);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QStringLiteral(""));
        MainWindow->setAnimated(true);
        actionSair = new QAction(MainWindow);
        actionSair->setObjectName(QStringLiteral("actionSair"));
        actionIniciar = new QAction(MainWindow);
        actionIniciar->setObjectName(QStringLiteral("actionIniciar"));
        actionConfigura_es_de_entrada = new QAction(MainWindow);
        actionConfigura_es_de_entrada->setObjectName(QStringLiteral("actionConfigura_es_de_entrada"));
        actionConfigura_es_de_processamento = new QAction(MainWindow);
        actionConfigura_es_de_processamento->setObjectName(QStringLiteral("actionConfigura_es_de_processamento"));
        actionIniciar_processamento = new QAction(MainWindow);
        actionIniciar_processamento->setObjectName(QStringLiteral("actionIniciar_processamento"));
        actionCongelar_tela = new QAction(MainWindow);
        actionCongelar_tela->setObjectName(QStringLiteral("actionCongelar_tela"));
        actionPararContinuar = new QAction(MainWindow);
        actionPararContinuar->setObjectName(QStringLiteral("actionPararContinuar"));
        actionCaptura_da_tela = new QAction(MainWindow);
        actionCaptura_da_tela->setObjectName(QStringLiteral("actionCaptura_da_tela"));
        actionContinuar = new QAction(MainWindow);
        actionContinuar->setObjectName(QStringLiteral("actionContinuar"));
        actionAdicionar_pe_as_padr_es = new QAction(MainWindow);
        actionAdicionar_pe_as_padr_es->setObjectName(QStringLiteral("actionAdicionar_pe_as_padr_es"));
        actionSobre = new QAction(MainWindow);
        actionSobre->setObjectName(QStringLiteral("actionSobre"));
        actionReiniciar = new QAction(MainWindow);
        actionReiniciar->setObjectName(QStringLiteral("actionReiniciar"));
        actionEncerrar = new QAction(MainWindow);
        actionEncerrar->setObjectName(QStringLiteral("actionEncerrar"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BoxInfo = new QGroupBox(centralWidget);
        BoxInfo->setObjectName(QStringLiteral("BoxInfo"));
        BoxInfo->setGeometry(QRect(0, 0, 231, 361));
        TelaInfo = new QPlainTextEdit(BoxInfo);
        TelaInfo->setObjectName(QStringLiteral("TelaInfo"));
        TelaInfo->setEnabled(true);
        TelaInfo->setGeometry(QRect(10, 20, 211, 231));
        TelaInfo->setReadOnly(true);
        label = new QLabel(BoxInfo);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 320, 81, 21));
        label_2 = new QLabel(BoxInfo);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 300, 71, 21));
        label_3 = new QLabel(BoxInfo);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 260, 71, 21));
        label_4 = new QLabel(BoxInfo);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 280, 71, 21));
        label_good = new QLabel(BoxInfo);
        label_good->setObjectName(QStringLiteral("label_good"));
        label_good->setGeometry(QRect(130, 260, 81, 21));
        label_good->setLayoutDirection(Qt::LeftToRight);
        label_good->setAutoFillBackground(false);
        label_good->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 127);"));
        label_good->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_good->setMargin(0);
        label_bad = new QLabel(BoxInfo);
        label_bad->setObjectName(QStringLiteral("label_bad"));
        label_bad->setGeometry(QRect(130, 280, 81, 21));
        label_bad->setLayoutDirection(Qt::LeftToRight);
        label_bad->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 127);"));
        label_bad->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_nodef = new QLabel(BoxInfo);
        label_nodef->setObjectName(QStringLiteral("label_nodef"));
        label_nodef->setGeometry(QRect(130, 300, 81, 21));
        label_nodef->setLayoutDirection(Qt::LeftToRight);
        label_nodef->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 127);"));
        label_nodef->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_objects = new QLabel(BoxInfo);
        label_objects->setObjectName(QStringLiteral("label_objects"));
        label_objects->setGeometry(QRect(130, 320, 81, 21));
        label_objects->setLayoutDirection(Qt::LeftToRight);
        label_objects->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 127);"));
        label_objects->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        TelaInfo->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_bad->raise();
        label_nodef->raise();
        label_objects->raise();
        label_good->raise();
        PartDef_1 = new QLabel(centralWidget);
        PartDef_1->setObjectName(QStringLiteral("PartDef_1"));
        PartDef_1->setGeometry(QRect(260, 510, 100, 100));
        PartDef_1->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        ScreenResult_1 = new QLabel(centralWidget);
        ScreenResult_1->setObjectName(QStringLiteral("ScreenResult_1"));
        ScreenResult_1->setGeometry(QRect(240, 20, 550, 412));
        ScreenResult_1->setLayoutDirection(Qt::LeftToRight);
        ScreenResult_1->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        ScreenResult_1->setAlignment(Qt::AlignCenter);
        ScreenResult_2 = new QLabel(centralWidget);
        ScreenResult_2->setObjectName(QStringLiteral("ScreenResult_2"));
        ScreenResult_2->setGeometry(QRect(800, 20, 550, 412));
        ScreenResult_2->setLayoutDirection(Qt::LeftToRight);
        ScreenResult_2->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        ScreenResult_2->setAlignment(Qt::AlignCenter);
        PartDef_2 = new QLabel(centralWidget);
        PartDef_2->setObjectName(QStringLiteral("PartDef_2"));
        PartDef_2->setGeometry(QRect(380, 510, 100, 100));
        PartDef_2->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartDef_3 = new QLabel(centralWidget);
        PartDef_3->setObjectName(QStringLiteral("PartDef_3"));
        PartDef_3->setGeometry(QRect(500, 510, 100, 100));
        PartDef_3->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartDef_4 = new QLabel(centralWidget);
        PartDef_4->setObjectName(QStringLiteral("PartDef_4"));
        PartDef_4->setGeometry(QRect(620, 510, 100, 100));
        PartDef_4->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartDef_5 = new QLabel(centralWidget);
        PartDef_5->setObjectName(QStringLiteral("PartDef_5"));
        PartDef_5->setGeometry(QRect(740, 510, 100, 100));
        PartDef_5->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartDef_6 = new QLabel(centralWidget);
        PartDef_6->setObjectName(QStringLiteral("PartDef_6"));
        PartDef_6->setGeometry(QRect(860, 510, 100, 100));
        PartDef_6->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartDef_7 = new QLabel(centralWidget);
        PartDef_7->setObjectName(QStringLiteral("PartDef_7"));
        PartDef_7->setGeometry(QRect(980, 510, 100, 100));
        PartDef_7->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartDef_8 = new QLabel(centralWidget);
        PartDef_8->setObjectName(QStringLiteral("PartDef_8"));
        PartDef_8->setGeometry(QRect(1100, 510, 100, 100));
        PartDef_8->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        PartDef_9 = new QLabel(centralWidget);
        PartDef_9->setObjectName(QStringLiteral("PartDef_9"));
        PartDef_9->setGeometry(QRect(1220, 510, 100, 100));
        PartDef_9->setStyleSheet(QStringLiteral("background-color: rgb(200, 200, 200);"));
        BoxInfo_2 = new QGroupBox(centralWidget);
        BoxInfo_2->setObjectName(QStringLiteral("BoxInfo_2"));
        BoxInfo_2->setGeometry(QRect(0, 370, 231, 271));
        TelaInfo_2 = new QPlainTextEdit(BoxInfo_2);
        TelaInfo_2->setObjectName(QStringLiteral("TelaInfo_2"));
        TelaInfo_2->setEnabled(true);
        TelaInfo_2->setGeometry(QRect(10, 20, 211, 211));
        TelaInfo_2->setReadOnly(true);
        label_5 = new QLabel(BoxInfo_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 240, 81, 21));
        label_objects_2 = new QLabel(BoxInfo_2);
        label_objects_2->setObjectName(QStringLiteral("label_objects_2"));
        label_objects_2->setGeometry(QRect(130, 240, 81, 21));
        label_objects_2->setLayoutDirection(Qt::LeftToRight);
        label_objects_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 127);"));
        label_objects_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        BoxCam1 = new QGroupBox(centralWidget);
        BoxCam1->setObjectName(QStringLiteral("BoxCam1"));
        BoxCam1->setGeometry(QRect(240, 0, 551, 441));
        BoxCam1_2 = new QGroupBox(centralWidget);
        BoxCam1_2->setObjectName(QStringLiteral("BoxCam1_2"));
        BoxCam1_2->setGeometry(QRect(800, 0, 551, 441));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(240, 440, 1111, 201));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 20, 1091, 171));
        groupBox_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        NameDef_1 = new QLineEdit(centralWidget);
        NameDef_1->setObjectName(QStringLiteral("NameDef_1"));
        NameDef_1->setEnabled(false);
        NameDef_1->setGeometry(QRect(260, 480, 101, 20));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        NameDef_1->setFont(font);
        NameDef_1->setAlignment(Qt::AlignCenter);
        NameDef_1->setReadOnly(true);
        NameDef_2 = new QLineEdit(centralWidget);
        NameDef_2->setObjectName(QStringLiteral("NameDef_2"));
        NameDef_2->setEnabled(false);
        NameDef_2->setGeometry(QRect(380, 480, 101, 20));
        NameDef_2->setFont(font);
        NameDef_2->setAlignment(Qt::AlignCenter);
        NameDef_2->setReadOnly(true);
        NameDef_3 = new QLineEdit(centralWidget);
        NameDef_3->setObjectName(QStringLiteral("NameDef_3"));
        NameDef_3->setEnabled(false);
        NameDef_3->setGeometry(QRect(500, 480, 101, 20));
        NameDef_3->setFont(font);
        NameDef_3->setAlignment(Qt::AlignCenter);
        NameDef_3->setReadOnly(true);
        NameDef_4 = new QLineEdit(centralWidget);
        NameDef_4->setObjectName(QStringLiteral("NameDef_4"));
        NameDef_4->setEnabled(false);
        NameDef_4->setGeometry(QRect(620, 480, 101, 20));
        NameDef_4->setFont(font);
        NameDef_4->setAlignment(Qt::AlignCenter);
        NameDef_4->setReadOnly(true);
        NameDef_5 = new QLineEdit(centralWidget);
        NameDef_5->setObjectName(QStringLiteral("NameDef_5"));
        NameDef_5->setEnabled(false);
        NameDef_5->setGeometry(QRect(740, 480, 101, 20));
        NameDef_5->setFont(font);
        NameDef_5->setAlignment(Qt::AlignCenter);
        NameDef_5->setReadOnly(true);
        NameDef_6 = new QLineEdit(centralWidget);
        NameDef_6->setObjectName(QStringLiteral("NameDef_6"));
        NameDef_6->setEnabled(false);
        NameDef_6->setGeometry(QRect(860, 480, 101, 20));
        NameDef_6->setFont(font);
        NameDef_6->setAlignment(Qt::AlignCenter);
        NameDef_6->setReadOnly(true);
        NameDef_7 = new QLineEdit(centralWidget);
        NameDef_7->setObjectName(QStringLiteral("NameDef_7"));
        NameDef_7->setEnabled(false);
        NameDef_7->setGeometry(QRect(980, 480, 101, 20));
        NameDef_7->setFont(font);
        NameDef_7->setAlignment(Qt::AlignCenter);
        NameDef_7->setReadOnly(true);
        NameDef_8 = new QLineEdit(centralWidget);
        NameDef_8->setObjectName(QStringLiteral("NameDef_8"));
        NameDef_8->setEnabled(false);
        NameDef_8->setGeometry(QRect(1100, 480, 101, 20));
        NameDef_8->setFont(font);
        NameDef_8->setAlignment(Qt::AlignCenter);
        NameDef_8->setReadOnly(true);
        NameDef_9 = new QLineEdit(centralWidget);
        NameDef_9->setObjectName(QStringLiteral("NameDef_9"));
        NameDef_9->setEnabled(false);
        NameDef_9->setGeometry(QRect(1220, 480, 101, 20));
        NameDef_9->setFont(font);
        NameDef_9->setAlignment(Qt::AlignCenter);
        NameDef_9->setReadOnly(true);
        MainWindow->setCentralWidget(centralWidget);
        groupBox->raise();
        BoxCam1_2->raise();
        BoxCam1->raise();
        BoxInfo->raise();
        PartDef_1->raise();
        ScreenResult_1->raise();
        ScreenResult_2->raise();
        PartDef_2->raise();
        PartDef_3->raise();
        PartDef_4->raise();
        PartDef_5->raise();
        PartDef_6->raise();
        PartDef_7->raise();
        PartDef_8->raise();
        PartDef_9->raise();
        BoxInfo_2->raise();
        NameDef_1->raise();
        NameDef_2->raise();
        NameDef_3->raise();
        NameDef_4->raise();
        NameDef_5->raise();
        NameDef_6->raise();
        NameDef_7->raise();
        NameDef_8->raise();
        NameDef_9->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1366, 21));
        menuArquivo = new QMenu(menuBar);
        menuArquivo->setObjectName(QStringLiteral("menuArquivo"));
        menuConfigura_es = new QMenu(menuBar);
        menuConfigura_es->setObjectName(QStringLiteral("menuConfigura_es"));
        menuSobre = new QMenu(menuBar);
        menuSobre->setObjectName(QStringLiteral("menuSobre"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuArquivo->menuAction());
        menuBar->addAction(menuConfigura_es->menuAction());
        menuBar->addAction(menuSobre->menuAction());
        menuArquivo->addAction(actionIniciar);
        menuArquivo->addAction(actionReiniciar);
        menuArquivo->addAction(actionEncerrar);
        menuArquivo->addSeparator();
        menuArquivo->addAction(actionPararContinuar);
        menuArquivo->addAction(actionCaptura_da_tela);
        menuArquivo->addSeparator();
        menuArquivo->addAction(actionSair);
        menuConfigura_es->addAction(actionAdicionar_pe_as_padr_es);
        menuConfigura_es->addSeparator();
        menuConfigura_es->addAction(actionConfigura_es_de_entrada);
        menuConfigura_es->addAction(actionConfigura_es_de_processamento);
        menuSobre->addAction(actionSobre);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TC Engenharia El\303\251trica - 2017", 0));
        actionSair->setText(QApplication::translate("MainWindow", "Sair", 0));
        actionIniciar->setText(QApplication::translate("MainWindow", "Iniciar", 0));
        actionIniciar->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", 0));
        actionConfigura_es_de_entrada->setText(QApplication::translate("MainWindow", "Configura\303\247\303\265es de entrada", 0));
        actionConfigura_es_de_processamento->setText(QApplication::translate("MainWindow", "Configura\303\247\303\265es de processamento", 0));
        actionIniciar_processamento->setText(QApplication::translate("MainWindow", "Iniciar processamento", 0));
        actionCongelar_tela->setText(QApplication::translate("MainWindow", "Congelar tela", 0));
        actionPararContinuar->setText(QApplication::translate("MainWindow", "Parar/Continuar", 0));
        actionPararContinuar->setShortcut(QApplication::translate("MainWindow", "Space", 0));
        actionCaptura_da_tela->setText(QApplication::translate("MainWindow", "Captura de frame", 0));
        actionCaptura_da_tela->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionContinuar->setText(QApplication::translate("MainWindow", "Continuar", 0));
        actionContinuar->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", 0));
        actionAdicionar_pe_as_padr_es->setText(QApplication::translate("MainWindow", "Adicionar pe\303\247as padr\303\265es", 0));
        actionSobre->setText(QApplication::translate("MainWindow", "Sobre", 0));
        actionReiniciar->setText(QApplication::translate("MainWindow", "Reiniciar", 0));
        actionReiniciar->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", 0));
        actionEncerrar->setText(QApplication::translate("MainWindow", "Encerrar tudo", 0));
        actionEncerrar->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        BoxInfo->setTitle(QApplication::translate("MainWindow", "INSPE\303\207\303\203O", 0));
        label->setText(QApplication::translate("MainWindow", "Total objetos", 0));
        label_2->setText(QApplication::translate("MainWindow", "N\303\243o definidas", 0));
        label_3->setText(QApplication::translate("MainWindow", "Pe\303\247as boas", 0));
        label_4->setText(QApplication::translate("MainWindow", "Pe\303\247as ruins", 0));
        label_good->setText(QString());
        label_bad->setText(QString());
        label_nodef->setText(QString());
        label_objects->setText(QString());
        PartDef_1->setText(QString());
        ScreenResult_1->setText(QString());
        ScreenResult_2->setText(QString());
        PartDef_2->setText(QString());
        PartDef_3->setText(QString());
        PartDef_4->setText(QString());
        PartDef_5->setText(QString());
        PartDef_6->setText(QString());
        PartDef_7->setText(QString());
        PartDef_8->setText(QString());
        PartDef_9->setText(QString());
        BoxInfo_2->setTitle(QApplication::translate("MainWindow", "RASTREAMENTO", 0));
        label_5->setText(QApplication::translate("MainWindow", "Total objetos", 0));
        label_objects_2->setText(QString());
        BoxCam1->setTitle(QApplication::translate("MainWindow", "CAMERA 1", 0));
        BoxCam1_2->setTitle(QApplication::translate("MainWindow", "CAMERA 2", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "PE\303\207AS PADR\303\225ES", 0));
        groupBox_2->setTitle(QString());
        menuArquivo->setTitle(QApplication::translate("MainWindow", "Arquivo", 0));
        menuConfigura_es->setTitle(QApplication::translate("MainWindow", "Configura\303\247\303\265es", 0));
        menuSobre->setTitle(QApplication::translate("MainWindow", "Ajuda", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
