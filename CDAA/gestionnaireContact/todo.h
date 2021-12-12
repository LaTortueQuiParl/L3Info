#ifndef TODO_H
#define TODO_H

#include <string>
#include "date.h"
#include <iostream>

class Interaction;

using namespace std;

/**
 * @brief La classe Todo qui défini une action à faire
 * Elle est la conséquence d'une action et a donc un pointeur sur l'action qui la justifie.
 * Elle permet de décrire et de manipuler un todo
 * @class Todo
 */
class Todo
{
private:
    string contenu;
    Date deadline;
    bool tag;
    Interaction* owner;

    /**
     * @brief setTag permet de mettre bool à true et dire que la deadline est autre que la date d'instanciation.
     * @param newTag le bool pour savoir si la date butoir est différente que la date d'instanciation
     */
    void setTag(const bool newTag);
public:

    /**
     * @brief Todo est le constructeur d'un todo avec la date d'instanciation pour la date butoir.
     * @param contenu l'action qu'il y a faire
     * @param own est l'instance de l'interaction à l'origine du Todo.
     */
    Todo(const string &contenu, Interaction *own);
    /**
     * @brief Constructeur de Todo avec une date butoir autre que la date d'instanciation
     * @param contenu l'action qu'il y a faire
     * @param own est l'instance de l'interaction à l'origine du Todo.
     * @param date est la date butoir
     */
    Todo(const string &contenu, Interaction *own, const Date date);

    /**
     * @brief getContenu renvoie le contenu du Todo.
     * @return Le contenu du todo.
     */
    string getContenu();
    /**
     * @brief getDeadline renvoie la date butoir.
     * @return La date butoir.
     */
    Date getDeadline();
    /**
     * @brief getInteraction renvoie l'interaction dont elle est à l'origine
     * @return Un pointeur sur l'interaction qui justifie le Todo.
     */
    Interaction* getInteraction();
    /**
     * @brief getTag permet de savoir si il y a une date butoir autre que la date d'instanciation.
     * @return le bool qui est true si il y a une date butoir autre que la date d'instanciation.
     */
    const bool &getTag() const;

    /**
     * @brief setContenu modifie le contenu du todo.
     * @param c est le nouveau contenu du Todo.
     */
    void setContenu(const string &c);
    /**
     * @brief setDeadline permet de changer la date butoir.
     * @param date la nouvelle date butoir.
     */
    void setDeadline(const Date &date);

    /**
     * @brief affichage permet l'affichage d'un todo.
     * @return un string contenant les attributs du todo.
     */
    string affichage();

    /**
    * @brief surchage de l'operateur << qui permet d'afficher simplement les informations du todo.
    * @param os Le stream dans lequel on veut envoyer les informations du Todo.
    * @param t L'instance du todo dont on veut afficher les informations.
    */
    friend ostream &operator<<(ostream &os, Todo &t)
    {
        if(t.getTag() == false)
            return os << "@todo " << t.getContenu();
        return os << "@todo " << t.getContenu() << " @date "  << t.getDeadline();
    }

    /**
    * @brief surchage de l'operateur == qui permet de vérifier qu'un todo est égal à un autre todo.
    * @param t L'instance du todo dont on veut vérifier l'égalitée.
    */
    bool operator==(Todo &t);
};

#endif // TODO_H
