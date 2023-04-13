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
    void on_Ouvrir_clicked(); // Bouton Ouvrir du menu

    void on_Signaler_clicked(); // Bouton Signaler du menu

    void on_Quitter_clicked(); // Bouton Quitter du menu

    void on_Admin_clicked(); // Bouton Admin du menu

    void on_Menu_clicked(); // Bouton Menu Du Connexion Admin

    void on_Inscription_clicked(); // Bouton Inscription de Connexion Admin

    void on_Connexion_clicked(); // Bouton Connexion de Connexion Admin

    void on_Retour_Connexion_clicked(); // Bouton Retour de Connexion Admin

    void on_Menu_2_clicked(); // Bouton Menu 2 de Inscription Admin

    void on_Sinscrire_clicked(); // Bouton S'inscrire de Inscription Admin

    void on_Dconnexion_clicked(); // Bouton Déconnexion De Adinistrateur

    void on_Ajouter_clicked(); // Bouton Ajouter de Administrateur

    void on_Annuler_clicked(); // Bouton Annuler de Ajouter

    void on_Enregistrer_clicked(); // Bouton Enregistrer de Ajouter

   // void Affichage_Donnée_Autre_Visiteurs();

    void on_Historique_clicked();

    void on_Retour_clicked();

    void on_viewfinder_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
};
#endif // MAINWINDOW_H
