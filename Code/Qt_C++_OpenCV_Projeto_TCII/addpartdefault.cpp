#include "addpartdefault.h"
#include "ui_addpartdefault.h"
#include "qmessagebox.h"
#include "QTimer"
#include "qdebug.h"
#include "QKeyEvent"

#include <opencv2/highgui.hpp>
#include <iostream>

#define num_max_default   9             //Maximum number of standard parts
#define max_char    5

using namespace std;
using namespace cv;

AddPartDefault::AddPartDefault(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPartDefault)
{
    ui->setupUi(this);

    LoadDefault();

    ui->NameDef_1->setInputMask("AAAAAAAAAAAAAAA;");
    ui->NameDef_2->setInputMask("AAAAAAAAAAAAAAA;");
    ui->NameDef_3->setInputMask("AAAAAAAAAAAAAAA;");
    ui->NameDef_4->setInputMask("AAAAAAAAAAAAAAA;");
    ui->NameDef_5->setInputMask("AAAAAAAAAAAAAAA;");
    ui->NameDef_6->setInputMask("AAAAAAAAAAAAAAA;");
    ui->NameDef_7->setInputMask("AAAAAAAAAAAAAAA;");
    ui->NameDef_8->setInputMask("AAAAAAAAAAAAAAA;");
    ui->NameDef_9->setInputMask("AAAAAAAAAAAAAAA;");
    ui->NameDef_1->setFocus();

}

