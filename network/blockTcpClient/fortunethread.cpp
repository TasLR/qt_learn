#include <QtNetwork>
#include "fortunethread.h"
FortuneThread::FortuneThread(QObject *parent)
    : QThread(parent), quit(false)
{

}

FortuneThread::~FortuneThread()
{
    mutex.lock();
    quit = true;
    cond.wakeOne();
    mutex.unlock();
    wait();
}

void FortuneThread::requestNewFortune(const QString &hostName, quint16 port)
{
    //! [1]
    QMutexLocker locker(&mutex);
    this->hostName = hostName;
    this->port = port;
    //! [3]
    if (!isRunning())
        start();
    else
        cond.wakeOne();
}
void FortuneThread::run()
{
    mutex.lock();
    //! [4] //! [5]
    QString serverName = hostName;
    quint16 serverPort = port;
    mutex.unlock();
    //! [5]

    //! [6]
    while (!quit) {
        //! [7]
        const int Timeout = 5 * 1000;

        QTcpSocket socket;
        socket.connectToHost(serverName, serverPort);
        //! [6] //! [8]

        if (!socket.waitForConnected(Timeout)) {
            emit error(socket.error(), socket.errorString());
            return;
        }
        //! [8] //! [11]

        QDataStream in(&socket);
        in.setVersion(QDataStream::Qt_6_5);
        QString fortune;
        //! [11] //! [12]

        do {
            if (!socket.waitForReadyRead(Timeout)) {
                emit error(socket.error(), socket.errorString());
                return;
            }

            in.startTransaction();
            in >> fortune;
        } while (!in.commitTransaction());
        //! [12] //! [15]

        mutex.lock();
        emit newFortune(fortune);
        //! [7]

        cond.wait(&mutex);
        serverName = hostName;
        serverPort = port;
        mutex.unlock();
    }
    //! [15]
}
