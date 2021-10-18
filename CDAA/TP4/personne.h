#ifndef PERSONNE_H
#define PERSONNE_H

#include <string>
using namespace std;

class Personne
{
private:
    string nom,prenom,ville,dateNaissance;

public:
    Personne();
    const string &getNom() const;
    void setNom(const string &newNom);
    const string &getPrenom() const;
    void setPrenom(const string &newPrenom);
    const string &getVille() const;
    void setVille(const string &newVille);
    const string &getDateNaissance() const;
    void setDateNaissance(const string &newDateNaissance);

    string Affiche();
};

#endif // PERSONNE_H
