#include "date.h"

Date::Date(){}
Date::Date(time_t time){
    this->date = localtime(&time);
}
void Date::setDate(int &j, int &m, int &a){
    this->date->tm_mday = j;
    this->date->tm_mon = m;
    this->date->tm_year = a;
}

int Date::getJour(){
    return this->date->tm_mday;
}

int Date::getMois(){
    return this->date->tm_mon + 1;
}

int Date::getAnnee(){
    return this->date->tm_year + 1900;
}
