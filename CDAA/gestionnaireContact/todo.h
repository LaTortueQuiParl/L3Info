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
 * @class Todo
 */
class Todo
{
private:
    string contenu;
    string contenuTag;
    string tag;
    Date dateCreation;
    Interaction* owner;
public:
    /**
     * @brief constructeur de Todo
     * @param newContenu nouveau contenu
     * @param newTag nouveau tag
     * @param own est l'instance de l'interaction à l'origine du Todo.
     */
    Todo(const string &contenu, const string &newContenu, const string &newTag, Interaction *own);

    /**
     * @brief getContenu renvoie le contenu du Todo.
     * @return Le contenu du todo.
     */
    string getContenu();
    /**
     * @brief getContenuTag renvoie un contenu additionnel au tag du Todo.
     * @return Le contenuTag du todo.
     */
    const string &getContenuTag();
    /**
     * @brief getTime renvoie la date de création du Todo.
     * @return La date de création du Todo
     */
    string getTime();
    /**
     * @brief getInteraction renvoie l'interaction dont elle est à l'origine
     * @return Un pointeur sur l'interaction qui justifie le Todo.
     */
    Interaction* getInteraction();
    /**
     * @brief getTag renvoie le tag du todo
     * @return un string contenant le tag passé en parametre
     */
    const string &getTag() const;

    /**
     * @brief setContenu modifie le contenu du todo.
     * @param c est le nouveau contenu du Todo.
     */
    void setContenu(const string &c);
    /**
     * @brief setContenuTag modifie le contenuTag du todo.
     * @param newContenuTag est le nouveau contenuTag du Todo.
     */
    void setContenuTag(const string &newContenuTag);
    /**
     * @brief setTag modifie le contenu de tag. Si le tag est différent de "todo" ou de "date" alors il affiche une erreur.
     * @param newTag un nouveau tag sous forme de string.
     */
    void setTag(const string &newTag);

    /**
    * @brief surchage de l'operateur << qui permet d'afficher simplement les informations du todo.
    * @param os Le stream dans lequel on veut envoyer les informations du Todo.
    * @param t L'instance du todo dont on veut afficher les informations.
    */
    friend ostream &operator<<(ostream &os, Todo &t)
    {
        if(!t.getTag().empty())
            return os << "@todo " << t.getContenu();
        return os << "@todo " << t.getContenu() << " " << t.getTag() << " " << t.getContenuTag();
    }
    /**
    * @brief surchage de l'operateur == qui permet de vérifier qu'un todo est égal à un autre todo.
    * @param t L'instance du todo dont on veut vérifier l'égalitée.
    */
    bool operator==(Todo &t);
};

#endif // TODO_H
