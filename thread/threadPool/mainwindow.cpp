#include "mainwindow.h"
#include <QRunnable>
#include <QThread>
#include <QThreadPool>
class CustomTask: public QRunnable{
public:
    CustomTask()
    {
        setAutoDelete(true);
    }
    void run() override
    {
        qDebug()<<"run task from thread"<<QThread::currentThread();
    }
};



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    CustomTask *task0 = new CustomTask;
    CustomTask *task1 = new CustomTask;
    CustomTask *task2 = new CustomTask;
    // use this
    // QThreadPool::globalInstance()->setMaxThreadCount(2);
    QThreadPool::globalInstance()->start(task0);
    QThreadPool::globalInstance()->start(task1);
    QThreadPool::globalInstance()->start(task2);
}

MainWindow::~MainWindow() {}
