#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,&MainWindow::mySignal,[=](){
        qDebug()<<"slot 3 receive signal";
    });
    connect(this,&MainWindow::mySignal,[=](){
        qDebug()<<"slot 4 receive signal";
    });
    connect(this,&MainWindow::mySignal,this,&MainWindow::mySlots0,Qt::QueuedConnection);
    connect(this,&MainWindow::mySignal,this,&MainWindow::mySlots1,Qt::QueuedConnection);
    connect(this,&MainWindow::mySignal,this,&MainWindow::mySlots2,Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mySlots0()
{
    qDebug()<<"slot0 run";
}

void MainWindow::mySlots1()
{
    qDebug()<< "slot1 run";
}

void MainWindow::mySlots2()
{
    qDebug()<< "slot2 run";
}

void MainWindow::customEvent(QEvent *event)
{

}

void MainWindow::on_pushButton_clicked()
{
    emit mySignal();
    qDebug()<<"signal send finish!";
}

