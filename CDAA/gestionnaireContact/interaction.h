#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>
#include <ctime>
#include <iostream>

//#include "contact.h"

using namespace std;

class Interaction
{
private:
    string contenu;
    tm* date;
    //Contact* contact;
public:
    Interaction();
    Interaction(const tm &, const string &);
    string getContenu() const;
    void setContenu(const string &);
    tm* getDate() const;
    void setDate(const tm &);

    friend ostream &operator<<(ostream &os, const Interaction &i){
        return os << i.getContenu() + "," + asctime(i.getDate());
    }

};

#endif // INTERACTION_H
