#include "gestionbdd.h"
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include <QVector>

GestionBDD::GestionBDD()
{
    connexionBDD();
    createTables();
}

void GestionBDD::connexionBDD()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../gestionnaireContact/mabase.sqlite");
    if(!db.open())
        throw invalid_argument("Pas de connexion BDD!");
}
GestionBDD::~GestionBDD(){
    db.close();
}

QSqlDatabase GestionBDD::getDb() const
{
    return db;
}

void GestionBDD::createTables(){
    string tableContact = "CREATE TABLE IF NOT EXISTS Contact( "
                          "id integer PRIMARY KEY,"
                          "nom varchar(255) NOT NULL,"
                          "prenom varchar(255) NOT NULL,"
                          "entreprise varchar(255) NOT NULL,"
                          "telephone integer NOT NULL,"
                          "photo varchar(255) NOT NULL,"
                          "mail varchar(255) NOT NULL"
                          " )";

    string tableInteraction = "CREATE TABLE IF NOT EXISTS Interaction ( "
                              "id integer PRIMARY KEY,"
                              "contenu varchar(255) NOT NULL,"
                              "date varchar(255) NOT NULL,"
                              "contact integer NOT NULL,"
                              "gestionTodos integer,"
                              "CONSTRAINT cle_etrangere FOREIGN KEY(contact) REFERENCES Contact(id) ON DELETE CASCADE"
                              " )";

    string tableTodo = "CREATE TABLE IF NOT EXISTS Todo ( "
                       "id integer PRIMARY KEY,"
                       "contenu varchar(255) NOT NULL,"
                       "deadline varchar(255) NOT NULL,"
                       "interaction integer,"
                       "CONSTRAINT cle_etrangere FOREIGN KEY(interaction) REFERENCES Interaction(id) ON DELETE CASCADE"
                       " );";

    QSqlQuery qContact;
    if (!qContact.exec(QString::fromStdString(tableContact)))
        throw invalid_argument("Impossible de creer la table Contact");
    QSqlQuery qInteraction;
    if (!qInteraction.exec(QString::fromStdString(tableInteraction)))
        throw invalid_argument("Impossible de creer la table Interaction");
    QSqlQuery qTodo;
    if (!qTodo.exec(QString::fromStdString(tableTodo)))
        throw invalid_argument("Impossible de creer la table Todo");
}

void GestionBDD::clearTables()
{
    QSqlQuery qDelAll;
    if (!qDelAll.exec("DELETE FROM Contact"))
        throw invalid_argument("Impossible de vider la table contact");
    if (!qDelAll.exec("DELETE FROM Interaction"))
        throw invalid_argument("Impossible de vider la table interaction");
    if (!qDelAll.exec("DELETE FROM Todo"))
        throw invalid_argument("Impossible de vider la table todo");
}

void GestionBDD::insertData(string table, Contact c){
    QSqlQuery qInsert;
    qInsert.prepare(QString("INSERT INTO %1(id, Nom, Prenom, Entreprise, Telephone, Photo, Mail) "
                                "VALUES(:id, :Nom, :Prenom, :Entreprise, :Telephone, :Photo, :Mail)").arg(QString::fromStdString(table)));
    //qInsert.bindValue(":table", QString::fromStdString(table));
    qInsert.bindValue(":id", 1);
    qInsert.bindValue(":Nom", QString::fromStdString(c.getNom()));
    qInsert.bindValue(":Prenom", QString::fromStdString(c.getPrenom()));
    qInsert.bindValue(":Entreprise", QString::fromStdString(c.getEntreprise()));
    qInsert.bindValue(":Telephone", QString::fromStdString(c.getTelephone()));
    qInsert.bindValue(":Photo", QString::fromStdString(c.getPhoto()));
    qInsert.bindValue(":Mail", QString::fromStdString(c.getMail()));
    if (!qInsert.exec())
        throw invalid_argument("Impossible d'exécuter la requete insert");
}
