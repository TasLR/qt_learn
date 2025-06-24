#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>

class Clock : public QWidget
{
    Q_OBJECT

public:
    Clock(QWidget *parent = nullptr);
    ~Clock();
protected:
    void paintEvent(QPaintEvent * event) override;
};
#endif // CLOCK_H
