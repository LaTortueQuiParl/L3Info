#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>
#include <ctime>
#include <iostream>
#include "contact.h"

using namespace std;

class Interaction
{
private:
    string contenu;
    Date dateCreation;
    Contact* contact;

public:
    Interaction(const string &contenu, Contact &contact);
    string getContenu();
    void setContenu(const string &);
    string getDateCreation();
    void setDateCreation();

    friend ostream &operator<<(ostream &os, Interaction &i)
    {
        return os << i.getContenu() << ", " << i.getDateCreation();
    }
    void setContact(Contact *newContact);
};

#endif // INTERACTION_H
