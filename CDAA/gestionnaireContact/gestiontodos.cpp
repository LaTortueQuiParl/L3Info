#include "gestiontodos.h"

GestionTodos::GestionTodos()
{
    this->listTodo = {};

}

list<Todo> const GestionTodos::getTodos(){
    return this->listTodo;
}

void GestionTodos::setTodos(const list<Todo> &l){
    this->listTodo = l;
}

void GestionTodos::addTodo(const Todo &t){
    Todo t2 = t;
    for(auto v=this->listTodo.begin() ; v!=this->listTodo.end(); ++v){
        if (*v == t2){
            throw invalid_argument("Ce todo est deja dans la liste");
        }
    }
    this->listTodo.push_back(t);
}

void GestionTodos::supprTodo(Todo &t){
    for(auto v=this->listTodo.begin() ; v!=this->listTodo.end(); ++v){
        if(*v==t)
            v = this->listTodo.erase(v);
    }
}
