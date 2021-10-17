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

void LesContacts::addContacts(const Contact &c){
    this->lContact.push_back(c);
}
