#include <QCoreApplication>
#include <QThread>
#include <QSemaphore>
#include <QRandomGenerator>
// use semaphore implement producer_consumer model
constexpr int DataSize = 100000;

constexpr int BufferSize = 8192;
char buffer[BufferSize];

QSemaphore freeBytes(BufferSize);
QSemaphore usedBytes;

class Producer : public QThread
//! [1] //! [2]
{
public:
    void run() override
    {
        for (int i = 0; i < DataSize; ++i) {
            freeBytes.acquire();
            buffer[i % BufferSize] = "ACGT"[QRandomGenerator::global()->bounded(4)];
            usedBytes.release();
        }
    }
};

class Consumer : public QThread
//! [3] //! [4]
{
public:
    void run() override
    {
        for (int i = 0; i < DataSize; ++i) {
            usedBytes.acquire();
            fprintf(stderr, "%c", buffer[i % BufferSize]);
            freeBytes.release();
        }
        fprintf(stderr, "\n");
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Producer producer;
    Consumer consumer;
    producer.start();
    consumer.start();
    producer.wait();
    consumer.wait();

    return a.exec();
}
