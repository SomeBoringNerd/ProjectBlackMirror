#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logger.h"
#include "QMessageBox"
#include <qsqlquery>
#include <QSqlDatabase>
#include <QLabel>
#include <string>
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //Clear Button Enable(icon) apres avoir ecrit dans les page Ajouter, Connexion et Inscription
     ui->lineEdit_2_Non_Ajouter->setClearButtonEnabled(true);
     ui->lineEdit_Prenom_Ajouter->setClearButtonEnabled(true);
     ui->lineEdit_Plaque_Ajouter->setClearButtonEnabled(true);
     ui->lineEdit_Nom_User_Inscription->setClearButtonEnabled(true);
     ui->lineEdit_2_Password_Inscription->setClearButtonEnabled(true);
     ui->lineEdit_2_Non_User_Connexion->setClearButtonEnabled(true);
     ui->lineEdit_2_Password_Connexion->setClearButtonEnabled(true);

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

// ###########    Connecting To SQLite Database
/* Connexion à la base de donnée quand les informations de la partie Inscription, Connexion et Ajouter seront rentrés
database = QSqlDatabase::addDatabase("SQLite");
database.setHostName("localhost");
database.setPort(3308);
database.setUserName("root");
database.setPassword("");
database.setDatabaseName("plaque");*/

// ##################### Partie MENU PRINCIPALE ####################

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

void MainWindow::on_pushButton_Quitter_Menu_clicked() // Bouton Quitter cliqué, renvoie une condition. Si l'utilisateur met YES, ferme le logiciel
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Creer un Compte", "Vous etes sur de vouloir fermer l'application?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

// ######################## Partie INSCRIPTION #############################

void MainWindow::on_pushButton_2_Retour_Inscription_clicked() // Bouton Inscription cliqué, renvoie à la page de menu
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_3_Inscrire_Inscription_clicked() // Bouton Inscription cliqué, inscrit utilisateur + ramène à la oage Connexion
{
    QMessageBox::information(this,"Inscription","Un nouvel utilisateur est inscrit");
     ui->stackedWidget->setCurrentIndex(2);
}

// #################### Partie CONNEXION ####################################

void MainWindow::on_pushButton_Retour_Connexion_clicked() //Bouton retour cliqué, retourne à la page d'accueil
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_3_Connexion_clicked() //Bouton de la page Connexion cliqué, ramène l'utilisateur à la page Ajouter
{
    ui->stackedWidget->setCurrentIndex(4);
}


// #################### Partie ADMIN ########################################

void MainWindow::on_pushButton_Retirer_Ajouter_clicked() // Si le bouton annuler de la page Ajouter est cliqué, efface tout
{
     ui->lineEdit_2_Non_Ajouter->setText("");
     ui->lineEdit_Prenom_Ajouter->setText("");
     ui->lineEdit_Plaque_Ajouter->setText("");
     ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_3_enregistrer_clicked() // Bouton Enregistrer cliqué, renvoie un message confirmant l'enregistrement
{
    QMessageBox::information(this,"enregistrer","L'enregistrement a bien été effectué");
    ui->stackedWidget->setCurrentIndex(4);
}






void MainWindow::on_pushButton_Annuler_Connexion_clicked() // Bouton Annuler cliqué, efface tout dans la page Connexion
{
    ui->lineEdit_2_Non_User_Connexion->setText("");
    ui->lineEdit_2_Password_Connexion->setText("");
}





void MainWindow::on_pushButton_2_Inscription_Connexion_clicked() // Bouton Inscription cliqué, revoie vers la page Inscription
{
    ui->stackedWidget->setCurrentIndex(3);
}




void MainWindow::on_pushButton_Ajouter_Admin_clicked() //Bouton Ajouter cliqué, renvoie à la page Ajouter
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_3_Deconnexion_Admin_clicked() // Boutton Déconnexion cliqué, renvoie une condition. Si l'utilisateur met YES, le ramène à l'accueil
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Déconnexion", "Etes vous sur de vouloir vous déconnecter?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        ui->stackedWidget->setCurrentIndex(0);
        QMessageBox::information(this,"Déconnexion","La déconnexion a bien été effectué");
    }
}



