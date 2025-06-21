#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <businesslogic.h>
#include <QIcon>
#include <QSize>
#include <QDebug>
#include <QFile>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setIconSize(QSize(148,53));
    // 验证资源是否存在
    if (QFile::exists(":/start.jpg")) {
        qDebug() << "Logo资源存在";
    } else {
        qDebug() << "Logo资源不存在";
    }
    ui->pushButton->setIcon(QIcon(":/start.jpg"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    static bool clicked = false;
    clicked = !clicked;
    if(clicked)
        ui->pushButton->setIcon(QIcon(":/start.jpg"));
    else
        ui->pushButton->setIcon(QIcon(":/stop.jpg"));
}


void MainWindow::on_pushButton_toggled(bool checked)
{
    // if(checked)
    //     ui->pushButton->setIcon(QIcon(":/start.jpg"));
    // else
    //     ui->pushButton->setIcon(QIcon(":/stop.jpg"));
}

