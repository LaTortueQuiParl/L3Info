#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <list>
#include <iostream>

#include "date.h"
#include "gestioninteractions.h"

using namespace std;

/**
 * @brief Classe contact qui représente un contact avec son nom, prenom, numéro de téléphone, entreprise, mail, photo.
 * Elle garde en mémoire sa date de creation ainsi que sa dernière modification.
 * @class Contact
 */
class Contact
{
private:
    string nom, prenom, entreprise, mail, telephone, photo;
    GestionInteractions gestionInteractions;
    Date dateCrea;
    Date dernModif;
public:

    Contact();
    /**
     * @brief Constructeur de contact.
     * @param n Le nom du contact.
     * @param p Le prénom du contact.
     * @param e L'entreprise du contact.
     * @param t Le téléphone du contact.
     * @param ph La photo du contact.
     * @param mail Le mail du contact.
     */
    Contact(const string &n, const string &p, const string &e, const string &t, const string &ph, const string &mail);
    ~Contact();

    /**
     * @brief getNom renvoie le nom du contact.
     * @return Le nom du contact sous forme de string.
     */
    string const getNom();
    /**
     * @brief getPrenom renvoie le prénom du contact.
     * @return Le nom du contact sous forme de string.
     */
    string const getPrenom();
    /**
     * @brief getEntreprise renvoie le nom de l'entreprise du contact.
     * @return L'entreprise du contact sous forme de string.
     */
    string const getEntreprise();
    /**
     * @brief getTelephone renvoie le numéro de téléphone du contact.
     * @return Le numéro de téléphone du contact sous forme de string.
     */
    string const getTelephone();
    /**
     * @brief getPhoto renvoie le nom du fichier contenant la photo du contact.
     * @return Le nom du fichier contenant la photo du contact sous forme de string.
     */
    string const getPhoto();
    /**
     * @brief getMail renvoie le mail du contact.
     * @return Le mail du contact sous forme de string.
     */
    string const getMail();
    /**
     * @brief getDateCrea renvoie la date de création du contact.
     * @return La date sous format de la classe Date.
     */
    Date getDateCrea();
    /**
     * @brief getDernModif renvoie la date de dernière modification de contact.
     * @return La date de la dernière modification sous format de la classe Date.
     */
    Date getDernModif();

    /**
     * @brief setNom modifie le nom du contact.
     * @param n Le nouveau nom du contact.
     */
    void setNom(const string &n);
    /**
     * @brief setPrenom modifie le prénom du contact.
     * @param p Le nouveau prénom du contact/
     */
    void setPrenom(const string &p);
    /**
     * @brief setEntreprise modifie l'entreprise du contact.
     * @param e La nouvelle entreprise du contact.
     */
    void setEntreprise(const string &e);
    /**
     * @brief setTelephone
     * @param t Le numéro de téléphone du contact.
     */
    void setTelephone(const string &t);
    /**
     * @brief setPhoto modifie le fichier contenant la photo du contact.
     * @param ph Le nouveau nom du fichier contenant la photo du contact.
     */
    void setPhoto(const string &ph);
    /**
     * @brief setMail modifie l'adresse mail du contact.
     * @param m La nouvelle adresse mail du contact.
     */
    void setMail(const string &m);

    /**
    * @brief surchage de l'operateur << qui permet d'afficher simplement les informations du contact.
    * @param os Le stream dans lequel on veut envoiyer les informations du contact.
    * @param c L'instance du contact dont on veut afficher les informations.
    */
    friend ostream &operator<<(ostream &os, Contact &c)
    {
        return os << c.getNom() << " " << c.getPrenom() << " [" << c.getEntreprise() << "] (" << c.getMail() << ") \"" << c.getTelephone() << "\" " << c.getPhoto() << " cree le: " << c.getDateCrea() << " modifie le:" << c.getDernModif();
    }
    bool operator==(Contact &);
};

#endif // CONTACT_H
