#ifndef GESTIONCONTACTS_H
#define GESTIONCONTACTS_H

#include<list>
#include "contact.h"
#include "date.h"

using namespace std;

/**
 * @brief La classe gestionContacts.
 * @class GestionContacts
 * Cette classe contient tous les contacts existants sous forme de liste.
 */
class GestionContacts
{
private:
    list<Contact*> listContact;
    Date derniereSuppr;

public:
    /**
     * @brief Le constructeur de GestionContacts.
     */
    GestionContacts();

    /**
     * @brief getContacts renvoie la liste de tous les contacts.
     * @return La liste de tous les contacts.
     */
    list<Contact*> const getContacts();

    /**
     * @brief getDerniereSuppr permet de récupérer la date de la dernière suppression, vaut par défaut la date de la création de l'instance
     * @return la date de la dernière suppression
     */
    Date getDerniereSuppr();

    /**
     * @brief setContacts permet de définir une nouvelle liste de contact.
     * @param lc est la nouvelle liste de contact.
     * La fonction trie automatiquement la nouvelle liste si besoin.
     */
    void setContacts(list<Contact*> &lc);

    /**
     * @brief resetDernModif permet de mettre la date de la dernière modification à la date courante
     */
    void resetDernSuppr();

    /**
     * @brief addContact permet d'insérer un contact dans la liste des contacts.
     * @param c est le contact à ajouter dans la liste de contact.
     * La fonction lance une exception 'std::invalid_argument' lorsque le contact à ajouter est déjà dans la liste.
     * Le contact ajouté est mis à la fin puis la liste est de nouveau triée si le contact ajouté n'est pas déjà présent
     */
    void addContact(Contact &c);

    /**
     * @brief supprContact permet de supprimer un contact de la liste
     * @param c est le contact à supprimer de la liste de contact
     */
    void supprContact(Contact &c);
};

#endif // GESTIONCONTACTS_H
