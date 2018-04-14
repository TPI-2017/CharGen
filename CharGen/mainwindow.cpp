#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    newFile.open(nameFile.c_str(), std::ios_base::app);
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            vec[i][j] = new QCheckBox(this);
            ui->gridLayout->addWidget(vec[i][j],i, j, 6, 6);
        }
    }
    setLayout(ui->gridLayout);

    confirmBox = new QMessageBox(this);
    confirmBox->setWindowTitle("Confirmation");
    confirmBox->setText("Do you want to clear file?");
    confirmBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    QObject::connect(confirmBox, SIGNAL(finished(int)), this, SLOT(dialogIsFinished(int)));
}

MainWindow::~MainWindow()
{
    if (newFile.is_open())
        newFile.close();
    delete ui;
}

void MainWindow::on_saveButton_clicked()
{
    if (newFile.is_open())
        newFile << createCharOutput() << std::endl;
    else
        qDebug() << "Archivo no creado";
}

void MainWindow::on_resetButton_clicked()
{
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            vec[i][j]->setChecked(false);
}

void MainWindow::on_binarioRadioButton_clicked()
{
    out = type_output::BINARIO;
}

void MainWindow::on_hexRadioButton_clicked()
{
    out = type_output::HEX;
}

void MainWindow::on_clearButton_clicked()
{
    confirmBox->show();
}

std::string MainWindow::createCharOutput(){
    std::string str;
    str += "{";
    switch (out)
    {
    case type_output::BINARIO:
        str += matrixToBinario();
        break;
    case type_output::HEX:
        str += matrixToHex();
        break;
    default:
        return "";
        break;
    }
    return str + "}, // " + ui->nameInput->text().toStdString();
}

std::string MainWindow::matrixToBinario(){
    std::string str;
    for (int j = 0; j < COL; j++)
    {
        str += (j == 0)? "0b" : ", 0b";
        for (int i = ROW-1; i >= 0; i--)
            str += (vec[i][j]->isChecked()) ? "1" : "0";
    }
    return str;
}

std::string MainWindow::matrixToHex(){
    std::stringstream ss;
    std::string str;
    int num;
    for (int j = 0; j < COL; j++)
    {
        num = 0;
        str += (j == 0)? "0x" : ", 0x";
        for (int i = ROW-1; i >= 0; i--)
            num += ((vec[i][j]->isChecked()) ? 1 : 0)*pow(2,i);
        ss << std::setfill('0') << std::setw(2) << std::hex << num;
        str += ss.str();
        ss.str(""); // Elimino el contendio para usarlo en el sigte bucle
    }
    return str;
}



void MainWindow::dialogIsFinished(int result){
    if ((result == QMessageBox::Yes) and (newFile.is_open())){
        newFile.close();
        newFile.open(nameFile.c_str());
    }
}
