#ifndef CONTACT_H
#define CONTACT_H
#include <string>
#include <list>
#include <iostream>
#include <ctime>
#include "lesinteractions.h"

using namespace std;

class Contact
{
private:
    string nom, prenom, entreprise, mail, telephone, photo;
    LesInteractions lesInteractions ;

    tm *dateCrea;
public:
    Contact(const string &, const string &, const string &, const string &, const string &, const string &);
    ~Contact();

    string const getNom();
    string const getPrenom();
    string const getEntreprise();
    string const getTelephone();
    string const getPhoto();
    string const getMail();
    LesInteractions const getInteraction();
    tm getDateCrea();

    void setNom(const string &);
    void setPrenom(const string &);
    void setEntreprise(const string &);
    void setMail(const string &);
    void setTelephone(const string &);
    void setPhoto(const string &);
    void setInteration(const Interaction &);

    friend ostream &operator<<(ostream &os, Contact &c){
        return os << c.getNom() << c.getPrenom() << c.getEntreprise() << c.getMail() << (string) c.getTelephone() << c.getPhoto();
    }
};

#endif // CONTACT_H
