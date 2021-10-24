#ifndef GESTIONTODOS_H
#define GESTIONTODOS_H

#include "todo.h"
#include <list>

using namespace std;

/**
 * @brief La classe gestionTodos.
 * Les classe gestionTodos permet de regrouper les todos sous forme de liste.
 * @class GestionTodos
 */
class GestionTodos
{
private:
    list<Todo> lTodo;
public:
    /**
     * @brief Le constructeur de GestionTodos.
     */
    GestionTodos();

    /**
     * @brief getTodos renvoie la liste des todos.
     * @return La liste des todos
     */
    list<Todo> const getTodos();
    /**
     * @brief setTodos remplace la liste des todos par une nouvelle.
     * @param lt est la nouvelle liste des todos.
     */
    void setTodos(const list<Todo> &lt);
    /**
     * @brief addTodo permet d'ajouter un nouveau todo dans la liste.
     * @param t est le todo à rajouter dans la liste.
     */
    void addTodo(const Todo &t);
};

#endif // GESTIONTODOS_H
