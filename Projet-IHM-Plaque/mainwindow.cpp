#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logger.h"
#include "QMessageBox"
#include <qsqlquery>
#include <QSqlDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //Clear Button Enable(icon) apres avoir ecrit dans la page Ajouter
     ui->lineEdit_2_Non_Ajouter->setClearButtonEnabled(true);
     ui->lineEdit_Prenom_Ajouter->setClearButtonEnabled(true);
     ui->lineEdit_Plaque_Ajouter->setClearButtonEnabled(true);

    //initLogger("ClientQT");
}

MainWindow::~MainWindow()
{
    delete ui;
}






// void MainWindow::on_textEdit_nom_ajouter_copyAvailable(bool b)
//{

//}


void MainWindow::on_pushButton_Ouvrir_Menu_clicked()
{
    QLabel *m_texte = new QLabel(); // Création de l"objet
    m_texte->setText("Vous avez ouvert le protail."); // Définition du texte
}

void MainWindow::on_pushButton_2_Ajouter_Menu_clicked() // Bouton ed Ajouter relier à la page Ajouter
{
     ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_Annuler_Ajouter_clicked() // Sile bouton annuler est cliqué
{
     ui->lineEdit_2_Non_Ajouter->setText("");
     ui->lineEdit_Prenom_Ajouter->setText("");
     ui->lineEdit_Plaque_Ajouter->setText("");
}

