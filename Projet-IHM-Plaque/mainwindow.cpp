#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logger.h"
#include "QMessageBox"
#include "Qtstring"
#include <qsqlquery>
#include <QSqlDatabase>

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



void MainWindow::on_pushButton_clicked()
{

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_textEdit_copyAvailable(bool b)
{

}

