#include "contact.h"

Contact::Contact(const string &n, const string &p, const string &e, const string &t, const string &ph, const string &mail)
{
    this->setNom(n);
    this->setPrenom(p);
    this->setEntreprise(e);
    this->setTelephone(t);
    this->setPhoto(ph);
    this->setMail(mail);
    time_t tmm = time(nullptr);
    this->dateCrea = Date(tmm);
    this->dernModif = Date(tmm);
    //this->lesInteractions = LesInteractions();
}

Contact::~Contact(){
    //lesInteractions.~LesInteractions();
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
std::string Contact::getDateCrea()
{
    return to_string(this->dateCrea.getJour()) + "/" + to_string(this->dateCrea.getMois()) + "/" + to_string(this->dateCrea.getAnnee());
}
std::string Contact::getDernModif()
{
    return to_string(this->dernModif.getJour()) + "/" + to_string(this->dernModif.getMois()) + "/" + to_string(this->dernModif.getAnnee());
}

//LesInteractions const Contact::getInteraction()
//{
//    return this->lesInteractions;
//}

void Contact::setNom(const string &n)
{
    if(!n.empty())
        this->nom=n;
    this->dernModif=Date(time(nullptr));
}
void Contact::setPrenom(const string &p)
{
    if(!p.empty())
        this->prenom=p;
    this->dernModif=Date(time(nullptr));
}
void Contact::setEntreprise(const string &e)
{
    if(!e.empty())
        this->entreprise=e;
    this->dernModif=Date(time(nullptr));
}
void Contact::setMail(const string &m)
{
    if(!m.empty())
        this->mail=m;
    this->dernModif=Date(time(nullptr));
}
void Contact::setTelephone(const string &t)
{
    if(!t.empty())
        this->telephone=t;
    this->dernModif=Date(time(nullptr));
}
void Contact::setPhoto(const string &ph)
{
    if(!ph.empty())
        this->photo=ph;
    this->dernModif=Date(time(nullptr));
}
void Contact::setDateCrea(int j, int m, int a){
    this->dateCrea = Date(j, m, a);
}

bool Contact::operator==(Contact &c)
{
    return this->nom == c.nom && this->prenom == c.prenom && this->entreprise == c.entreprise && this->mail == c.mail && this->telephone == c.telephone;
}
//void Contact::setInteration(const Interaction &i){this->lesInteractions=i;};