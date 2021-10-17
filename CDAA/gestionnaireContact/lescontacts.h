#ifndef LESCONTACTS_H
#define LESCONTACTS_H

#include<list>
#include "contact.h"

using namespace std;

class LesContacts
{
private:
    list<Contact> lContact;

public:
    LesContacts();

    list<Contact> const getContacts();

    void setContacts(const list<Contact> &);

    void addContacts(const Contact &);
};

#endif // LESCONTACTS_H
