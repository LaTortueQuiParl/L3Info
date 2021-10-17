#include "lesinteractions.h"

LesInteractions::LesInteractions()
{
}

list<interaction> const LesInteractions::getInteractions(){return this->lInteractions;};


void LesInteractions::setInteractions(const list<interaction> &l){if(!l.empty()) this->lInteractions = l;}

void LesInteractions::addInteraction(const interaction &i){ this->lInteractions.push_back(i);}
