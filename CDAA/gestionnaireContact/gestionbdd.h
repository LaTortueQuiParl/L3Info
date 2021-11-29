#ifndef GESTIONBDD_H
#define GESTIONBDD_H

#include <string>
#include <map>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "contact.h"
#include <QVariant>

using namespace std;

/**
 * @brief La classe GestionBDD qui gère tout ce qui est lié aux bases de données
 * @class GestionBDD
 */
class GestionBDD
{
private:
    QSqlDatabase db;
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
     * @brief clearTables drop toutes les tables et les recréée, utilisé pour avoir des tests sur des tables vides
     */
    void clearTables();

    /**
     * @brief insertData permet d'exécuter des requêtes d'insertions
     * @param table La table dans laquelle on veut insérer des données
     * @param m Une map de QVariant qui représente les données à insérer
     */
    void insertData(string table, Contact obj);

    /**
     * @brief selectQuery permet de faire créer et exécuter des selects
     * @param attribute Le ou les attributs que l'on veut récupérer
     * @param table La table dans laquelle on veut faire un select
     * @param condition La condition dans la where si il y a
     */
    void selectQuery(string attribute, string table, string condition = "");
};

#endif // GESTIONBDD_H
