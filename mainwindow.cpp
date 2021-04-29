#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icons/default.png"));
    trayIcon->show();
    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::show);
    connect(trayIcon, &QSystemTrayIcon::messageClicked, this, &MainWindow::show);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::timerTick);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_shortBreakStartButton_clicked() {
    QString text = "finish";
    QIcon icon = QIcon(":/icons/green.png");
    startTimer(5, text, icon);
}

void MainWindow::on_longBreakStartButton_clicked() {
    QString text = "finish";
    QIcon icon = QIcon(":/icons/green.png");
    startTimer(10, text, icon);
}

void MainWindow::on_pomodoroStartButton_clicked() {
    QString text = "finish";
    QIcon icon = QIcon(":/icons/red.png");
    startTimer(25, text, icon);
}

void MainWindow::timerTick() {
    --time_left;

    actualizeTimeText();

    if (time_left == 0) {
        trayIcon->showMessage(timer_message, timer_message);
        timer->stop();
        trayIcon->setIcon(QIcon(":/icons/default.png"));
        setWindowIcon(QIcon(":/icons/default.png"));
    }
}

void MainWindow::startTimer(int munutes, QString& finish_text, QIcon& icon) {
    time_left = munutes * 60;
    timer_message = finish_text;
    trayIcon->setIcon(icon);
    setWindowIcon(icon);
    actualizeTimeText();

    timer->start(1000);
}

void MainWindow::actualizeTimeText() {
    int minutes = time_left / 60;
    int seconds = time_left % 60;

    QLabel* label = findChild<QLabel*>("timeLabel");
    auto text = QString("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));
    label->setText(text);
    trayIcon->setToolTip(text);
}
