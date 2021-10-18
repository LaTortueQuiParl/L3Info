#ifndef LESINTERACTION_H
#define LESINTERACTION_H

#include "interaction.h"
#include <list>

using namespace std;

class LesInteractions
{
private:
    list<Interaction> lInteractions;

public:
    LesInteractions();

    list<Interaction> const getInteractions();

    void setInteractions(const list<Interaction> &);

    void addInteraction(const Interaction &);
};

#endif // LESINTERACTION_H
