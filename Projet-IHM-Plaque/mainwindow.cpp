#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logger.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initLogger("ClientQT");
}

MainWindow::~MainWindow()
{
    delete ui;
}

