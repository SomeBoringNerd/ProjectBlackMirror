#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
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
