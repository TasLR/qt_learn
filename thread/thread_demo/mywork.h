#ifndef MYWORK_H
#define MYWORK_H

#include <QObject>

class MyWork : public QObject
{
    Q_OBJECT
public:
    explicit MyWork(QObject *parent = nullptr);

    void working();

signals:
  void  curNumber(int num);
};

#endif // MYWORK_H
