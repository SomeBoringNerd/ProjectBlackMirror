#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QSqlquery>
#include <QLabel>
#include <Qstring>
#include <QDialogButtonBox>
#include <QSqlDatabase>
#include <QComboBox>
#include <QSql>
#include <QDate>
#include <QStringList>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Affichage_Donnee_Autre_Visiteurs();

    ui->Nom_Ajouter->setPlaceholderText("Nom");
    ui->Prenom_Ajouter->setPlaceholderText("Prénom");
    ui->Plaque_Immatriculation->setPlaceholderText("Plaque");
    ui->Nom_User_Inscription->setPlaceholderText("Nom d'utilisateur");
    ui->Password_Inscription->setPlaceholderText("Mot de passe");
    ui->Nom_User_Connexion->setPlaceholderText("Nom d'utilisateur");
    ui->Password_Connexion->setPlaceholderText("Mot de passe");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Placeholder text


//Placeholder text




//#######Partie MENU PRINCIPALE ####################################
void MainWindow::on_Ouvrir_clicked()
{
    QMessageBox::information(this,"Ouverture","le portail est bien ouvert");
}


void MainWindow::on_Signaler_clicked()
{
    QMessageBox::information(this,"Alerte","Alerte Intrusion !!");
}


void MainWindow::on_Quitter_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Arrêt du logiciel", "Vous etes sur de vouloir fermer l'application?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}


void MainWindow::on_Admin_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


// ################################ Partie CONNEXION ADMIN ####################################


void MainWindow::on_Menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_Inscription_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_Connexion_clicked()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL", "MyConnect");
    db.setHostName("localhost");
    //db.setPort(3306);
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("plaqueihm2.0");

    QString Nom_User = ui->Nom_User_Connexion->text();
    QString Password = ui->Password_Connexion->text();


    if(db.open())
    {
        // Creating My quereis
        //QMessageBox::information(this, "Database Success", "Database Connection Success");
        QSqlQuery query(QSqlDatabase::database("MyConnect"));

        query.prepare(QString("SELECT * FROM administrateur WHERE Nom_User = :Nom_User AND Password = :Password"));

        query.bindValue(":Nom_User", Nom_User);
        query.bindValue(":Password", Password);

        if(!query.exec())

        {
            QMessageBox::information(this, "Failed", "Query Failed to Execute");
        }else {


                while(query.next()) {


                    QString User = query.value(0).toString();
                    QString Password = query.value(1).toString();

                    if(User == User && Password == Password) {

                        QMessageBox::information(this, "Réussi", "Réussite de l’ouverture de session");
                        //query.prepare(QString("SELECT * FROM utilisateur"));

                        //dexieme page
                        ui->stackedWidget->setCurrentIndex(3);
                    }
                    else
                    {
                        QMessageBox::information(this, "Echec", "Échec d’ouverture de session");



                    }


                }




        }

}
else
{

    QMessageBox::information(this, "Échec de la base de données", "Échec de la connexion à la base de données");
}
}





// ############################ Partie INSCRIPTION ADMIN ####################################



void MainWindow::on_Retour_Connexion_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_Menu_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_Sinscrire_clicked()
{
    // Connexion à la base de donnée quand les informations de la partie Inscription, Connexion et Ajouter seront rentrés
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    // database.setPort(3306);
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("plaqueihm2.0");

    if(database.open())
    {
        // Récupérer les données des champs d'entrée
        QString Nom_User = ui->Nom_User_Inscription->text();
        QString Password = ui->Password_Inscription->text();


        // Exécutez notre requête d'insertion

        QSqlQuery qry;

        qry.prepare("INSERT INTO administrateur( Nom_User, Password)  VALUES(:Nom_User, :Password )");



        // lier la valeur

        qry.bindValue(":Nom_User", Nom_User);
        qry.bindValue(":Password", Password);


        if (!(Nom_User == "" ||  Password == "" ))
        {
            if(qry.exec()){
                QMessageBox::information(this,"Inscription","Un nouvel administrateur a bien été inscrit");
                 ui->stackedWidget->setCurrentIndex(1);


            }
            else{
                    QMessageBox::information(this,"échec","Une erreur est survenue");
            }



        }

        else {

            QMessageBox::information(this, "Non insérée", "Les données existent déja");


        }
        database.close();
        QSqlDatabase::removeDatabase("QMYSQL");

    }
    else {

        QMessageBox::information(this, "Base de donnée", "La base de donnée n'est pas connecté");
    }
}


