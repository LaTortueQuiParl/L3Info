#include "interaction.h"

Interaction::Interaction()
{
    setContenu("");
    time_t te= time(0);
    date = new tm(*localtime(&te));
}
Interaction::Interaction(const tm &d, const string &c){
    setContenu(c);
    date = new tm(d);
}

string Interaction::getContenu() const{
    return this->contenu;
}

void Interaction::setDate(const tm &t){
    *this->date = t;
}

void Interaction::setContenu(const string &s){
    this->contenu=s;
}
