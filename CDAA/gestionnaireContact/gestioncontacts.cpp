#include "gestioncontacts.h"

GestionContacts::GestionContacts()
{

}

list<Contact> const GestionContacts::getContacts(){
    return this->lContact;
}

void  GestionContacts::setContacts(const list<Contact> &lc){
    this->lContact = lc;
}

void GestionContacts::addContact(const Contact &c){
    this->lContact.push_back(c);
}

void GestionContacts::supprContact(Contact &c){
    for(auto v=this->lContact.begin() ; v!=this->lContact.end();){
        if(*v==c){
            v = this->lContact.erase(v);
        }else
            ++v;
    }
    this->derniereSuppr=Date();
}
