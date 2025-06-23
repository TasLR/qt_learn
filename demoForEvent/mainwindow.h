#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class QScrollArea;
class QMenu;
class QAction;
class MyEvent;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    bool event(QEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    bool eventFilter(QObject *object, QEvent *event) override;
    // void customEvent(MyEvent *event);
private slots:
    void about();
    void on_eventButton_clicked();

private:
    Ui::MainWindow *ui;
    QMenu *m_menu;
    QAction *m_action;
};
#endif // MAINWINDOW_H
