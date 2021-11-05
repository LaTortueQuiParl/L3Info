#include "contact.h"

Contact::Contact(){}

Contact::Contact(const string &n, const string &p, const string &e, const string &t, const string &ph, const string &mail)
{
    this->setNom(n);
    this->setPrenom(p);
    this->setEntreprise(e);
    this->setTelephone(t);
    this->setPhoto(ph);
    this->setMail(mail);
    this->dateCrea = Date();
    this->dernModif = Date();
    this->gestionInteractions = GestionInteractions();
}
Contact::~Contact(){
    this->dateCrea.~Date();
    this->dernModif.~Date();
}

string const Contact::getNom()
{
    return this->nom;
}
string const Contact::getPrenom()
{
    return this->prenom;
}
string const Contact::getEntreprise()
{
    return this->entreprise;
}
string const Contact::getTelephone()
{
    return this->telephone;
}
string const Contact::getPhoto()
{
    return this->photo;
}
string const Contact::getMail()
{
    return this->mail;
}
Date Contact::getDateCrea()
{
    return this->dateCrea;
}
Date Contact::getDernModif()
{
    return this->dernModif;
}
GestionInteractions Contact::getInteractions()
{
    return this->gestionInteractions;
}

void Contact::setNom(const string &n)
{
    if(n.empty())
        throw invalid_argument("le contact doit avoir un nom");
    this->nom=n;
    this->dernModif=Date();
}
void Contact::setPrenom(const string &p)
{
    if(p.empty())
        throw invalid_argument("le contact doit avoir un prenom");
    this->prenom=p;
    this->dernModif=Date();
}
void Contact::setEntreprise(const string &e)
{
    if(e.empty())
        throw invalid_argument("le contact doit avoir une entreprise");
    this->entreprise=e;
    this->dernModif=Date();
}
void Contact::setTelephone(const string &t)
{
    string nt = t;
    if (t.empty() == true)
        throw invalid_argument("le contact doit avoir un numero de telephone");

    // Verification que le numero ne contien que 10 chiffres et des espaces
    int nbChiffre = 0;
    for (auto it = t.begin(); it != t.end(); it++){
        if (*it >= 47 && *it <= 57)
            nbChiffre++;
        else if (*it == 32)
            continue;
        else
            throw invalid_argument("un numero de telephone ne contient que des chiffres et des espaces");
    }
    if (nbChiffre != 10)
        throw invalid_argument("un numero de telephone contient 10 chiffres");

    // Suppression des espaces dans le numero
    int i = 0;
    while ((i = nt.find(' ')) != -1)
        nt.erase(i, 1);

    //insertion des espaces dans le numero
    int inserted = 0;
    for (i = 2; i < 10; i+=2){
        if (nt.at(i + inserted) != ' '){
            nt.insert(i + inserted, " ");
            inserted++;
        }
    }

    this->telephone=nt;
    this->dernModif=Date();
}
void Contact::setPhoto(const string &ph)
{
    if(ph.empty())
        throw invalid_argument("le contact doit avoir une photo");
    this->photo=ph;
    this->dernModif=Date();
}
void Contact::setMail(const string &m)
{
    if(m.empty())
        throw invalid_argument("le contact doit avoir un mail");
    this->mail=m;
    this->dernModif=Date();
}
void Contact::setDateCrea(Date d){
    this->dateCrea = d;
}

bool Contact::operator==(Contact &c)
{
    return this->nom == c.nom && this->prenom == c.prenom && this->entreprise == c.entreprise && this->mail == c.mail && this->telephone == c.telephone;
}
