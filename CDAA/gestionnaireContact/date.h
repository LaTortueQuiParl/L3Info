#ifndef DATE_H
#define DATE_H

#include <time.h>
#include <string>

/**
 * @brief The Date class
 * @class The date from time.h library but gives back int type
 */
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

};

#endif // DATE_H
