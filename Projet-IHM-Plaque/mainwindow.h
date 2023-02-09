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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_textEdit_copyAvailable(bool b);

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
