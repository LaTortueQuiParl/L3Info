#include "interaction.h"

Interaction::Interaction(const string &contenu, Contact &contact)
{
    this->setContenu(contenu);
    this->dateCreation = Date();
    this->setContact(&contact);
}
Interaction::~Interaction(){}

string Interaction::getContenu(){
    return this->contenu;
}
Date Interaction::getDateCreation(){
    return this->dateCreation;
}
Contact* Interaction::getContact(){
    return this->contact;
}

void Interaction::setContenu(const string &c){
    if (c.empty() == true)
        throw invalid_argument("une intraction doit avoir un contenu");
    this->contenu=c;
}
void Interaction::setContact(Contact *c){
    this->contact = c;
}

void Interaction::setDateCreation(const Date d){
    this->dateCreation = d;
}

bool Interaction::operator==(Interaction &i){
    return i.getContact() == this->getContact() && i.getContenu() == this->getContenu() && i.getDateCreation() == this->getDateCreation();
}

bool Interaction::operator<(Interaction &i){
    return this->getDateCreation() < i.getDateCreation();
}
