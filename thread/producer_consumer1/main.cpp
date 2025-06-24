#include <QCoreApplication>
#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QRandomGenerator>
#include <QThread>
#include <QWaitCondition>

#include <stdio.h>
#include <stdlib.h>

constexpr int DataSize = 100000;
constexpr int BufferSize = 8192;

QMutex mutex; // protects the buffer and the counter
char buffer[BufferSize];
int numUsedBytes;

QWaitCondition bufferNotEmpty;
QWaitCondition bufferNotFull;
//! [0]

//! [1]
class Producer : public QThread
{
public:
    explicit Producer(QObject *parent = nullptr)
        : QThread(parent)
    {
    }

private:
    void run() override
    {
        for (int i = 0; i < DataSize; ++i) {
            {
                const QMutexLocker locker(&mutex);
                while (numUsedBytes == BufferSize)
                    bufferNotFull.wait(&mutex);
            }

            buffer[i % BufferSize] = "ACGT"[QRandomGenerator::global()->bounded(4)];

            {
                const QMutexLocker locker(&mutex);
                ++numUsedBytes;
                bufferNotEmpty.wakeAll();
            }
        }
    }
};
class Consumer : public QThread
//! [3] //! [4]
{
public:
    explicit Consumer(QObject *parent = nullptr)
        : QThread(parent)
    {
    }

private:
    void run() override
    {
        for (int i = 0; i < DataSize; ++i) {
            {
                const QMutexLocker locker(&mutex);
                while (numUsedBytes == 0)
                    bufferNotEmpty.wait(&mutex);
            }

            fprintf(stderr, "%c", buffer[i % BufferSize]);

            {
                const QMutexLocker locker(&mutex);
                --numUsedBytes;
                bufferNotFull.wakeAll();
            }
        }
        fprintf(stderr, "\n");
    }
};
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.
    Producer producer;
    Consumer consumer;
    producer.start();
    consumer.start();
    producer.wait();
    consumer.wait();

    return a.exec();
}
