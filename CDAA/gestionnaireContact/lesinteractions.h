#ifndef LESINTERACTION_H
#define LESINTERACTION_H

#include "interaction.h"
#include <list>

using namespace std;

class LesInteractions
{
private:
    list<interaction> lInteractions;

public:
    LesInteractions();

    list<interaction> const getInteractions();

    void setInteractions(const list<interaction> &);

    void addInteraction(const interaction &);
};

#endif // LESINTERACTION_H
