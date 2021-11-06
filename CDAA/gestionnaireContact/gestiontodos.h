#ifndef GESTIONTODOS_H
#define GESTIONTODOS_H

#include "todo.h"
#include <list>

using namespace std;

/**
 * @brief La classe gestionTodos.
 * Les classe gestionTodos permet de regrouper les todos sous forme de liste.
 * Elle a pour seul attribut une liste de pointeur sur Todo pour que les modifications des todos modifient aussi ceux dans la liste
 * @class GestionTodos
 */
class GestionTodos
{
private:
    list<Todo*> listTodo;
public:
    /**
     * @brief Le constructeur de GestionTodos.
     */
    GestionTodos();

    /**
     * @brief getTodos renvoie la liste des todos.
     * @return La liste des todos
     */
    list<Todo*> const getTodos();

    /**
     * @brief setTodos remplace la liste des todos par une nouvelle.
     * @param l est la nouvelle liste des todos.
     */
    void setTodos(const list<Todo*> &l);

    /**
     * @brief addTodo permet d'ajouter un nouveau todo dans la liste.
     * @param t est le todo à rajouter dans la liste. Il n'est pas constant pour que les todos dans la liste soit modifié lorsqu'ils le sont à l'extérieur de la liste
     * La fonction lance une exception 'std::invalid_argument' lorsque l'interaction à ajouter est déjà dans la liste.
     * La fonction doit donc toujours être dans un try et catch pour pouvoir gérer l'exception sinon quoi le programme se termine
     */
    void addTodo(Todo &t);
    /**
     * @brief supprTodo permet de supprimer un todo dans la liste.
     * @param t est le todo à supprimer de la liste.
     */
    void supprTodo(Todo &t);

    /**
     * @brief operator << permet d'afficher tous les todos de la liste.
     * @param os est le flux dans lequel on veut envoyer la liste.
     * @param gt est le gestionTodos que l'on veut afficher.
     * @return Le flux avec dedans tous les éléments de la liste.
     */
    friend ostream &operator<<(ostream &os, GestionTodos &gt)
    {
        for(auto v:gt.getTodos()){
            os << v << endl;
        }
        return os;
    }
};

#endif // GESTIONTODOS_H
