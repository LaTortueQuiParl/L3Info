#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>
#include <iostream>
#include "gestiontodos.h"

class Contact;

using namespace std;

/**
 * @brief La classe interaction
 * Elle représente l'intéraction, décrite dans contenu, garde en mémoire sa date de création et est associée avec le contact qui est à l'origine de l'interaction
 * Elle permet de décrire et de manipuler une interaction
 * @class Interaction
 */
class Interaction
{
private:
    string contenu;
    Date dateCreation;
    Contact* contact;
    GestionTodos gt;

    /**
     * @brief setContact change le contact.
     * setContact défini le contact qui est à l'origine de l'interaction, n'est utilisée que dans le constructeur et est donc en privé.
     * Cela n'a pas de sens de le mettre en public car une fois qu'une intéraction à eu lieu, la personne qui en est à l'origine ne change pas
     * @param newContact Le contact qui a fait l'intéraction.
     */
    void setContact(Contact *newContact);

public:
    /**
     * @brief Constructeur d'interaction.
     * @param contenu La nature de l'intéraction (rendez-vous, appel...).
     * @param contact Le contact qui a intéragi.
     */
    Interaction(const string &contenu, Contact &contact);
    ~Interaction();

    /**
     * @brief getContenu récupère le contenu de l'interaction.
     * @return Le Contanu sous forme de string.
     */
    string getContenu();
    /**
     * @brief getDateCreation récupère la date de création de l'interaction.
     * @return La date de création de l'interaction sous format "dd/mm/aaaa".
     */
    Date getDateCreation();
    /**
     * @brief getContact récupère le contact qui est la source de l'interaction.
     * @return Renvoie le contact qui a intéragi.
     */
    Contact* getContact();

    /**
     * @brief setContenu redéfini le contenu de l'intéraction.
     * @param c Le nouveau contenu de l'interaction.
     */
    void setContenu(const string &c);

    /**
     * @brief setDateCreation permet de mettre une date de création autre que la date courante pour une interaction, ne sert que pour les tests et n'a pas d'application réelle
     * @param d la date à laquelle on veut créer une interaction
     */
    void setDateCreation(const Date d);

    /**
     * @brief operator << permet de faire la surcharge de l'opérateur << afin de faciliter le débugage.
     * @param os Le stream dans lequel on envoie les informations d'interaction.
     * @param i L'instance d'interaction dont on veut envoyer les informations dans un stream.
     * @return
     */
    friend ostream &operator<<(ostream &os, Interaction &i)
    {
        return os << i.getContenu() << ", " << i.getDateCreation();
    }

    /**
     * @brief operator == permet de comparer 2 interaction
     * @param i le deuxième membre à comprarer
     * @return renvoie vrai si le contact, contenu et date de création sont les mêmes
     */
    bool operator==(Interaction &i);

    /**
     * @brief operator < permet de savoir si une interaction a été créée avant une autre
     * @param i le deuxième membre à comparer
     * @return renvoie vrai si le membre de gauche est plus petit que le membre de droite
     */
    bool operator<(Interaction &i);
};

#endif // INTERACTION_H
