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

    /**
     * @brief updateDate permet de faire des updates sur les tables sur tous ces éléments ou seulement certain selon les conditions précisés
     * @param nomTable Le nom de la table dans laquelle on veut effectuer une modification
     * @param modifications Une map qui contient les modifications que l'on veut faire (ex: sil map={{Prenom},{'Romain'}} modifiera le prenom en Romain)
     * @param conditions Une map qui contient les conditions pour préciser sur quels éléments de la table il faut faire une modification (ex: si map={{"Nom"}, {{"Thomas"}}} fera que Seulement les contacts ayant "Thomas" pur nom seront modifiés).
     * conditions est par défaut une liste vide. Si conditions est vide alors les modifications seront appliqués à tous les éléments de la table
     */
    void updateData(string nomTable, map<string, string> modifications, map<string, list<string>> conditions = {});

    /**
     * @brief deleteData permet de supprimer des données des tables
     * @param objet Un pointeur sur l'objet à supprimer
     * L'objet est par défaut un nullptr. Si l'objet est un nullptr, alors, selon le type du pointeur toute la table correspondant à l'objet est supprimée.
     * La méthode est surchargé pour pouvoir supprimer des contact, interaction, todo
     */
    void deleteData(Contact *contact = nullptr);
    void deleteData(Interaction *interaction = nullptr);
    void deleteData(Todo *todo = nullptr);

    /**
     * @brief countTable permet de donner le nombre d'élément de la table
     * @param nomTable Le nom de la table
     * @return Un entier qui est le nombre d'élément de la table
     */
    int countTable(string nomTable);

    /**
     * @brief selectInteractionEntreDeuxDates permet de selectionner toutes les interactions qui ont eu lieu entre 2 dates données
     * @param d1 La permière date limite
     * @param d2 La deuxième date limite
     * @return Une liste d'interaction contenant toutes les interactions qui ont eu lieu entre les 2 dates
     * Il n'y a pas de condition sur les dates tel que d1<d2 ou inversement
     */
    list<Interaction> selectInteractionEntreDeuxDates(Date d1, Date d2);

    /**
     * @brief selectTodoEntreDeuxDatesPourContact Përmet de selectionner tous les todos d'un contact qui ont eu lieu entre 2 dates données
     * @param d1 La première date limite
     * @param d2 La deuxième date limite
     * @param contact Le contact dont on veut récupérer toutes les interactions
     * @return Une liste de Todo contenant tous les Todos du contact compris entres les 2 dates limites
     */
    list<Todo> selectTodoEntreDeuxDatesPourContact(Date d1, Date d2, Contact *contact = nullptr);
};

#endif // GESTIONBDD_H
