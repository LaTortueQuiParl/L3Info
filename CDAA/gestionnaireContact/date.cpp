#include "date.h"

Date::Date()
{
    time_t t = time(nullptr);
    this->date = *localtime(&t);
}
Date::Date(unsigned int j, unsigned int m, unsigned int a){
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
