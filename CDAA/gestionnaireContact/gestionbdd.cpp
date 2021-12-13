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
                          "telephone integer NOT NULL UNIQUE,"
                          "photo varchar(255) NOT NULL,"
                          "mail varchar(255) NOT NULL"
                          " )";

    string tableInteraction = "CREATE TABLE IF NOT EXISTS Interaction( "
                              "id integer PRIMARY KEY,"
                              "contenu varchar(255) NOT NULL,"
                              "date varchar(255) NOT NULL,"
                              "idContact integer NOT NULL,"
                              "CONSTRAINT cle_etrangere FOREIGN KEY(idContact) REFERENCES Contact(id) ON DELETE CASCADE"
                              " )";

    string tableTodo = "CREATE TABLE IF NOT EXISTS Todo( "
                       "id integer PRIMARY KEY,"
                       "contenu varchar(255) NOT NULL,"
                       "deadline varchar(255) NOT NULL,"
                       "idInteraction integer,"
                       "CONSTRAINT cle_etrangere FOREIGN KEY(idInteraction) REFERENCES Interaction(id) ON DELETE CASCADE"
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

QString getIdContact(Contact c){
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
        throw invalid_argument("Impossible de faire une selection dans Interaction pour recuperer l'ID du contact de l'interaction");

    if (qIdContact.isValid() == false && !qIdContact.next())
        throw invalid_argument("Aucun contact n'a ete trouve");

    return qIdContact.value(0).toString();
}

void GestionBDD::insertData(Interaction i){
    QSqlQuery qInsert;
    qInsert.prepare("INSERT INTO Interaction(id, contenu, date, idContact) "
                    "VALUES(:id, :contenu, :date, :idContact)");
    qInsert.bindValue(":id", sizeInteraction + 1);
    qInsert.bindValue(":contenu", QString::fromStdString((i.getContenu())));
    qInsert.bindValue(":date", QString::fromStdString(i.getDateCreation().affichage()));
    qInsert.bindValue(":idContact", getIdContact(*i.getContact()));
    if (!qInsert.exec())
        throw invalid_argument("Impossible d'executer la requete insert dans Interaction");
    sizeInteraction++;
}

void GestionBDD::insertData(Todo t){
    Interaction i = *t.getInteraction();
    QSqlQuery qIdInteraction;
    qIdInteraction.prepare("SELECT * FROM Interaction WHERE Contenu=:Contenu AND Date=:Date "
                           "AND idContact=idContact");
    qIdInteraction.bindValue(":Contenu", QString::fromStdString(i.getContenu()));
    qIdInteraction.bindValue(":Date", QString::fromStdString(i.getDateCreation().affichage()));
    qIdInteraction.bindValue(":idContact", getIdContact(*i.getContact()));

    if (!qIdInteraction.exec())
        throw invalid_argument("Impossible de recuprer l'interaction associee au todo ");
    else{
        if (qIdInteraction.isValid() == false && qIdInteraction.next() == false)
            throw invalid_argument("Aucune interaction n'a ete trouve pour inserer un todo");
        else {
            QSqlQuery qInsert;
            qInsert.prepare("INSERT INTO Todo(id, contenu, deadline, idInteraction) "
                            "VALUES(:id, :contenu, :deadline, :idInteraction)");
            qInsert.bindValue(":id", sizeTodo + 1);
            qInsert.bindValue(":contenu", QString::fromStdString(t.getContenu()));
            qInsert.bindValue(":deadline", QString::fromStdString(t.getDeadline().affichage()));
            qInsert.bindValue(":idInteraction", qIdInteraction.value(0).toString());
            if (!qInsert.exec())
                throw invalid_argument("Impossible d'inserer le todo");
            sizeTodo++;
        }
    }
}

