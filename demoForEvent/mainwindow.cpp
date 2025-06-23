#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCloseEvent> // must  be indicate specify class
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QEvent>

static QEvent::Type MyEventType = static_cast<QEvent::Type>(QEvent::User + 100);
// dynamic create one event type
// static QEvent::Type MyEventType = static_cast<QEvent::Type>(QEvent::registerEventType());

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("event demo"));
    m_action = new QAction(tr("&About"),this);
    connect(m_action, &QAction::triggered, this, &MainWindow::about);
    m_menu = new QMenu(tr("&Help"),this);
    m_menu->addAction(m_action);
    ui->menubar->addMenu(m_menu);
    this->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::event(QEvent *event)
{
    // if(event->type() == MyEventType)
    // {
    //     MyEvent *myEvent = static_cast<MyEvent*>(event);
    //     qDebug()<<"handle event deliver"<<myEvent->data();
    //     return true;
    // }
    return QWidget::event(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<< "close event accuor";
    // event->ignore();
    event->accept();//use accept/ignore, indicate that event had been handle,unwant parent widget continute to handle it
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    // if (object == this && event->type() == MyEventType) {
    //     qDebug()<<"trigger custom event filter";
    //     return true; // stop event from being processed any further.
    // }
    return false;
}
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Scribble"),
                       tr("<p>The <b>Scribble</b> example shows how to use QMainWindow as the "
                          "base widget for an application, and how to reimplement some of "
                          "QWidget's event handlers to receive the events generated for "
                          "the application's widgets:</p><p> We reimplement the mouse event "
                          "handlers to facilitate drawing, the paint event handler to "
                          "update the application and the resize event handler to optimize "
                          "the application's appearance. In addition we reimplement the "
                          "close event handler to intercept the close events before "
                          "terminating the application.</p><p> The example also demonstrates "
                          "how to use QPainter to draw an image in real time, as well as "
                          "to repaint widgets.</p>"));
}

void MainWindow::on_eventButton_clicked()
{
    // QCoreApplication::sendEvent(this,customEvent);
    // delete customEvent;
    // customEvent  = nullptr;
    QCloseEvent * closeEvent = new QCloseEvent;
    // QCoreApplication::sendEvent(this,closeEvent);
    QCoreApplication::postEvent(this,closeEvent);
    delete closeEvent;
    closeEvent  = nullptr;
}

