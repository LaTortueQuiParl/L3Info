#ifndef GESTIONBDD_H
#define GESTIONBDD_H

#include <string>
#include <map>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "contact.h"
#include "interaction.h"
#include "todo.h"

using namespace std;

/**
 * @brief La classe GestionBDD qui gère tout ce qui est lié aux bases de données
 * @class GestionBDD
 */
class GestionBDD
{
private:
    QSqlDatabase db;
    int sizeContact;
    int sizeInteraction;
    int sizeTodo;
public:
    /**
     * @brief GestionBDD le constructeur qui lance automatiquement connexionBDD
     */
    GestionBDD();

    ~GestionBDD();
    /**
     * @brief connexionBDD permet de se connecter à la bdd
     */
    void connexionBDD();
    /**
     * @brief getDb renvoie la db
     * @return La db
     */
    QSqlDatabase getDb() const;
    /**
     * @brief permet de créer les tables utiles pour le projet
     */
    void createTables();

    /**
     * @brief recreateTable permet de supprimer toutes les tables et les recréer pour faire des updates sur les tables
     * N'a pas d'utilité pratique dans le projet mais permet de modifier la BDD si l'on en a besoin
     */
    void recreateTable();

    /**
     * @brief clearTables drop toutes les tables et les recréée, utilisé pour avoir des tests sur des tables vides
     */
    void clearTables();

    /**
     * @brief insertData permet d'exécuter des requêtes d'insertions
     * @param c/i/t Un objet qui est soit un contact, une interaction soit un todo
     * La fonction est surchargée pour pouvoir insérer les 3 types d'objets qui sont : Contact, Interaction, Todo
     */
    void insertData(Contact c);
    void insertData(Interaction i);
    void insertData(Todo t);

    /**
     * @brief selectQueryContact permet de créer et exécuter des selects dans la table Contact
     * @param Les conditions de la selection qui est vide par défaut
     */
    list<Contact> selectQueryContact(map<string, list<string>> condition = {});

    /**
     * @brief selectQueryInteraction permet de créer et exécuter des selects dans la table Interaction
     * @param Les conditions de la selection qui est vide par défaut
     */
    list<Interaction> selectQueryInteraction(map<string, list<string>> condition = {});

    /**
     * @brief selectQueryTodo permet de créer et exécuter des selects dans la table Todo
     * @param Les conditions de la selection qui est vide par défaut
     */
    list<Todo> selectQueryTodo(map<string, list<string>> condition = {});

    void updateData(string nomTable, map<string, string> modifications, map<string, list<string>> conditions = {});

    int countTable(string nomTable);

    list<Interaction> selectInteractionEntreDeuxDates(Date d1, Date d2);
};

#endif // GESTIONBDD_H
