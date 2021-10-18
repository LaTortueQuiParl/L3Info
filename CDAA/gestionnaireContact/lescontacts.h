#ifndef LESCONTACTS_H
#define LESCONTACTS_H

#include<list>
#include "contact.h"
#include "date.h"

using namespace std;

class LesContacts
{
private:
    list<Contact> lContact;
    Date derniereSuppr;

public:
    LesContacts();

    list<Contact> const getContacts();

    void setContacts(const list<Contact> &);

    void addContact(const Contact &);

    void supprContact(const Contact &);
};

#endif // LESCONTACTS_H
