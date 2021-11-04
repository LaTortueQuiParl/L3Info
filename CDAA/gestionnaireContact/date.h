#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>
#include <time.h>
#include <vector>

/**
 * @brief La classe date
 * Permet de formater les données de la librairier time.h sous forme de int.
 * La date ne supporte que le format jj/mm/aaaa
 * @class Date
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

    /**
     * @brief affichage permet d'avoir le même format pour afficher les dates
     * @return La date de l'instance sous forme de string jj/mm/aaaa
     */
    std::string affichage();

    /**
     * @brief operator << permet l'affichage facile de la date.
     * @param os est le flux dans lequel on veut envoyer la date.
     * @param d est la date à afficher.
     * @return Le flus contenant la date.
     */
    friend std::ostream &operator<<(std::ostream &os, Date d){
        return os << std::to_string(d.getJour()) + "/" + std::to_string(d.getMois()) + "/" + std::to_string(d.getAnnee());
    }

    /**
     * @brief operator == permet de savoir si les attrbuts de 2 dates sont les mêmes.
     * @param d est la date avec laquelle on compare cette instance.
     * @return Un booléen qui est vrai si les deux dates ont les mêmes attributs.
     */
    bool operator==(Date d);

    /**
     * @brief operator < permet de comparer 2 dates dans l'ordre chronologique.
     * @param d est la date avec laquelle on compare cette instance.
     * @return Un booléen qui est vrai si la date de cette instance précède la date avec laquelle on la compare.
     */
    bool operator<(Date d);
};

#endif // DATE_H