// ################### Partie ADMINISTRATEUR ###########################################

void MainWindow::on_Dconnexion_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Déconnexion", "Vous etes sur de vouloir vous déconnecter ?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        ui->stackedWidget->setCurrentIndex(0);
        QMessageBox::information(this, "Déconnexion", "La déconnexion de votre conte a bien été effectué");
    }
}

void MainWindow::on_Historique_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_Ajouter_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

// ########################### Partie AJOUTER ########################################


void MainWindow::on_Annuler_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_Enregistrer_clicked()
{
    // Connexion à la base de donnée quand les informations de la partie Inscription, Connexion et Ajouter seront rentrés
     database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setPort(3306);
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("plaqueihm2.0");

    if(database.open())
    {
        // Récupérer les données des champs d'entrée
        QString Prenom = ui->Prenom_Ajouter->text();
        QString Nom = ui->Nom_Ajouter->text();
        QString Profession = ui->Profession_Ajouter->currentText();
        QDate Date_Debut = ui->Date_Debut->date();
        QDate Date_Fin = ui->Date_Fin->date();
        QString Plaque_Immatriculation = ui->Plaque_Immatriculation->text();


        // Exécutez notre requête d'insertion

        QSqlQuery qry;

        qry.prepare("INSERT INTO personnel( Prenom, Nom, Profession, Date_Debut, Date_Fin, Plaque_Immatriculation)  VALUES(:Prenom, :Nom, :Profession, :Date_Debut, :Date_Fin, :Plaque_Immatriculation )");



        // lier la valeur

        qry.bindValue(":Prenom", Prenom);
        qry.bindValue(":Nom", Nom);
        qry.bindValue(":Profession", Profession);
        qry.bindValue(":Date_Debut", Date_Debut);
        qry.bindValue(":Date_Fin", Date_Fin);
        qry.bindValue(":Plaque_Immatriculation", Plaque_Immatriculation);
/*

        qry.prepare(QString("SELECT * FROM personnel WHERE Plaque_Immatriculation = :Plaque_Immatriculation"));

        qry.bindValue(":Plaque_Immatriculation", Plaque_Immatriculation);

         QString nPlaque_Immatriculation = qry.value(7).toString();

*/


        if (!(Prenom == "" || Nom == "" ||  Profession == "" ||  Plaque_Immatriculation == "" ))
        {
            if(qry.exec()){
                QMessageBox::information(this,"Ajouter","Un nouveau visiteur a bien été enregistré");
                 ui->stackedWidget->setCurrentIndex(3);


            }
            else{
                    QMessageBox::information(this,"Echec","Une erreur est survenue");
            }


        }

        else {

            QMessageBox::information(this, "Non insérée", "Les données existent déja");


        }
        database.close();
        QSqlDatabase::removeDatabase("QMYSQL");

    }
    else {

        QMessageBox::information(this, "base de donnée", "La base de donnée n'est pas connecté");
    }
}


//"""############################# Partie HISTORIQUE ##############################
/*
void Affichage_Donnée_Autre_Visiteurs(){
   QSqlQuery requete; int ligne (0);
    int modele (0);
    requete.exec("SELECT * FROM personnel WHERE Profession = :Autre Visiteurs  ");
    while (requete.next()) {
        ligne=  requete.value(0).toInt();

    }
    modele = new QStandardItemModel(ligne, 3);
    int row(0);
    requete.exec("SELECT * FROM personnel WHERE Profession = :Autre Visiteurs");
    while (requete.exec()) {
        for (int j = 0; j < 3; ++j) {
            QStandardItem *item=new QStandardItem(requete.value(j).toString());
            modele->setItem(row, j, item);

        }
        row ++;
    }
}*/




void MainWindow::on_Retour_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_viewfinder_customContextMenuRequested(const QPoint &pos)
{

}

