#include "lestodos.h"

LesTodos::LesTodos()
{

}

list<Todo> const LesTodos::getTodos(){return this->lTodo;}

void LesTodos::setTodos(const list<Todo> &l){this->lTodo = l;}

void LesTodos::addTodo(const Todo &t){this->lTodo.push_back(t);}
