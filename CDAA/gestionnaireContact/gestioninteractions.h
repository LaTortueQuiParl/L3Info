#ifndef LESINTERACTION_H
#define LESINTERACTION_H

#include "interaction.h"
#include "date.h"
#include <list>

using namespace std;

/**
 * @brief La classe GestionInteractions.
 * Cette classe contient toutes les interactions souus forme de liste.
 * @class GestionInteractions
 */
class GestionInteractions
{
private:
    list<Interaction> listInteractions;
    Date dernModif;

public:
    /**
     * @brief Le constructeur de la classe GestionInteractions.
     * Initialise la date de dernière modification à la date d'instanciation et la liste avec une liste vide.
     */
    GestionInteractions();

    /**
     * @brief getInteractions renvoie les intéractions d'un contact.
     * @return La liste d'interaction d'un contact.
     */
    list<Interaction> const getInteractions();

    /**
     * @brief getDernModif renvoie la date de dernière modification de la liste.
     * @return La date de la dernière modification
     * @todo Trier les dat
     */
    Date getDernModif();

    /**
     * @brief setInteractions permet de définir une nouvelle liste d'intéraction.
     * @param li est la nouvelle liste d'intéraction.
     */
    void setInteractions(const list<Interaction> &li);

    /**
     * @brief setDernModif permet de mettre la date de dernière modification à la date courante.
     */
    void setDernModif();

    /**
     * @brief addInteraction permet d'ajouter une interaction à la liste.
     * @param i est l'intéraction à ajouter dans la liste
     * @todo Vérifier que l'interaction à ajouter n'est pas dans la liste pour éviter les doublons
     */
    void addInteraction(const Interaction &i);

    /**
     * @brief supprInteraction permet de supprimer une interaction de la liste
     * @param i est l'interaction à supprimer
     * Utilisation d'un static cast pour convertir i en non constant et le comparer à l'itérateur.
     */
    void supprInteraction(const Interaction &i);
};

#endif // LESINTERACTION_H
