#include "personne.h"
#include <iostream>

const string &Personne::getNom() const
{
    return nom;
}

void Personne::setNom(const string &newNom)
{
    nom = newNom;
}

const string &Personne::getPrenom() const
{
    return prenom;
}

void Personne::setPrenom(const string &newPrenom)
{
    prenom = newPrenom;
}

const string &Personne::getVille() const
{
    return ville;
}

void Personne::setVille(const string &newVille)
{
    ville = newVille;
}

const string &Personne::getDateNaissance() const
{
    return dateNaissance;
}

void Personne::setDateNaissance(const string &newDateNaissance)
{
    dateNaissance = newDateNaissance;
}

Personne::Personne()
{}

string Personne::Affiche(){
    return this->nom + "[" + this->prenom + "]" + this->dateNaissance + "//" + this->ville;
}
