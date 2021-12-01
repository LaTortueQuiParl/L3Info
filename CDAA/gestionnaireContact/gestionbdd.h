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
     */
    void recreateTable();

    /**
     * @brief clearTables drop toutes les tables et les recréée, utilisé pour avoir des tests sur des tables vides
     */
    void clearTables();

    /**
     * @brief insertData permet d'exécuter des requêtes d'insertions
     * @param table La table dans laquelle on veut insérer des données
     * @param m Une map de QVariant qui représente les données à insérer
     */
    void insertData(Contact c);
    void insertData(Interaction i);
    void insertData(Todo t);

    /**
     * @brief selectQuery permet de faire créer et exécuter des selects
     * @param c Le contact que l'on cherche dans la table
     * Fait par défaut
     */
    list<Contact> selectQuery(string table, map<string, string> conditions);
};

#endif // GESTIONBDD_H
