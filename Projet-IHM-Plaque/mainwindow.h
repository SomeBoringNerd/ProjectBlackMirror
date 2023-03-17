#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:



    void on_pushButton_Ouvrir_Menu_clicked(); //Bouton Ouvrir dans la page Menu


    void on_pushButton_2_Ajouter_Menu_clicked(); // Bouton Ajouter dans la page Menu

    void on_pushButton_Annuler_Ajouter_clicked(); // Bouton Annuler dans la page Ajouter

    void on_pushButton_3_enregistrer_clicked(); // Bouton Enregistrer dans la page Ajouter

    void on_pushButton_3_Connexion_clicked(); // Bouton Connexion dans la page Connexion

    void on_pushButton_Annuler_Connexion_clicked(); // Bouton Annuler dans la page Connexion

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
};
#endif // MAINWINDOW_H

class Nom : public QMainWindow
{
public :
    Nom ();
    ~Nom ();
private:
    Nom(char);
    char nom [15];
    Ui::MainWindow *ui;
};

class Prenom : public QMainWindow
{
public :
    Prenom ();
    ~Prenom ();
private:
    Prenom(char);
    char prenom [15];
    Ui::MainWindow *ui;
};

class Nombreplaque : public QMainWindow
{
public :
    Nombreplaque ();
    ~Nombreplaque ();
private:
    Nombreplaque(char);
    char nombreplaque [15];
    Ui::MainWindow *ui;
};
