#ifndef DATE_H
#define DATE_H

#include <time.h>
#include <string>

/**
 * @brief La classe date
 * Permet de formater les données de la librairier time.h sous forme de int.
 * Comme il n'est pas possible de modifier les valeurs de la structure renvoyée par time.h, la classe ne contient pas de setteur.
 * @class Date
 */
class Date
{
private:
    tm *date;

public:
    /**
     * @brief Les constructeur de Date.
     * La date est toujours la date courante.
     */
    Date();

    /**
     * @brief getJour renvoie le jour de la création de la Date.
     * @return Le jour de la création de la Date.
     */
    int getJour();
    /**
     * @brief getMois renovie le mois de la création de la Date.
     * @return Le mois de la création de la Date.
     */
    int getMois();
    /**
     * @brief getAnnee renvoie l'année de la création de la Date.
     * @return L'année de la création de la Date.
     */
    int getAnnee();
    /**
     * @brief getAnnee renvoie l'heure de la création de la Date.
     * @return L'heure de la création de la Date.
     */
    int getHeures();
    /**
     * @brief getAnnee renvoie la minute de la création de la Date.
     * @return La minute de la création de la Date.
     */
    int getMinutes();
    /**
     * @brief getAnnee renvoie l'année de la création de la Date.
     * @return La seconde de la création de la Date.
     */
    int getSecondes();

};

#endif // DATE_H
