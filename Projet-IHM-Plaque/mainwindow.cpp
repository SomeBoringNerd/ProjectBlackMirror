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

    initLogger("ClientQT");
    Log("Logiciel lancé");
}

MainWindow::~MainWindow()
{
    delete ui;
}



/* Présentation des différente pages :
 * Page 0 : Menu d'accueil pour l'agent d'accueil
 * Page 1 : page "Ajouter" pour la partie Admin
 * Page 2 : Page "Connexion" pour la partie Admin
 * Page 3 : Page "Inscription" pour la partie Admin
 * Page 4 : Menu d'accueil pour la partie Admin */


// void MainWindow::on_textEdit_nom_ajouter_copyAvailable(bool b)
//{

//}


void MainWindow::on_pushButton_Ouvrir_Menu_clicked() // Le bouton Ouvir du menu est appuyé, envoie un message de confirmation à l'utilisateur
{
    QMessageBox::information(this,"message","le portail est bien ouvert");
}

void MainWindow::on_pushButton_2_Ajouter_Menu_clicked() // Bouton Ajouter qui est relier à la page Ajouter
{
     ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_4_Signaler_Menu_clicked() // Bouton Signaler cliqué, envoie un message d'intrusion à l'utilisateur
{
    QMessageBox::information(this,"message","Alerte Intrusion !!");
}


void MainWindow::on_pushButton_Annuler_Ajouter_clicked() // Si le bouton annuler de la page Ajouter est cliqué, efface tout
{
     ui->lineEdit_2_Non_Ajouter->setText("");
     ui->lineEdit_Prenom_Ajouter->setText("");
     ui->lineEdit_Plaque_Ajouter->setText("");
}


void MainWindow::on_pushButton_3_enregistrer_clicked() // Bouton Enregistrer cliqué, renvoie un message confirmant l'enregistrement
{
    QMessageBox::information(this,"enregistrer","L'enregistrement a bien été effectué");
    ui->stackedWidget->setCurrentIndex(4);
}




void MainWindow::on_pushButton_3_Connexion_clicked() //Bouton de la page Connexion cliqué, ramène l'utilisateur à la page Ajouter
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_Annuler_Connexion_clicked() // Bouton Annuler cliqué, efface tout dans la page Connexion
{
    ui->lineEdit_2_NonUser_Connexion->setText("");
    ui->lineEdit_2_MotDePasse_Connexion->setText("");
}




void MainWindow::on_pushButton_Retour_Connexion_clicked() //Bouton retour cliqué, retourne à la page d'accueil
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_2_Inscription_Connexion_clicked() // Bouton Inscription cliqué, revoie vers la page Inscription
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_2_Retour_Inscription_clicked() // Bouton Inscription cliqué, renvoie à la page de menu
{
    ui->stackedWidget->setCurrentIndex(0);
}





void MainWindow::on_pushButton_Ajouter_Admin_clicked() //Bouton Ajouter cliqué, renvoie à la page Ajouter
{
    ui->stackedWidget->setCurrentIndex(1);
}

