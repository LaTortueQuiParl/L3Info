#include "gestioncontacts.h"

GestionContacts::GestionContacts()
{
    this->listContact = {};
    this->derniereSuppr = Date();
}

list<Contact> const GestionContacts::getContacts(){
    return this->listContact;
}

string GestionContacts::getDerniereSuppr(){
    return to_string(this->derniereSuppr.getJour()) + "/" + to_string(this->derniereSuppr.getMois()) + "/" + to_string(this->derniereSuppr.getAnnee());
}

void  GestionContacts::setContacts(const list<Contact> &lc){
    this->listContact = lc;
}

void GestionContacts::addContact(const Contact &c){
    this->listContact.push_back(c);
}

void GestionContacts::supprContact(Contact &c){
    for(auto v=this->listContact.begin() ; v!=this->listContact.end();){
        if(*v==c){
            v = this->listContact.erase(v);
        }else
            ++v;
    }
    this->derniereSuppr=Date();
}
