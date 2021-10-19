#ifndef DATE_H
#define DATE_H

#include <time.h>
#include <string>

class Date
{

public:
    tm *date;
    Date();
    Date(time_t time);
    int getJour();
    int getMois();
    int getAnnee();
    int getHeures();
    int getMinutes();
    int getSecondes();

    void setDate(int &j, int &m, int &a);
};

#endif // DATE_H
