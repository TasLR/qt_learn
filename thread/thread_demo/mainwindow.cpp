#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include "mywork.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<< "main thread id:"<<QThread::currentThreadId();

    //create thread
    QThread *workThread = new QThread;
    MyWork *work = new MyWork;
    work->moveToThread(workThread);

    workThread->start();

    connect(ui->pushButton,&QPushButton::clicked,work,&MyWork::working);
    connect(work,&MyWork::curNumber,this,[=](int num){
        ui->label->setNum(num);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
