#include "lescontacts.h"

LesContacts::LesContacts()
{

}

list<Contact> const LesContacts::getContacts(){
    return this->lContact;
}

void  LesContacts::setContacts(const list<Contact> &lc){
    this->lContact = lc;
}

void LesContacts::addContact(const Contact &c){
    this->lContact.push_back(c);
}

void LesContacts::supprContact(Contact &c){
    for(auto v=this->lContact.begin() ; v!=this->lContact.end();){
        if(*v==c){
            v = this->lContact.erase(v);
        }else
            ++v;
    }
    this->derniereSuppr=Date(time(nullptr));
}
