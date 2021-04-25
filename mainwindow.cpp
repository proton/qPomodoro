#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->trayIcon = new QSystemTrayIcon(this);
    this->trayIcon->setIcon(QIcon(":/icon.png"));
    this->trayIcon->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

