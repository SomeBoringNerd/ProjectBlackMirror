#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraViewfinder>
#include <QtSql/QSqlDatabase>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void on_viewfinder_customContextMenuRequested(const QPoint &pos);


private slots:
    void on_Ouvrir_clicked();

    void on_Signaler_clicked();

    void on_Admin_clicked();

    void on_Exit_clicked();

    void on_Camera_clicked();

    void on_Inscription_clicked();

    void on_Menu_2_clicked();

    void on_Menu_clicked();

    void on_Deconnexion_clicked();

    void on_Ajouter_clicked();

    void on_Historique_clicked();

    void on_Retour_clicked();

    void on_Retour_Inscription_clicked();

    void affichageDonneeUtilisateur();

    void on_Sinscrire_clicked();

    void on_Connexion_clicked();

    //void on_Menu_3_clicked();

    //void on_stackedWidget_currentChanged(int arg1);

    //void on_openGLWidget_aboutToCompose();

    //void on_actionCamera_2_toggled(bool arg1);

    //void on_actionCamera_3_toggled(bool arg1);

    void on_actionMenu_principal_toggled(bool arg1);

    void on_Enregistrer_clicked();

    void on_actionCamera2_triggered();

    void on_actionMenu_principal_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QStandardItemModel *modele;
};
#endif // MAINWINDOW_H
