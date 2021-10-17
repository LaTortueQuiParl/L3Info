#ifndef LESTODOS_H
#define LESTODOS_H

#include "todo.h"
#include <list>

using namespace std;

class LesTodos
{
private:
    list<Todo> lTodo;
public:
    LesTodos();
    list<Todo> const getTodos();
    void setTodos(const list<Todo> &);
    void addTodo(const Todo &);
};

#endif // LESTODOS_H
