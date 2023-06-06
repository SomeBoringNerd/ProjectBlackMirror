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
#include <QCameraInfo>
#include <QtWidgets/QApplication>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaContent>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <QApplication>
#include <QMediaPlayer>
#include <QVideoWidget>

QSqlDatabase db;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    db = QSqlDatabase::addDatabase("QMYSQL", "MyConnect");
    db.setHostName("192.168.1.3");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("plaqueihm2.0");

    // PlaceHolder pour les différentes espaces d'écritures
   /* ui->Nom_Ajouter->setPlaceholderText("Nom");
    ui->Prenom_Ajouter->setPlaceholderText("Prénom");
    ui->Plaque_Immatriculation->setPlaceholderText("XX-000-XX");
    ui->Nom_User_Insctiption->setPlaceholderText("Nom d'utilisateur");
    ui->Password_Inscription->setPlaceholderText("Mot de passe");
    ui->Nom_User_Connexion->setPlaceholderText("Nom d'utilisateur");
    ui->Password_Connexion->setPlaceholderText("Mot de passe");*/

    camera = new QCamera;
    QWidget  *widget = new QWidget ;
    QVBoxLayout *layout = new QVBoxLayout;
    setCentralWidget(widget);
/*
    QMediaPlayer mediaPlayer;
    mediaPlayer.setVideoOutput(widget);
     //mediaPlayer.setMedia(QUrl("rtsp://192.168.1.2:554"));
*/
    QCameraViewfinder *viewfinder = new QCameraViewfinder;
    viewfinder->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    viewfinder->setMinimumSize(260, 180);
    camera->setViewfinder(viewfinder);

    camera->start();

    layout->addWidget(viewfinder);
    widget->setLayout(layout);

    ui->setupUi(this);

    ui->stackedWidget->insertWidget(6, widget);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ######################### Bouton de la Partie MENU PRINCIPALE ####################################

void MainWindow::on_Ouvrir_clicked()
{
    QMessageBox::information(this, "Ouverture", "le portail est bien ouvert");
}

void MainWindow::on_Signaler_clicked()
{
    QMessageBox::information(this, "Alerte", "Alerte Intrusion !!");
}


void MainWindow::on_Admin_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);

}


void MainWindow::on_Exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Arrêt du logiciel", "Vous êtes sur de vouloir fermer l'application?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

void MainWindow::on_Camera_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

// ######################### Bouton de la Partie CONNEXION ####################################

void MainWindow::on_Inscription_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_Menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Connexion_clicked()
{
    QString Nom_User = ui->Nom_User_Connexion->text();
    QString _Password = ui->Password_Connexion->text();

    if (db.open())
    {
        // Creating My quereis
        // QMessageBox::information(this, "Database Success", "Database Connection Success");
        QSqlQuery query(QSqlDatabase::database("MyConnect"));

        query.prepare(QString("SELECT * FROM administrateur WHERE Nom_User = :Nom_User"));

        query.bindValue(":Nom_User", Nom_User);

        if (!query.exec())
        {
            QMessageBox::information(this, "Failed", "Query Failed to Execute");
        }
        else
        {
            while (query.next())
            {
                QString User = query.value(0).toString();
                QString Password = query.value(1).toString();

                if (_Password == Password)
                {
                    QMessageBox::information(this, "Réussi", "Réussite de l’ouverture de session");

                    ui->stackedWidget->setCurrentIndex(3);
                }
                else
                {
                    QMessageBox::information(this, "Mot de passe incorrect", "Échec d’ouverture de session");
                }
            }
        }
    }
    else
    {

        QMessageBox::information(this, "Échec de la base de données", "Échec de la connexion à la base de données");
    }
}


// ######################### Bouton de la Partie INSCRIPTION ####################################

void MainWindow::on_Menu_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_Retour_Inscription_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_Sinscrire_clicked()
{
    if (db.open())
    {
        // Récupérer les données des champs d'entrée
        QString Nom_User = ui->Nom_User_Inscription->text();
        QString Password = ui->Password_Inscription->text();

        QSqlQuery qry;

        qry.prepare("INSERT INTO administrateur( Nom_User, Password)  VALUES(:Nom_User, :Password )");

        qry.bindValue(":Nom_User", Nom_User);
        qry.bindValue(":Password", Password);

        if (!(Nom_User == "" || Password == ""))
        {
            if (qry.exec())
            {
                QMessageBox::information(this, "Inscription", "Un nouvel administrateur a bien été inscrit");
                ui->stackedWidget->setCurrentIndex(1);
            }
            else
            {
                QMessageBox::information(this, "échec", "Une erreur est survenue");
            }
        }

        else
        {

            QMessageBox::information(this, "Non insérée", "Les données existent déja");
        }
    }
    else
    {

        QMessageBox::information(this, "Base de donnée", "La base de donnée n'est pas connecté");
    }
}


// ######################### Bouton de la Partie MENU ADMIN ####################################

void MainWindow::on_Ajouter_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_Deconnexion_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Déconnexion", "Vous etes sur de vouloir vous déconnecter ?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        ui->stackedWidget->setCurrentIndex(0);
        QMessageBox::information(this, "Déconnexion", "La déconnexion de votre conte a bien été effectué");
    }
}


void MainWindow::on_Historique_clicked()
{
     ui->stackedWidget->setCurrentIndex(6);
}



void MainWindow::on_Retour_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::affichageDonneeUtilisateur()
{
    QSqlQuery requete;
    int ligne(0);

    requete.exec("SELECT * FROM personnel where Profession = Autre Visiteurs");

    while (requete.exec())
    {
        ligne=requete.value(0).toInt();

    }

    modele = new QStandardItemModel(ligne, 6);

    requete.exec("SELECT Prenom, Nom, Profession, Date_Debut, Date_Fin, Plaque_Immatriculation FROM personnel ");

    while (requete.next())
    {
        for(int j=0; j<6; j++)
        {
            QStandardItem *item=new QStandardItem(requete.value(j).toString());
            modele->setItem(ligne, j, item);
        }
    }

    modele->setHeaderData(0, Qt::Horizontal, "Prenom" );
    modele->setHeaderData(1, Qt::Horizontal, "Nom" );
    modele->setHeaderData(2, Qt::Horizontal, "Profession" );
    modele->setHeaderData(3, Qt::Horizontal, "Date_Debut" );
    modele->setHeaderData(4, Qt::Horizontal, "Date_Fin" );
    modele->setHeaderData(5, Qt::Horizontal, "Plaque_Immatriculation" );

    ui->tableView->setModel(modele);
}

void MainWindow::on_actionCamera_2_toggled(bool arg1)
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_actionCamera_3_toggled(bool arg1)
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_actionMenu_principal_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

