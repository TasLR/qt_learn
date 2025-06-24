#include "clock.h"
#include <QTimer>
#include <QTime>
#include <QPainter>
Clock::Clock(QWidget *parent)
    : QWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Clock::update));
    timer->start(1000);

    setWindowTitle(tr("Clock"));
    resize(200,200);
}

Clock::~Clock() {}

void Clock::paintEvent(QPaintEvent *event)
{
    static const QPoint hourHand[4] = {
        QPoint(5, 14),
        QPoint(-5, 14),
        QPoint(-4, -71),
        QPoint(4, -71)
    };
    static const QPoint minuteHand[4] = {
        QPoint(4, 14),
        QPoint(-4, 14),
        QPoint(-3, -89),
        QPoint(3, -89)
    };

    static const QPoint secondsHand[4] = {
        QPoint(1, 14),
        QPoint(-1, 14),
        QPoint(-1, -89),
        QPoint(1, -89)
    };

    const QColor hourColor(palette().color(QPalette::Text));
    const QColor minuteColor(palette().color(QPalette::Text));
    const QColor secondsColor(palette().color(QPalette::Accent));

    int side = qMin(width(), height());

    //! [11]
    QPainter painter(this);
    //! [11] //! [12]
    painter.setRenderHint(QPainter::Antialiasing);
    //! [12] //! [13]
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);
    //! [9] //! [13]

    //! [14]
    QTime time = QTime::currentTime();
    //! [14]

    //! [15]
    painter.setPen(Qt::NoPen);
    //! [15] //! [16]
    painter.setBrush(hourColor);
    //! [16]
    //! [18]

    //! [17]
    painter.save();
    //! [17] //! [19]
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 4);
    painter.restore();
    //! [18] //! [19]

    //! [20]
    for (int i = 0; i < 12; ++i) {
        painter.drawRect(73, -3, 16, 6);
        painter.rotate(30.0);
    }
    //! [20]

    //! [21]
    painter.setBrush(minuteColor);

    //! [22]
    painter.save();
    painter.rotate(6.0 * time.minute());
    painter.drawConvexPolygon(minuteHand, 4);
    painter.restore();
    //! [21] //! [22]


    //! [23]
    painter.setBrush(secondsColor);
    //! [23]

    //! [24]
    painter.save();
    painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(secondsHand, 4);
    painter.drawEllipse(-3, -3, 6, 6);
    painter.drawEllipse(-5, -68, 10, 10);
    painter.restore();
    //! [24]

    //! [25]
    painter.setPen(minuteColor);
    //! [25] //! [26]

    //! [27]
    for (int j = 0; j < 60; ++j) {
        painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }
}
