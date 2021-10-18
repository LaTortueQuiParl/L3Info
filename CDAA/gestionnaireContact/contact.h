#ifndef CONTACT_H
#define CONTACT_H
#include <string>
#include <list>
#include <iostream>
#include <ctime>
#include "date.h"
#include "lesinteractions.h"

using namespace std;

class Contact
{
private:
    string nom, prenom, entreprise, mail, telephone, photo;
    LesInteractions lesInteractions ;
    Date dateCrea;
    Date dernModif;
public:
    Contact(const string &n, const string &p, const string &e, const string &t, const string &ph, const string &mail);
    ~Contact();

    string const getNom();
    string const getPrenom();
    string const getEntreprise();
    string const getTelephone();
    string const getPhoto();
    string const getMail();
    LesInteractions const getInteraction();
    std::string getDateCrea();

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
