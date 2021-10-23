#include "interaction.h"

Interaction::Interaction(const string &contenu, Contact &contact)
{
    setContenu(contenu);
    dateCreation = Date(time(nullptr));
    setContact(&contact);
}

string Interaction::getContenu()
{
    return this->contenu;
}
void Interaction::setContenu(const string &s)
{
    this->contenu=s;
}
string Interaction::getDateCreation()
{
    return to_string(this->dateCreation.getJour()) + "/" + to_string(this->dateCreation.getMois()) + "/" + to_string(this->dateCreation.getAnnee()) + "_" + to_string(this->dateCreation.getHeures()) + "_" + to_string(this->dateCreation.getMinutes()) + "_" + to_string(this->dateCreation.getSecondes());
}
void Interaction::setDateCreation(){
    this->dateCreation = Date(time(0));
}

void Interaction::setContact(Contact *newContact)
{
    contact = newContact;
}
