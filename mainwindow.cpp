#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->trayIcon = new QSystemTrayIcon(this);
    this->trayIcon->setIcon(QIcon(":/icons/default.png"));
    this->trayIcon->show();
    connect(this->trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::show);

    this->timer = new QTimer(this);
    connect(this->timer, &QTimer::timeout, this, &MainWindow::timerTick);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_shortBreakStartButton_clicked() {
    QString text = "finish";
    QIcon icon = QIcon(":/icons/green.png");
    this->startTimer(5, text, icon);
}

void MainWindow::on_longBreakStartButton_clicked() {
    QString text = "finish";
    QIcon icon = QIcon(":/icons/green.png");
    this->startTimer(10, text, icon);
}

void MainWindow::on_pomodoroStartButton_clicked() {
    QString text = "finish";
    QIcon icon = QIcon(":/icons/red.png");
    this->startTimer(25, text, icon);
}

void MainWindow::timerTick() {
    --this->time_left;

    this->actualizeTimeText();

    if (this->time_left == 0) {
        this->trayIcon->showMessage(this->timer_message, this->timer_message);
        this->timer->stop();
        this->trayIcon->setIcon(QIcon(":/icons/default.png"));
        this->setWindowIcon(QIcon(":/icons/default.png"));
    }
}

void MainWindow::startTimer(int munutes, QString& finish_text, QIcon& icon) {
    this->time_left = munutes * 60;
    this->timer_message = finish_text;
    this->trayIcon->setIcon(icon);
    this->setWindowIcon(icon);
    this->actualizeTimeText();

    this->timer->start(1000);
}

void MainWindow::actualizeTimeText() {
    int minutes = this->time_left / 60;
    int seconds = this->time_left % 60;

    QLabel* label = this->findChild<QLabel*>("timeLabel");
    auto text = QString("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));
    label->setText(text);
    this->trayIcon->setToolTip(text);
}
