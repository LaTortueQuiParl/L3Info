#include "gestionbdd.h"
#include <QDebug>
#include <QSqlRecord>
#include <QtSql>
#include <QMap>

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

    string tableInteraction = "CREATE TABLE IF NOT EXISTS Interaction( "
                              "id integer PRIMARY KEY,"
                              "contenu varchar(255) NOT NULL,"
                              "date varchar(255) NOT NULL,"
                              "idContact integer NOT NULL"
                              //"CONSTRAINT cle_etrangere FOREIGN KEY(contact) REFERENCES Contact(id) ON DELETE CASCADE"
                              " )";

    string tableTodo = "CREATE TABLE IF NOT EXISTS Todo( "
                       "id integer PRIMARY KEY,"
                       "contenu varchar(255) NOT NULL,"
                       "deadline varchar(255) NOT NULL,"
                       "idInteraction integer"
                       //"CONSTRAINT cle_etrangere FOREIGN KEY(interaction) REFERENCES Interaction(id) ON DELETE CASCADE"
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
    sizeContact = 0;
    sizeInteraction = 0;
    sizeTodo = 0;
}

void GestionBDD::recreateTable(){
    QSqlQuery qDropTable;
    if (!qDropTable.exec("DROP TABLE Contact"))
        throw invalid_argument("Impossible de supprimer la table Contact");
    if (!qDropTable.exec("DROP TABLE Interaction"))
        throw invalid_argument("Impossible de supprimer la table Interaction");
    if (!qDropTable.exec("DROP TABLE Todo"))
        throw invalid_argument("Impossible de supprimer la table Todo");
    createTables();
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
    sizeContact = 0;
    sizeInteraction = 0;
    sizeTodo = 0;
}

void GestionBDD::insertData(Contact c){
    QSqlQuery qInsert;
    qInsert.prepare("INSERT INTO Contact(id, Nom, Prenom, Entreprise, Telephone, Photo, Mail) "
                    "VALUES(:id, :Nom, :Prenom, :Entreprise, :Telephone, :Photo, :Mail)");
    qInsert.bindValue(":id", sizeContact+1);
    qInsert.bindValue(":Nom", QString::fromStdString(c.getNom()));
    qInsert.bindValue(":Prenom", QString::fromStdString(c.getPrenom()));
    qInsert.bindValue(":Entreprise", QString::fromStdString(c.getEntreprise()));
    qInsert.bindValue(":Telephone", QString::fromStdString(c.getTelephone()));
    qInsert.bindValue(":Photo", QString::fromStdString(c.getPhoto()));
    qInsert.bindValue(":Mail", QString::fromStdString(c.getMail()));
    if (!qInsert.exec())
        throw invalid_argument("Impossible d'executer la requete insert dans Contact");
    sizeContact++;
}

void GestionBDD::insertData(Interaction i){
    Contact c = *i.getContact();
    QSqlQuery qIdContact;
    qIdContact.prepare("SELECT * FROM Contact WHERE Nom=:Nom AND Prenom=:Prenom AND Entreprise=:Entreprise "
                       "AND Telephone=:Telephone AND Photo=:Photo");
    qIdContact.bindValue(":Nom", QString::fromStdString(c.getNom()));
    qIdContact.bindValue(":Prenom", QString::fromStdString(c.getPrenom()));
    qIdContact.bindValue(":Entreprise", QString::fromStdString(c.getEntreprise()));
    qIdContact.bindValue(":Telephone", QString::fromStdString(c.getTelephone()));
    qIdContact.bindValue(":Photo", QString::fromStdString(c.getPhoto()));
    qIdContact.bindValue(":Mail", QString::fromStdString(c.getMail()));

    if (!qIdContact.exec())
        throw invalid_argument("Impossible de faire une selection dans Contact pour recuperer l'ID du contact de l'interaction");

    if (qIdContact.isValid() == false)
        qIdContact.next();

    QSqlQuery qInsert;
    qInsert.prepare("INSERT INTO Interaction(id, contenu, date, idContact) "
                    "VALUES(:id, :contenu, :date, :idContact)");
    qInsert.bindValue(":id", sizeInteraction + 1);
    qInsert.bindValue(":contenu", QString::fromStdString((i.getContenu())));
    qInsert.bindValue(":date", QString::fromStdString(i.getDateCreation().affichage()));
    qInsert.bindValue(":idContact", qIdContact.value(0).toString());
    if (!qInsert.exec())
        throw invalid_argument("Impossible d'executer la requete insert dans Interaction");
    sizeInteraction++;
}

list<Contact> GestionBDD::selectQuery(string table, map<string, string> stProjection){
    QSqlQuery qSelect;
    QMap<string, string> projection(stProjection);
    list<Contact> res;
    QString conditions = "";
    if (projection.empty() == true){
        qSelect.prepare("SELECT nom, prenom, entreprise, telephone, photo, mail FROM Contact");
    } else {
        /*
        qSelect.prepare("SELECT nom, prenom, entreprise, telephone, photo, mail FROM Contact WHERE nom='Ratu'"); // solution 1

        qSelect.prepare("SELECT nom, prenom, entreprise, telephone, photo, mail FROM Contact WHERE :condition"); // solution 2
        qSelect.bindValue(":condition", "nom='Ratu'");
        */
        QMapIterator<string, string> condition(projection);
        while (condition.hasNext()){
            condition.next();
            conditions.append(QString("%1='%2'").arg(QString::fromStdString(condition.key()), QString::fromStdString(condition.value())));
            if (projection.size() != 1 && condition.value() != projection.last()){
                conditions.append(" AND ");
            }
        }
        qSelect.prepare(QString("SELECT nom, prenom, entreprise, telephone, photo, mail FROM %1 WHERE %2").arg(QString::fromStdString(table), conditions));
    }
    if (!qSelect.exec()){
        throw invalid_argument((QString("Impossible de selectionner les donnees de contact avec pour condition %1").arg(conditions)).toStdString());
    } else {
        while (qSelect.next()){
            Contact c(qSelect.value(0).toString().toStdString(),
                      qSelect.value(1).toString().toStdString(),
                      qSelect.value(2).toString().toStdString(),
                      qSelect.value(3).toString().toStdString(),
                      qSelect.value(4).toString().toStdString(),
                      qSelect.value(5).toString().toStdString());
            res.push_back(c);
        }
    }
    return res;
}
