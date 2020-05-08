#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void MainProcess();
    void LoadConfigProcess();
    void LoadDefault();
    void LoadDefault_compare();

    void on_actionSair_triggered();
    void on_actionIniciar_triggered();
    void on_actionPararContinuar_triggered();
    void on_actionCaptura_da_tela_triggered();
    void on_actionConfigura_es_de_entrada_triggered();
    void on_actionConfigura_es_de_processamento_triggered();
    void on_actionAdicionar_pe_as_padr_es_triggered();
    void on_actionSobre_triggered();
    void on_actionReiniciar_triggered();
    void on_actionEncerrar_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
