#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connexionBDD();
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::connexionBDD(){
    db = QSqlDatabase::addDatabase("QSQLITE");

    //attention à avoir placer le fichier dans le répertoire /tmp
    db.setDatabaseName("../tmp/base.sqlite");

      if(!db.open())
      {
          qDebug() << "Pas de connexion BDD !";
      }
      else
      {
          qDebug() << "Connexion BDD ok";
          QSqlQuery query("SELECT * from Personne");

          if(!query.exec())
          {
              qDebug() << "Impossible d'exécuter la requête !";
          }
          else
          {
              qDebug() << "Requête exécutée";
              while(query.next())
              {
                  //le value(0) est l'idPersonne
                  qDebug() << "nom : " << query.value(1).toString();
                  qDebug() << "prenom : " << query.value(2).toString();
                  qDebug() << "age : " << query.value(3).toString();
              }
          }
      }
}
*/

void MainWindow::on_pushButton_clicked()
{

}

