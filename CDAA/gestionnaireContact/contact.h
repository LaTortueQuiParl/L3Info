#ifndef CONTACT_H
#define CONTACT_H
#include <string>
#include <list>
#include <iostream>
#include <ctime>
#include "date.h"
#include "lesinteractions.h"

using namespace std;

/**
 * @brief The Contact class
 * @class class contact qui représente un contact
 */
class Contact
{
private:
    string nom, prenom, entreprise, mail, telephone, photo;
    LesInteractions lesInteractions ;
    Date dateCrea;
    Date dernModif;
public:
    /**
     * @brief Constructeur de contact
     * @param n Le nom du contact
     * @param p Le prénom du contact
     * @param e L'entreprise du contact
     * @param t Le téléphone du contact
     * @param ph La photo du contact
     * @param mail Le mail du contact
     */
    Contact(const string &n, const string &p, const string &e, const string &t, const string &ph, const string &mail);
    ~Contact();

    string const getNom();
    string const getPrenom();
    string const getEntreprise();
    string const getTelephone();
    string const getPhoto();
    string const getMail();
    LesInteractions const getInteraction();

    /**
     * @brief getDateCrea
     * @return La date sous format de la classe Date
     */
    std::string getDateCrea();// On renvoie un string car cette méthide ne sert qu'à afficher la date :)
    /**
     * @brief getDernModif
     * @return La date de la dernière modification sous format de la classe Date
     */
    std::string getDernModif();// Pareil (:

    void setNom(const string &);
    void setPrenom(const string &);
    void setEntreprise(const string &);
    void setMail(const string &);
    void setTelephone(const string &);
    void setPhoto(const string &);
    void setInteration(const Interaction &);

    friend ostream &operator<<(ostream &os, Contact &c)
    {
        return os << c.getNom() << " " << c.getPrenom() << " [" << c.getEntreprise() << "] (" << c.getMail() << ") \"" << (string) c.getTelephone() << "\" " << c.getPhoto() << "\tcree le: " << c.getDateCrea() << "\tderniere modification le: " << c.getDernModif();
    }
    bool operator==(Contact &);
};

#endif // CONTACT_H