QString craftSelect(string table, map<string, list<string>> mapConditions = {}){
    QMap<string, list<string>> QmapConditions(mapConditions);
    QString conditions = "";
    if (QmapConditions.empty() == true){
        if (table == "Contact")
            return QString("SELECT nom, prenom, entreprise, telephone, photo, mail FROM %1").arg(QString::fromStdString(table));
        else if (table == "Interaction")
            return QString("SELECT contenu, date, idContact FROM %1").arg(QString::fromStdString(table));
        else if (table == "Todo")
            return QString("SELECT contenu, deadline, idInteraction FROM %1").arg(QString::fromStdString(table));

    } else if (QmapConditions.contains("idContact") && table=="Todo"){
        return QString("SELECT contenu, deadline, idInteraction FROM Todo, Contact WHERE idContact=Contact.id");
    } else {
        QMapIterator<string, list<string>> condition(QmapConditions);
        while (condition.hasNext()){
            condition.next();
            for (list<string>::const_iterator it = condition.value().begin(); it != condition.value().end() ; it++){
                conditions.append(QString("%1='%2'").arg(QString::fromStdString(condition.key()), QString::fromStdString(*it)));
                if (*it != condition.value().back())
                    conditions.append(" OR ");
            }
            if (condition.hasNext() && condition.value() != QmapConditions.last())
                conditions.append(" AND ");
        }
    }
    if (table == "Contact")
        return QString("SELECT nom, prenom, entreprise, telephone, photo, mail FROM %1 WHERE %2").arg(QString::fromStdString(table), conditions);
    else if (table == "Interaction")
        return QString("SELECT contenu, date, idContact FROM %1 WHERE %2").arg(QString::fromStdString(table), conditions);
    else if (table == "Todo")
        return QString("SELECT contenu, deadline, idInteraction FROM %1 WHERE %2").arg(QString::fromStdString(table), conditions);
    else
        throw invalid_argument("Impossible de faire une selection sur une table qui n'existe pas dans la base de donnee");
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
    qSelect.prepare(select);
    if (!qSelect.exec()){
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

list<Todo> GestionBDD::selectQueryTodo(map<string, list<string>> mapConditions){
    QSqlQuery qSelect;
    QString select = craftSelect("Todo", mapConditions);
    list<Todo> res;
    if (!qSelect.exec(select)){
        throw invalid_argument("Impossible d'executer le select : " + select.toStdString());
    } else {
        while (qSelect.next()){
            map<string, list<string>> mapIdInteraction;
            mapIdInteraction["id"] = {qSelect.value(2).toString().toStdString()};
            Interaction todoInteraction = selectQueryInteraction(mapIdInteraction).front();
            QStringList listDeadline = qSelect.value(1).toString().split("/");
            Date deadline = Date(listDeadline.at(0).toInt(), listDeadline.at(1).toInt(), listDeadline.at(2).toInt());
            Date ajd = Date();
            if (deadline == ajd){
                Todo t = Todo(qSelect.value(0).toString().toStdString(), &todoInteraction);
                res.push_back(t);
            }
            else{
                Todo t = Todo(qSelect.value(0).toString().toStdString(), &todoInteraction, deadline);
                res.push_back(t);
            }
        }
    }
    return res;
}

void GestionBDD::updateData(string nomTable, map<string, string> modifications, map<string, list<string>> conditions){
    QSqlQuery qUpdate;
    QString qStringModifications;
    QMap<string, string> modif(modifications);
    QMapIterator<string, string> iterModif(modif);
    while(iterModif.hasNext()){
        iterModif.next();
    qStringModifications.append(QString("%1='%2'").arg(QString::fromStdString(iterModif.key()), QString::fromStdString(iterModif.value())));
        if (iterModif.hasNext() && iterModif.peekNext().value() != modif.last())
            qStringModifications.append(" ");
    }
    if (conditions.empty() == true){
        qUpdate.prepare(QString("UPDATE %1 SET %2").arg(QString::fromStdString(nomTable), qStringModifications));
        if (!qUpdate.exec())
            throw invalid_argument("Impossible de modifier la table " + nomTable);
    } else {
        QString qStringConditions;
        QMap<string, list<string>> condition(conditions);
        QMapIterator<string, list<string>> iterCondition(condition);
        while(iterCondition.hasNext()){
            iterCondition.next();
            for (auto it = iterCondition.value().begin(); it != iterCondition.value().end(); it++){
                qStringConditions.append(QString("%1='%2'").arg(QString::fromStdString(iterCondition.key()), QString::fromStdString(*it)));
                if (*it != iterCondition.value().back())
                    qStringConditions.append(" OR ");
            }
            if (iterCondition.hasNext() && iterCondition.value() != condition.last())
                qStringConditions.append(" AND ");
        }
        qUpdate.prepare(QString("UPDATE %1 SET %2 WHERE %3").arg(QString::fromStdString(nomTable), qStringModifications, qStringConditions));
        if (!qUpdate.exec())
            throw invalid_argument("Impossible de modifier la table " + nomTable);
    }
}

int GestionBDD::countTable(string nomTable){
    QSqlQuery qSelectCount;
    if (nomTable == "Contact")
        qSelectCount.prepare(QString("SELECT COUNT(Nom) FROM %1").arg(QString::fromStdString(nomTable)));
    else if (nomTable == "Interaction")
        qSelectCount.prepare(QString("SELECT COUNT(Contenu) FROM %1").arg(QString::fromStdString(nomTable)));
    else if (nomTable == "Todo")
        qSelectCount.prepare(QString("SELECT COUNT(Contenu) FROM %1").arg(QString::fromStdString(nomTable)));
    else
        throw invalid_argument("La table " + nomTable + " n'existe pas, il est donc impossible de compter ses lignes");
    if (!qSelectCount.exec())
        throw invalid_argument("Impossible de compter les " + nomTable);
    qSelectCount.next();
    int res = qSelectCount.value(0).toInt();
    return res;
}

list<Interaction> GestionBDD::selectInteractionEntreDeuxDates(Date d1, Date d2){
    QSqlQuery qSelectInteraction;
    qSelectInteraction.prepare("SELECT contenu, date, idContact FROM Interaction");
    list<Interaction> res;
    if (!qSelectInteraction.exec())
        throw invalid_argument("Impossible de recuperer les interactions enter 2 dates");
    for (int i = 0; i < this->countTable("Interaction"); i++){
        qSelectInteraction.next();
        QString qStringDateInteraction = qSelectInteraction.value(1).toString();
        QStringList contenuDateInteraction = qStringDateInteraction.split("/");
        int j = contenuDateInteraction.at(0).toInt();
        int m = contenuDateInteraction.at(1).toInt();
        int a = contenuDateInteraction.at(2).toInt();
        Date dateInteraction = Date(j, m, a);
        if ((d1 < d2 && !(dateInteraction < d1) && dateInteraction < d2) ||
                (d2 < d1 && !(dateInteraction < d2) && dateInteraction < d1)){
            map<string, list<string>> map = {{"id", {qSelectInteraction.value(2).toString().toStdString()}}};
            Contact c = selectQueryContact(map).front();
            Interaction interaction(qSelectInteraction.value(0).toString().toStdString(), c);
            interaction.setDateCreation(dateInteraction);
            res.push_back(interaction);
        }
    }
    return res;
}

list<Todo> GestionBDD::selectTodoEntreDeuxDatesPourContact(Date d1, Date d2, Contact *contact){
    QSqlQuery qSelectTodo;
    Contact tmp = Contact();
    if (!(contact == nullptr)){
        qSelectTodo.prepare("SELECT contenu, deadline, idInteraction FROM Todo WHERE :conditions");
    } else {
        qSelectTodo.prepare("SELECT contenu, deadline, idInteraction FROM Todo");
    }
    return {};
}
