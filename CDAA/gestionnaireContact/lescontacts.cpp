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

void LesContacts::supprContact(const Contact &c){
    this->lContact.remove(c);
}
