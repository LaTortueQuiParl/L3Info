#include "date.h"

Date::Date()
{
    time_t t = time(nullptr);
    this->date = *localtime(&t);
}
Date::Date(unsigned int j, unsigned int m, unsigned int a){

    std::vector<std::string> mois = {"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};

    if (m > 12)
        throw std::invalid_argument("Il n'est pas possible de creer une date le "
                                    + std::to_string(j) + "/" + std::to_string(m) + "/" + std::to_string(a)
                                    + ", Il n'y a que 12 mois dans l'annee");

    else if (m%2 == 1 && m<7 && j > 31)
        throw std::invalid_argument("Il n'est pas possible de creer une date le "
                                    + std::to_string(j) + "/" + std::to_string(m-1) + "/" + std::to_string(a)
                                    + ", Il n'y a que 31 jours en " + mois.at(m-1));

    else if(m%2 == 0  && m<7 && j > 30)
        throw std::invalid_argument("Il n'est pas possible de creer une date le "
                                    + std::to_string(j) + "/" + std::to_string(m-1) + "/" + std::to_string(a)
                                    + ", Il n'y a que 30 jours en " + mois.at(m-1));

    else if (m%2 == 0 && m>=7 && j > 31)
        throw std::invalid_argument("Il n'est pas possible de creer une date le "
                                    + std::to_string(j) + "/" + std::to_string(m-1) + "/" + std::to_string(a)
                                    + ", Il n'y a que 31 jours en " + mois.at(m-1));

    else if(m%2 == 1  && m>=7 && j > 30)
        throw std::invalid_argument("Il n'est pas possible de creer une date le "
                                    + std::to_string(j) + "/" + std::to_string(m-1) + "/" + std::to_string(a)
                                    + ", Il n'y a que 30 jours en " + mois.at(m-1));

    else if (m==2 && j > 29)
        throw std::invalid_argument("Il n'est pas possible de creer une date le "
                                    + std::to_string(j) + "/" + std::to_string(m) + "/" + std::to_string(a)
                                    + ", Il n'y a que 29 jours au plus en Fevrier");

    else if (m==2 && j == 29 && a%4!=0)
        throw std::invalid_argument("Il n'est pas possible de creer une date le "
                                    + std::to_string(j) + "/" + std::to_string(m) + "/" + std::to_string(a)
                                    + ", Il n'y a que 28 jours en Fevrier hors annee bixestile");

    time_t t = time(nullptr);
    this->date = *localtime(&t);
    this->date.tm_year = a - 1900;
    this->date.tm_mon = m - 1;
    this->date.tm_mday = j;
}

int Date::getJour()
{
    return this->date.tm_mday;
}
int Date::getMois()
{
    return this->date.tm_mon + 1;
}
int Date::getAnnee()
{
    return this->date.tm_year + 1900;
}
int Date::getHeures()
{
    return this->date.tm_hour;
}
int Date::getMinutes()
{
    return this->date.tm_min;
}
int Date::getSecondes()
{
    return this->date.tm_sec;
}

std::string Date::affichage(){
    return std::to_string(this->getJour()) + "/"
            + std::to_string(this->getMois()) + "/"
            + std::to_string(this->getAnnee());
}

bool Date::operator==(Date d){
    return d.getAnnee() == this->getAnnee() && d.getMois() == this->getMois() && d.getJour() == this->getJour();
}

bool Date::operator<(Date d){
    bool tA = this->getAnnee() < d.getAnnee();
    bool tM = this->getMois() < d.getMois();
    bool tJ = this->getJour() < d.getJour();
    if (tA == true)
        return true;
    else if (this->getAnnee() == d.getAnnee() && tM == true)
        return true;
    else if (this->getAnnee() == d.getAnnee() && this->getMois() == d.getMois() && tJ == true)
        return true;
    return false;
}
