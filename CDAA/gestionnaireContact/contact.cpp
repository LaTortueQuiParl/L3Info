#include "contact.h"

Contact::Contact(const string &n, const string &p, const string &e, const string &t, const string &ph, const string &m)
{
    this->setNom(n);
    this->setPrenom(p);
    this->setEntreprise(e);
    this->setMail(m);
    this->setTelephone(t);
    this->setPhoto(ph);
    time_t tmm = time(0);
    this->dateCrea = localtime(&tmm);

}
Contact::~Contact(){lesInteractions.~interaction();}

string const Contact::getNom(){return this->nom;}
string const Contact::getPrenom(){return this->prenom;}
string const Contact::getEntreprise(){return this->entreprise;}
string const Contact::getTelephone(){return this->telephone;}
string const Contact::getPhoto(){return this->photo;}
string const Contact::getMail(){return this->mail;}
tm Contact::getDateCrea(){return *this->dateCrea;}
interaction const Contact::getInteraction(){return this->lesInteractions;};

void Contact::setNom(const string &n){if(!n.empty()) this->nom=n;}
void Contact::setPrenom(const string &p){if(!p.empty()) this->prenom=p;}
void Contact::setEntreprise(const string &e){if(!e.empty()) this->entreprise=e;}
void Contact::setMail(const string &m){if(!m.empty()) this->mail=m;}
void Contact::setTelephone(const string &t){if(!t.empty()) this->nom=t;}
void Contact::setPhoto(const string &ph){if(!ph.empty()) this->nom=ph;}

void Contact::setInteration(const interaction &i){this->lesInteractions=i;};
