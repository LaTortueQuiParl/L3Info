#include "lesinteractions.h"

LesInteractions::LesInteractions()
{
}

list<Interaction> const LesInteractions::getInteractions(){return this->lInteractions;};


void LesInteractions::setInteractions(const list<Interaction> &l){if(!l.empty()) this->lInteractions = l;}

void LesInteractions::addInteraction(const Interaction &i){ this->lInteractions.push_back(i);}
