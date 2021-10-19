#include "interaction.h"

Interaction::Interaction()
{
    setContenu("");
    date = Date(time(nullptr));
}
Interaction::Interaction(const string &c)
{
    setContenu(c);
    date = Date(time(nullptr));
}

string Interaction::getContenu() const
{
    return this->contenu;
}
void Interaction::setContenu(const string &s)
{
    this->contenu=s;
}
string Interaction::getDate()
{
    return to_string(this->date.getJour()) + "/" + to_string(this->date.getMois()) + "/" + to_string(this->date.getAnnee()) + "_" + to_string(this->date.getHeures()) + "_" + to_string(this->date.getMinutes()) + "_" + to_string(this->date.getSecondes());
}
