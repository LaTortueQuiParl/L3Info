#include "gestionbdd.h"
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QDebug>

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
    this->db.commit();
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

void GestionBDD::insertData(string table, map<string, string> m){

    std::pair<string, string> lastP = *m.rbegin();

    string stInsert = "INSERT INTO ";
    stInsert.append(table);
    stInsert.append("(id, ");
    for (const auto& ks : m){
        stInsert.append(ks.first);
        if (m.value_comp()(ks, lastP))
            stInsert.append(", ");
    }
    stInsert.append(") VALUES (1, ");
    for (const auto& ks : m){
        stInsert.append("'");
        stInsert.append(ks.second);
        stInsert.append("'");
        if (m.value_comp()(ks, lastP))
            stInsert.append(", ");
    }
    stInsert.append(")");
    QSqlQuery qInsert;
    if (!qInsert.exec(QString::fromStdString(stInsert))){
        qDebug() << "Impossible d'exécuter la requete : " << QString::fromStdString(stInsert);
    } else {
        qDebug() << "Requête " << QString::fromStdString(stInsert) << " effectuée";
    }
        //throw invalid_argument("Impossible d'exécuter la requete : " + stInsert);
}

void GestionBDD::selectQuery(string attribute, string table, string condition){
    string stSelect = ("SELECT ");
    stSelect.append(attribute);
    stSelect.append(" FROM ");
    stSelect.append(table);
    if (!condition.empty()){
        stSelect.append(" WHERE ");
        stSelect.append(condition);
    }
    QSqlQuery qSelect(QString::fromStdString(stSelect));
    if (!qSelect.exec()){
        qDebug() << "Impossible d'exectuer la requête : " << QString::fromStdString(stSelect);
    } else {
        qDebug() << "Selection : " << QString::fromStdString(stSelect) << "réussie";
    }
}
