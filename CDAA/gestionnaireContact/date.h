#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>
#include <time.h>
#include <vector>

/**
 * @brief La classe date
 * Permet de formater les données de la librairier time.h sous forme de int.
 * Comme il n'est pas possible de modifier les valeurs de la structure renvoyée par time.h, la classe ne contient pas de setteur.
 * @class Date
 * @todo faire des exceptions lorsque le format de la date n'est pas respecté
 */
class Date
{
private:
    tm date;

public:
    /**
     * @brief Les constructeur de Date.
     * La date est toujours la date courante.
     */
    Date();
    /**
     * @brief Date est le constructeur de Date qui permet d'avoir une date autre que la date courante
     * @param j le jour de la date
     * @param m le mois de la date
     * @param a l'année de la date
     * @todo vérifier que le jour est inférieur à 31.., utiliser des exceptions.
     */
    Date(unsigned int j, unsigned int m, unsigned int a);

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

    friend std::ostream &operator<<(std::ostream &os, Date d){
        return os << std::to_string(d.getJour()) + "/" + std::to_string(d.getMois()) + "/" + std::to_string(d.getAnnee());
    }

    bool operator==(Date d);

    bool operator<(Date d);
};

#endif // DATE_H
