#include "interaction.h"

Interaction::Interaction(const string &contenu, Contact &contact)
{
    setContenu(contenu);
    dateCreation = Date();
    setContact(&contact);
}
Interaction::~Interaction(){}

string Interaction::getContenu(){
    return this->contenu;
}
string Interaction::getDateCreation(){
    return to_string(this->dateCreation.getJour()) + "/" + to_string(this->dateCreation.getMois()) + "/" + to_string(this->dateCreation.getAnnee());
}
Contact* Interaction::getContact(){
    return this->contact;
}

void Interaction::setContenu(const string &c){
    this->contenu=c;
}
void Interaction::setContact(Contact *c){
    this->contact = c;
}

bool Interaction::operator==(Interaction &i){
    return i.getContact() == this->getContact() && i.getContenu() == this->getContenu() && i.getDateCreation() == this->getDateCreation();
}
