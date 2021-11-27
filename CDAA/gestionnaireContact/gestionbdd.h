#ifndef GESTIONBDD_H
#define GESTIONBDD_H

#include <string>
#include <map>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

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

    void clearTables();

    void insertData(string table, map<string, string>);

    /**
     * @brief selectQuery permet de faire créer et exécuter des selects
     * @param attribute Le ou les attributs que l'on veut récupérer
     * @param table La table dans laquelle on veut faire un select
     * @param condition La condition dans la where si il y a
     */
    void selectQuery(string attribute, string table, string condition = "");
};

#endif // GESTIONBDD_H
