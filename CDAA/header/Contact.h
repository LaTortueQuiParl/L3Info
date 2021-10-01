#include <stdio.h>
#include <time.h>
using namespace std::;

class Contact
{
private:
    string nom, prenom, entreprise, mail, telephone, photo;
    time_t *dateCrea;
public:
    Contact(const string &, const string &, const string &, const string &, const string &, const string &, const time_t &);
    ~Contact();
};

Contact::Contact(const string nom, const string prenom, const string entreprise, const string mail, const string telephone, const string photo, const time_t *date)
{
    this->nom = nom;
    this->prenom = prenom;
    this->entreprise = entreprise;
    this->mail = mail;
    this->telephone = telephone;
    this->photo = photo;
    this->dateCrea = date;

}

Contact::~Contact()
{
}
