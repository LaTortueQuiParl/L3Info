#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>
#include <ctime>
#include <iostream>
#include "date.h"

using namespace std;

class Interaction
{
private:
    string contenu;
    Date date;
    //Contact* contact;
public:
    Interaction();
    Interaction(const string &);
    string getContenu() const;
    void setContenu(const string &);
    string getDate();

    friend ostream &operator<<(ostream &os, Interaction &i)
    {
        return os << i.getContenu() << ", " << i.getDate();
    }

};

#endif // INTERACTION_H
