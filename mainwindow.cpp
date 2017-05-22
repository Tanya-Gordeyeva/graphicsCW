#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mywidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    widget=new MyWidget(this);
    ui->horizontalSlider_4->setMaximum(10);
    ui->horizontalSlider->setMaximum(360);
    ui->horizontalSlider_2->setMaximum(360);
    ui->horizontalSlider_3->setMaximum(360);
    ui->horizontalSlider_4->setMinimum(0);
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider_2->setMinimum(0);
    ui->horizontalSlider_3->setMinimum(0);
    ui->horizontalSlider_4->setValue(10);
    ui->horizontalSlider_2->setValue(40);
    ui->horizontalSlider_3->setValue(30);
    ui->horizontalSlider_5->setMinimum(-10);
    ui->horizontalSlider_7->setMinimum(-10);
    ui->horizontalSlider_8->setMinimum(-10);
    ui->horizontalSlider_5->setMaximum(10);
    ui->horizontalSlider_7->setMaximum(10);
    ui->horizontalSlider_8->setMaximum(10);
    ui->horizontalSlider_5->setValue(10);
    ui->horizontalSlider_7->setValue(10);
    ui->horizontalSlider_8->setValue(0);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    widget->rotateX(value);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    widget->rotateY(value);
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    widget->rotateZ(value);
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    widget->changeR(value);
}



void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{
    widget->changeX_light(value);
}

void MainWindow::on_horizontalSlider_7_valueChanged(int value)
{
    widget->changeY_light(value);
}

void MainWindow::on_horizontalSlider_8_valueChanged(int value)
{
    widget->changeZ_light(value);
}
