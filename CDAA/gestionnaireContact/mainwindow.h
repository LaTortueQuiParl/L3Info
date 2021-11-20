#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QtSql/QSqlDatabase>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QLabel *lab;
    QSqlDatabase db;
    QPushButton *ajouter;
    QPushButton *supprimer;
    QPushButton *modifier;
    QVBoxLayout *bouton;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connexionBDD();

//private slots:
//    void on_pushButton_clicked();

};
#endif // MAINWINDOW_H
