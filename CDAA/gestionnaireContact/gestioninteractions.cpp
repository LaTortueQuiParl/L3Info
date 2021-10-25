#include "gestioninteractions.h"


Date GestionInteractions::getDernModif()
{
    return dernModif;
}

void GestionInteractions::setDernModif(const Date &newDernModif)
{
    dernModif = newDernModif;
}

GestionInteractions::GestionInteractions()
{
}

list<Interaction> const GestionInteractions::getInteractions(){return this->lInteractions;};


void GestionInteractions::setInteractions(const list<Interaction> &l){if(!l.empty()) this->lInteractions = l;}

void GestionInteractions::addInteraction(const Interaction &i){ this->lInteractions.push_back(i);}

