#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtSql/QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connexionBDD();

    ajouter = new QPushButton("Ajouter", this);
    supprimer = new QPushButton("Supprimer", this);
    modifier = new QPushButton("Modifier", this);
    /*
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    bouton = new QVBoxLayout();
    bouton->addWidget(ajouter);
    bouton->addWidget(supprimer);
    bouton->addWidget(modifier);

    mainLayout->addLayout(bouton);

    setLayout(mainLayout);
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connexionBDD(){
    db = QSqlDatabase::addDatabase("QSQLITE");

    //attention à avoir placer le fichier dans le répertoire /tmp
    db.setDatabaseName("../gestionnaireContact/mabase.sqlite");

    if(!db.open())
    {
        qDebug() << "Pas de connexion BDD !";
    }
    else
    {
        qDebug() << "Connexion BDD ok";

        /*
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
        */
    }
}
