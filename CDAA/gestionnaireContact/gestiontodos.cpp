#include "gestiontodos.h"

GestionTodos::GestionTodos()
{

}

list<Todo> const GestionTodos::getTodos(){return this->lTodo;}

void GestionTodos::setTodos(const list<Todo> &l){this->lTodo = l;}

void GestionTodos::addTodo(const Todo &t){this->lTodo.push_back(t);}

void GestionTodos::supprTodo(Todo &t){
    for(auto v=this->lTodo.begin() ; v!=this->lTodo.end(); ++v){
        if(*v==t)
            v = this->lTodo.erase(v);
    }
}
