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
     * @todo Vérifier que le liste est trier et la trier si besoin. Envoyer une erreur si il y a des doublons?
     */
    void setContacts(const list<Contact*> &lc);

    /**
     * @brief resetDernModif permet de mettre la date de la dernière modification à la date courante
     */
    void resetDernSuppr();

    /**
     * @brief addContact permet d'insérer un contact dans la liste des contacts.
     * @param c est le contact à ajouter dans la liste de contact.
     * La fonction lance une exception 'std::invalid_argument' lorsque l'interaction à ajouter est déjà dans la liste.
     * La fonction doit donc toujours être dans un try et catch pour pouvoir gérer l'exception sinon quoi le programme se termine
     */
    void addContact(Contact &c);

    /**
     * @brief supprContact permet de supprimer un contact de la liste
     * @param c est le contact à supprimer de la liste de contact
     * @todo faire des exceptions pour savoir si il y a réellement eu une suppression ou non
     */
    void supprContact(Contact &c);
};

#endif // GESTIONCONTACTS_H
