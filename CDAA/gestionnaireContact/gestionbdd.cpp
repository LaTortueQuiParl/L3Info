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

QString craftSelect(string table, map<string, list<string>> mapConditions){
    QMap<string, list<string>> QmapConditions(mapConditions);
    QString conditions = "";
    if (QmapConditions.empty() == true){
        if (table == "Contact")
            return QString("SELECT nom, prenom, entreprise, telephone, photo, mail FROM %1").arg(QString::fromStdString(table));
        else if (table == "Interaction")
            return QString("SELECT contenu, date, idContact FROM %1").arg(QString::fromStdString(table));
        else if (table == "Todo")
            return QString("SELECT contenu, deadline idInteractrion FROM %1").arg(QString::fromStdString(table));
    } else {
        QMapIterator<string, list<string>> condition(QmapConditions);
        while (condition.hasNext()){
            condition.next();
            for (list<string>::const_iterator it = condition.value().begin(); it != condition.value().end() ; it++){
                conditions.append(QString("%1='%2'").arg(QString::fromStdString(condition.key()), QString::fromStdString(*it)));
                if (*it != condition.value().back())
                    conditions.append(" OR ");
            }
            if (condition.hasNext() && condition.value() != QmapConditions.last()){
                conditions.append(" AND ");
            }
        }
    }
    return QString("SELECT nom, prenom, entreprise, telephone, photo, mail FROM %1 WHERE %2").arg(QString::fromStdString(table), conditions);
}

list<Contact> GestionBDD::selectQueryContact(map<string, list<string>> mapConditions){
    QSqlQuery qSelect;
    QString select = craftSelect("Contact", mapConditions);
    list<Contact> res;
    if (!qSelect.exec(select)){
        throw invalid_argument("Impossible d'executer le select : " + select.toStdString());
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

list<Interaction> GestionBDD::selectQueryInteraction(map<string, list<string>> mapConditions){
    QSqlQuery qSelect;
    QString select = craftSelect("Interaction", mapConditions);
    list<Interaction> res;
    if (!qSelect.exec(select)){
        throw invalid_argument("Impossible d'executer le select : " + select.toStdString());
    } else {
        while (qSelect.next()){
            map<string, list<string>> mapIdContact;
            mapIdContact["id"] = {qSelect.value(2).toString().toStdString()};
            Contact contactInteraction = selectQueryContact(mapIdContact).front();
            Interaction i(qSelect.value(0).toString().toStdString(),
                          contactInteraction);
            res.push_back(i);
        }
    }
    return res;
}
