#ifndef DATE_H
#define DATE_H

#include <time.h>
#include <string>

class Date
{
    tm *date;
public:
    Date();
    Date(time_t time);
    int getJour();
    int getMois();
    int getAnnee();

    void setDate(int &j, int &m, int &a);
};

#endif // DATE_H
