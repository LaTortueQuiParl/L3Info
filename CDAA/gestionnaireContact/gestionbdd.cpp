#include "gestionbdd.h"
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QDebug>

GestionBDD::GestionBDD()
{
    connexionBDD();
}

void GestionBDD::connexionBDD()
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./mabase.sqlite");
    if(!db.open()){
        qDebug() << "Pas de connexion BDD!";
    } else {
        qDebug() << "Connexion BDD ok";
    }

}

QSqlDatabase GestionBDD::getDb() const
{
    return db;
}

void GestionBDD::createTables(){
    string deleteContact = "DROP TABLE Contact;";

    string tableContact = "CREATE TABLE Contact ( ";
    tableContact.append("id integer PRIMARY KEY,");
    tableContact.append("nom varchar(255) NOT NULL,");
    tableContact.append("prenom varchar(255) NOT NULL,");
    tableContact.append("entreprise varchar(255) NOT NULL,");
    tableContact.append("telephone integer NOT NULL,");
    tableContact.append("photo varchar(255) NOT NULL,");
    tableContact.append("mail varchar(255) NOT NULL");
    tableContact.append(" )");

    string tableInteraction = "CREATE TABLE Interaction ( ";
    tableInteraction.append("id integer PRIMARY KEY,");
    tableInteraction.append("contenu varchar(255) NOT NULL,");
    tableInteraction.append("date varchar(255) NOT NULL,");
    tableInteraction.append("contact integer NOT NULL,");
    tableInteraction.append("gestionTodos integer,");
    tableInteraction.append("CONSTRAINT cle_etrangere FOREIGN KEY(contact) REFERENCES Contact(id) ON DELETE CASCADE");
    tableInteraction.append(" );");

    string tableTodo = "CREATE TABLE Todo ( ";
    tableTodo.append("id integer PRIMARY KEY,");
    tableTodo.append("contenu varchar(255) NOT NULL,");
    tableTodo.append("deadline varchar(255) NOT NULL,");
    tableTodo.append("interaction integer,");
    tableTodo.append("CONSTRAINT cle_etrangere FOREIGN KEY(interaction) REFERENCES Interaction(id) ON DELETE CASCADE");
    tableTodo.append(" );");

   // QSqlQuery qDelContact(QString::fromStdString(deleteContact));
   //if (!qDelContact.exec()){
   //    qDebug() << "Impossible de suprimer la table Contact";
   //} else {
   //    qDebug() << "Suppression de la table Contact";
   //}
   QSqlQuery qContact(QString::fromStdString(tableContact));
   if (!qContact.exec()){
       qDebug() << "Impossible de creer la table Contact";
   } else {
       qDebug() << "Creation de la table Contact";
   }
    QSqlQuery query("SELECT * FROM Contact");
   if (!query.exec()){
       qDebug() << "Impossible de suprimer la table Contact";
   } else {
       qDebug() << "Suppression de la table Contact";
   }



}
