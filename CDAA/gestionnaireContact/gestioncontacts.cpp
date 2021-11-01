#include "gestioncontacts.h"

GestionContacts::GestionContacts()
{
    this->listContact = {};
    resetDernSuppr();
}

list<Contact> const GestionContacts::getContacts(){
    return this->listContact;
}

Date GestionContacts::getDerniereSuppr(){
    return this->derniereSuppr;
}

void  GestionContacts::setContacts(const list<Contact> &lc){
    this->listContact = lc;
}

void GestionContacts::resetDernSuppr(){
    this->derniereSuppr = Date();
}

void GestionContacts::addContact(const Contact &c){
    Contact cc = c;
    for(auto v=this->listContact.begin() ; v!=this->listContact.end(); v++){
        if (*v == cc){
            throw invalid_argument("Ce contact { "
                                   + cc.getNom() + " " + cc.getPrenom()
                                   + " } est deja dans la liste");
            return;
        }
    }
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
