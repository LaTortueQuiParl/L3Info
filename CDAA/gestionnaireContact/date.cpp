#include "date.h"

Date::Date()
{
    time_t t = time(nullptr);
    this->date = localtime(&t);
}
int Date::getJour()
{
    return this->date->tm_mday;
}
int Date::getMois()
{
    return this->date->tm_mon + 1;
}
int Date::getAnnee()
{
    return this->date->tm_year + 1900;
}
int Date::getHeures()
{
    return this->date->tm_hour;
}
int Date::getMinutes()
{
    return this->date->tm_min;
}
int Date::getSecondes()
{
    return this->date->tm_sec;
}
