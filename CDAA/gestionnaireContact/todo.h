#ifndef TODO_H
#define TODO_H

#include <string>
#include "interaction.h"

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
    string tag;
    Date dateCreation;
    Interaction* owner;
public:
    /**
     * @brief Le constructeur de Todo.
     */
    Todo();

    /**
     * @brief getContenu renvoie le contenu du Todo.
     * @return Le contenu du todo.
     */
    string getContenu();
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
     * @brief setContenu modifie le contenu du todo.
     * @param c est le nouveau contenu du Todo.
     */
    void setContenu(const string &c);
    /**
     * @brief setInteraction modifie l'interaction justifiant le Todo.
     * @param i est l'instance de l'interaction à l'origine du Todo.
     */
    void setInteraction(const Interaction &i);
};

#endif // TODO_H
