#include "mywork.h"
#include <QDebug>
#include <QThread>
MyWork::MyWork(QObject *parent)
    : QObject{parent}
{}

void MyWork::working()
{
    qDebug()<<"current thread id"<<QThread::currentThreadId();
    int num = 0;
    while(1)
    {
        emit curNumber(num++);
        if(num == 1000000000)
        {
            break;
        }
        QThread::usleep(1);
    }
    qDebug()<< "run() finish, subthread exit";
}