AddPartDefault::~AddPartDefault()
{
    delete ui;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ACTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddPartDefault::on_bot_add_clicked()
{
    QPixmap imgRect1("temp/part_default1.jpg");
    if(!imgRect1.isNull()){

        if(QMessageBox::Yes == QMessageBox::question(this,
                              tr("Salvar arquivos"),
                              tr("Deseja manter as peças padrões anteriores?"))){

            QPixmap imgRect1("default/part_default1.jpg");
            QPixmap imgRect2("default/part_default2.jpg");
            QPixmap imgRect3("default/part_default3.jpg");
            QPixmap imgRect4("default/part_default4.jpg");
            QPixmap imgRect5("default/part_default5.jpg");
            QPixmap imgRect6("default/part_default6.jpg");
            QPixmap imgRect7("default/part_default7.jpg");
            QPixmap imgRect8("default/part_default8.jpg");
            QPixmap imgRect9("default/part_default9.jpg");

            int num_parts = 1;
            if(!imgRect1.isNull())
                num_parts++;
            if(!imgRect2.isNull())
                num_parts++;
            if(!imgRect3.isNull())
                num_parts++;
            if(!imgRect4.isNull())
                num_parts++;
            if(!imgRect5.isNull())
                num_parts++;
            if(!imgRect6.isNull())
                num_parts++;
            if(!imgRect7.isNull())
                num_parts++;
            if(!imgRect8.isNull())
                num_parts++;
            if(!imgRect9.isNull())
                num_parts++;

            stringstream num_picture;
            string file_name_number;

            if(num_parts<=9){
                num_picture << num_parts++;
                file_name_number = "default/part_default";
                file_name_number = file_name_number + num_picture.str() + ".jpg";
                rename("temp/part_default1.jpg", file_name_number.c_str());
            }
            if(num_parts<=9){
                num_picture.str("");
                num_picture << num_parts++;
                file_name_number = "default/part_default";
                file_name_number = file_name_number + num_picture.str() + ".jpg";
                rename("temp/part_default2.jpg", file_name_number.c_str());
            }
            if(num_parts<=9){
                num_picture.str("");
                num_picture << num_parts++;
                file_name_number = "default/part_default";
                file_name_number = file_name_number + num_picture.str() + ".jpg";
                rename("temp/part_default3.jpg", file_name_number.c_str());
            }
            if(num_parts<=9){
                num_picture.str("");
                num_picture << num_parts++;
                file_name_number = "default/part_default";
                file_name_number = file_name_number + num_picture.str() + ".jpg";
                rename("temp/part_default4.jpg", file_name_number.c_str());
            }
            if(num_parts<=9){
                num_picture.str("");
                num_picture << num_parts++;
                file_name_number = "default/part_default";
                file_name_number = file_name_number + num_picture.str() + ".jpg";
                rename("temp/part_default5.jpg", file_name_number.c_str());
            }
            if(num_parts<=9){
                num_picture.str("");
                num_picture << num_parts++;
                file_name_number = "default/part_default";
                file_name_number = file_name_number + num_picture.str() + ".jpg";
                rename("temp/part_default6.jpg", file_name_number.c_str());
            }
            if(num_parts<=9){
                num_picture.str("");
                num_picture << num_parts++;
                file_name_number = "default/part_default";
                num_picture << num_parts++;
                file_name_number = file_name_number + num_picture.str() + ".jpg";
                rename("temp/part_default7.jpg", file_name_number.c_str());
            }
            if(num_parts<=9){
                num_picture.str("");
                num_picture << num_parts++;
                file_name_number = "default/part_default";
                file_name_number = file_name_number + num_picture.str() + ".jpg";
                rename("temp/part_default8.jpg", file_name_number.c_str());
            }
            if(num_parts<=9){
                num_picture.str("");
                num_picture << num_parts++;
                file_name_number = "default/part_default";
                file_name_number = file_name_number + num_picture.str() + ".jpg";
                rename("temp/part_default9.jpg", file_name_number.c_str());
            }
        }
        else{
            remove("default/part_default1.jpg");
            remove("default/part_default2.jpg");
            remove("default/part_default3.jpg");
            remove("default/part_default4.jpg");
            remove("default/part_default5.jpg");
            remove("default/part_default6.jpg");
            remove("default/part_default7.jpg");
            remove("default/part_default8.jpg");
            remove("default/part_default9.jpg");

            rename("temp/part_default1.jpg", "default/part_default1.jpg");
            rename("temp/part_default2.jpg", "default/part_default2.jpg");
            rename("temp/part_default3.jpg", "default/part_default3.jpg");
            rename("temp/part_default4.jpg", "default/part_default4.jpg");
            rename("temp/part_default5.jpg", "default/part_default5.jpg");
            rename("temp/part_default6.jpg", "default/part_default6.jpg");
            rename("temp/part_default7.jpg", "default/part_default7.jpg");
            rename("temp/part_default8.jpg", "default/part_default8.jpg");
            rename("temp/part_default9.jpg", "default/part_default9.jpg");

            FILE *file_save;
            file_save = fopen("default/labels.txt", "w");
            fprintf(file_save, "Part 1 = ... \n");
            fprintf(file_save, "Part 2 = ... \n");
            fprintf(file_save, "Part 3 = ... \n");
            fprintf(file_save, "Part 4 = ... \n");
            fprintf(file_save, "Part 5 = ... \n");
            fprintf(file_save, "Part 6 = ... \n");
            fprintf(file_save, "Part 7 = ... \n");
            fprintf(file_save, "Part 8 = ... \n");
            fprintf(file_save, "Part 9 = ... \n");
            fclose(file_save);

        }

        LoadDefault();

    }
}

void AddPartDefault::on_bot_clear_clicked()
{
    if(QMessageBox::Yes == QMessageBox::question(this,
                          tr("Limpar arquivos"),
                          tr("Deseja realmente excluir todas peças padrões salvas?"))){

        remove("default/part_default1.jpg");
        remove("default/part_default2.jpg");
        remove("default/part_default3.jpg");
        remove("default/part_default4.jpg");
        remove("default/part_default5.jpg");
        remove("default/part_default6.jpg");
        remove("default/part_default7.jpg");
        remove("default/part_default8.jpg");
        remove("default/part_default9.jpg");

        FILE *file_save;
        file_save = fopen("default/labels.txt", "w");
        fprintf(file_save, "Part 1 = ... \n");
        fprintf(file_save, "Part 2 = ... \n");
        fprintf(file_save, "Part 3 = ... \n");
        fprintf(file_save, "Part 4 = ... \n");
        fprintf(file_save, "Part 5 = ... \n");
        fprintf(file_save, "Part 6 = ... \n");
        fprintf(file_save, "Part 7 = ... \n");
        fprintf(file_save, "Part 8 = ... \n");
        fprintf(file_save, "Part 9 = ... \n");
        fclose(file_save);

        ui->PartDef_1->clear();
        ui->PartDef_2->clear();
        ui->PartDef_3->clear();
        ui->PartDef_4->clear();
        ui->PartDef_5->clear();
        ui->PartDef_6->clear();
        ui->PartDef_7->clear();
        ui->PartDef_8->clear();
        ui->PartDef_9->clear();

        ui->NameDef_1->clear();
        ui->NameDef_2->clear();
        ui->NameDef_3->clear();
        ui->NameDef_4->clear();
        ui->NameDef_5->clear();
        ui->NameDef_6->clear();
        ui->NameDef_7->clear();
        ui->NameDef_8->clear();
        ui->NameDef_9->clear();
    }

}

void AddPartDefault::on_bot_ok_accepted()
{
    FILE *file_save;
    file_save = fopen("default/labels.txt", "w");

    if(ui->NameDef_1->text().isEmpty() || ui->PartDef_1->pixmap()->isNull())
        fprintf(file_save, "Part 1 = ... \n");
    else
        fprintf(file_save, "Part 1 = %s \n", ui->NameDef_1->text().toStdString().c_str());

    if(ui->NameDef_2->text().isEmpty() || ui->PartDef_2->pixmap()->isNull())
        fprintf(file_save, "Part 2 = ... \n");
    else
    fprintf(file_save, "Part 2 = %s \n", ui->NameDef_2->text().toStdString().c_str());

    if(ui->NameDef_3->text().isEmpty() || ui->PartDef_3->pixmap()->isNull())
        fprintf(file_save, "Part 3 = ... \n");
    else
    fprintf(file_save, "Part 3 = %s \n", ui->NameDef_3->text().toStdString().c_str());

    if(ui->NameDef_4->text().isEmpty() || ui->PartDef_4->pixmap()->isNull())
        fprintf(file_save, "Part 4 = ... \n");
    else
    fprintf(file_save, "Part 4 = %s \n", ui->NameDef_4->text().toStdString().c_str());

    if(ui->NameDef_5->text().isEmpty() || ui->PartDef_5->pixmap()->isNull())
        fprintf(file_save, "Part 5 = ... \n");
    else
    fprintf(file_save, "Part 5 = %s \n", ui->NameDef_5->text().toStdString().c_str());

    if(ui->NameDef_6->text().isEmpty() || ui->PartDef_6->pixmap()->isNull())
        fprintf(file_save, "Part 6 = ... \n");
    else
    fprintf(file_save, "Part 6 = %s \n", ui->NameDef_6->text().toStdString().c_str());

    if(ui->NameDef_7->text().isEmpty() || ui->PartDef_7->pixmap()->isNull())
        fprintf(file_save, "Part 7 = ... \n");
    else
    fprintf(file_save, "Part 7 = %s \n", ui->NameDef_7->text().toStdString().c_str());

    if(ui->NameDef_8->text().isEmpty() || ui->PartDef_8->pixmap()->isNull())
        fprintf(file_save, "Part 8 = ... \n");
    else
    fprintf(file_save, "Part 8 = %s \n", ui->NameDef_8->text().toStdString().c_str());

    if(ui->NameDef_9->text().isEmpty() || ui->PartDef_9->pixmap()->isNull())
        fprintf(file_save, "Part 9 = ... \n");
    else
    fprintf(file_save, "Part 9 = %s \n", ui->NameDef_9->text().toStdString().c_str());
    fclose(file_save);


    for(int i=0; i<num_max_default; i++){
        string file_name_number = "temp/part_default";
        stringstream num_picture;
        num_picture << i+1;
        file_name_number = file_name_number + num_picture.str() + ".jpg";

        const char *file_name_test = file_name_number.c_str();
        FILE *file_test;
        file_test = fopen(file_name_test, "w");
        if(!file_test){
            fclose(file_test);
        }
        else{
            fclose(file_test);
            remove(file_name_test);
        }
    }
    bot_ok = true;
}

void AddPartDefault::on_bot_ok_rejected()
{
    for(int i=0; i<num_max_default; i++){
        string file_name_number = "temp/part_default";
        stringstream num_picture;
        num_picture << i+1;
        file_name_number = file_name_number + num_picture.str() + ".jpg";

        const char *file_name_test = file_name_number.c_str();
        FILE *file_test;
        file_test = fopen(file_name_test, "w");
        if(!file_test){
            fclose(file_test);
        }
        else{
            fclose(file_test);
            remove(file_name_test);
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddPartDefault::LoadDefault(){

    //Clear name parts - default
    ui->NameDef_1->clear();
    ui->NameDef_2->clear();
    ui->NameDef_3->clear();
    ui->NameDef_4->clear();
    ui->NameDef_5->clear();
    ui->NameDef_6->clear();
    ui->NameDef_7->clear();
    ui->NameDef_8->clear();
    ui->NameDef_9->clear();

    //Clear name parts - photos
    ui->NumDef_1->clear();
    ui->NumDef_2->clear();
    ui->NumDef_3->clear();
    ui->NumDef_4->clear();
    ui->NumDef_5->clear();
    ui->NumDef_6->clear();
    ui->NumDef_7->clear();
    ui->NumDef_8->clear();
    ui->NumDef_9->clear();

    //Images parts - default
    QPixmap imgRect1("default/part_default1.jpg");
    ui->PartDef_1->setPixmap(imgRect1.scaled(100,100));
    QPixmap imgRect2("default/part_default2.jpg");
    ui->PartDef_2->setPixmap(imgRect2.scaled(100,100));
    QPixmap imgRect3("default/part_default3.jpg");
    ui->PartDef_3->setPixmap(imgRect3.scaled(100,100));
    QPixmap imgRect4("default/part_default4.jpg");
    ui->PartDef_4->setPixmap(imgRect4.scaled(100,100));
    QPixmap imgRect5("default/part_default5.jpg");
    ui->PartDef_5->setPixmap(imgRect5.scaled(100,100));
    QPixmap imgRect6("default/part_default6.jpg");
    ui->PartDef_6->setPixmap(imgRect6.scaled(100,100));
    QPixmap imgRect7("default/part_default7.jpg");
    ui->PartDef_7->setPixmap(imgRect7.scaled(100,100));
    QPixmap imgRect8("default/part_default8.jpg");
    ui->PartDef_8->setPixmap(imgRect8.scaled(100,100));
    QPixmap imgRect9("default/part_default9.jpg");
    ui->PartDef_9->setPixmap(imgRect9.scaled(100,100));

    //Images parts - photos
    QPixmap imgCap1("temp/part_default1.jpg");
    ui->PartCap_1->setPixmap(imgCap1.scaled(100,100));
    QPixmap imgCap2("temp/part_default2.jpg");
    ui->PartCap_2->setPixmap(imgCap2.scaled(100,100));
    QPixmap imgCap3("temp/part_default3.jpg");
    ui->PartCap_3->setPixmap(imgCap3.scaled(100,100));
    QPixmap imgCap4("temp/part_default4.jpg");
    ui->PartCap_4->setPixmap(imgCap4.scaled(100,100));
    QPixmap imgCap5("temp/part_default5.jpg");
    ui->PartCap_5->setPixmap(imgCap5.scaled(100,100));
    QPixmap imgCap6("temp/part_default6.jpg");
    ui->PartCap_6->setPixmap(imgCap6.scaled(100,100));
    QPixmap imgCap7("temp/part_default7.jpg");
    ui->PartCap_7->setPixmap(imgCap7.scaled(100,100));
    QPixmap imgCap8("temp/part_default8.jpg");
    ui->PartCap_8->setPixmap(imgCap8.scaled(100,100));
    QPixmap imgCap9("temp/part_default9.jpg");
    ui->PartCap_9->setPixmap(imgCap9.scaled(100,100));

    //Labels part
    char label_part_def[num_max_default][20];

    FILE *load_data;
    load_data = fopen("default/labels.txt", "r");
    fscanf(load_data, "Part 1 = %s \n", label_part_def[0]);
    fscanf(load_data, "Part 2 = %s \n", label_part_def[1]);
    fscanf(load_data, "Part 3 = %s \n", label_part_def[2]);
    fscanf(load_data, "Part 4 = %s \n", label_part_def[3]);
    fscanf(load_data, "Part 5 = %s \n", label_part_def[4]);
    fscanf(load_data, "Part 6 = %s \n", label_part_def[5]);
    fscanf(load_data, "Part 7 = %s \n", label_part_def[6]);
    fscanf(load_data, "Part 8 = %s \n", label_part_def[7]);
    fscanf(load_data, "Part 9 = %s \n", label_part_def[8]);

    fclose(load_data);

    //Names parts - default
    if(!imgRect1.isNull())
        ui->NameDef_1->setText(label_part_def[0]);
    if(!imgRect2.isNull())
        ui->NameDef_2->setText(label_part_def[1]);
    if(!imgRect3.isNull())
        ui->NameDef_3->setText(label_part_def[2]);
    if(!imgRect4.isNull())
        ui->NameDef_4->setText(label_part_def[3]);
    if(!imgRect5.isNull())
        ui->NameDef_5->setText(label_part_def[4]);
    if(!imgRect6.isNull())
        ui->NameDef_6->setText(label_part_def[5]);
    if(!imgRect7.isNull())
        ui->NameDef_7->setText(label_part_def[6]);
    if(!imgRect8.isNull())
        ui->NameDef_8->setText(label_part_def[7]);
    if(!imgRect9.isNull())
        ui->NameDef_9->setText(label_part_def[8]);

    //Names parts - photos
    if(!imgCap1.isNull())
        ui->NumDef_1->setText("1");
    if(!imgCap2.isNull())
        ui->NumDef_2->setText("2");
    if(!imgCap3.isNull())
        ui->NumDef_3->setText("3");
    if(!imgCap4.isNull())
        ui->NumDef_4->setText("4");
    if(!imgCap5.isNull())
        ui->NumDef_5->setText("5");
    if(!imgCap6.isNull())
        ui->NumDef_6->setText("6");
    if(!imgCap7.isNull())
        ui->NumDef_7->setText("7");
    if(!imgCap8.isNull())
        ui->NumDef_8->setText("8");
    if(!imgCap9.isNull())
        ui->NumDef_9->setText("9");

}

void AddPartDefault::keyPressEvent(QKeyEvent *e){

    switch (e->key()) {
    case Qt::Key_Enter:
        ui->bot_ok->setFocus();
        break;
    case Qt::Key_Return:
        ui->bot_ok->setFocus();
        break;
    case Qt::Key_Escape:
        ui->bot_ok->setFocus();
        break;
    case Qt::Key_Space:
        ui->bot_ok->setFocus();
        break;
    }
}
