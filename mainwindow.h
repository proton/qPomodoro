#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_shortBreakStartButton_clicked();
    void on_longBreakStartButton_clicked();
    void on_pomodoroStartButton_clicked();
    void on_toggle();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void timerTick();

private:
    Ui::MainWindow *ui;
    int time_left = 0;
    QString timer_message;
    QTimer* timer;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *toggleAction;
    QAction *quitAction;
    QAction *shortBreakAction;
    QAction *longBreakAction;
    QAction *pomodoroAction;

    void setupTrayIcon();

    void startTimer(int minutes, QString& finish_text, QIcon& icon);
    void actualizeTimeText();
};
#endif // MAINWINDOW_H
