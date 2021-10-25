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
    list<Interaction> lInteractions;
    Date dernModif;

public:
    /**
     * @brief Le constructeur de la classe GestionInteractions.
     */
    GestionInteractions();

    list<Interaction> const getInteractions();

    void setInteractions(const list<Interaction> &);

    void addInteraction(const Interaction &);

    Date getDernModif();
    void setDernModif(const Date &newDernModif);
};

#endif // LESINTERACTION_H
