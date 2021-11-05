#include "gestioncontacts.h"

GestionContacts::GestionContacts()
{
    this->listContact = {};
    resetDernSuppr();
}

list<Contact*> const GestionContacts::getContacts(){
    return this->listContact;
}

Date GestionContacts::getDerniereSuppr(){
    return this->derniereSuppr;
}

struct ContactComparator
{
    bool operator ()(Contact &c1, Contact &c2){
        return c1.getDateCrea() < c2.getDateCrea();
    }
};

void  GestionContacts::setContacts(list<Contact*> &lc){
    this->listContact = lc;
    listContact.sort([] (Contact *c1, Contact *c2){
        return c1->getDateCrea() < c2->getDateCrea();
    });
}

void GestionContacts::resetDernSuppr(){
    this->derniereSuppr = Date();
}

void GestionContacts::addContact(Contact &c){
    if (this->getContacts().empty() == true) {
        this->listContact.push_back(&c);
        return;
    }
    for(auto v=this->listContact.begin() ; v!=this->listContact.end(); v++){
        if (**v == c){
            throw invalid_argument("ce contact { "
                                   + c.getNom() + " " + c.getPrenom()
                                   + " } est deja dans la liste");
        }
    }
    this->listContact.push_back(&c);
    this->listContact.sort([](Contact *c1, Contact *c2){
        return c1->getDateCrea() < c2->getDateCrea();
    });
}

void GestionContacts::supprContact(Contact &c){
    bool t = false;
    for(auto v=this->listContact.begin() ; v!=this->listContact.end(); ++v){
        if(**v==c && *v==&c){
            v = this->listContact.erase(v);
            t = true;
        }
    }
    if (t == false)
        throw invalid_argument("le contact n'a pas ete suprime car il n'etait pas dans la liste");
    this->derniereSuppr=Date();
}
