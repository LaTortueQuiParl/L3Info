#include "gestiontodos.h"

GestionTodos::GestionTodos()
{
    this->listTodo = {};

}

list<Todo*> const GestionTodos::getTodos(){
    return this->listTodo;
}

void GestionTodos::setTodos(const list<Todo*> &l){
    this->listTodo = l;
    this->listTodo.sort([] (Todo* t1, Todo* t2){
        return t1->getDeadline() < t2->getDeadline();
    });
}

void GestionTodos::addTodo(Todo &t){
    for(std::list<Todo*>::iterator v = this->listTodo.begin() ; v != this->listTodo.end(); ++v){
        if (**v == t){
            throw invalid_argument("Ce todo { "
                                   + t.affichage()
                                   + " } est deja dans la liste");
        }
    }
    this->listTodo.push_back(&t);
    this->listTodo.sort([] (Todo* t1, Todo* t2){
        return t1->getDeadline() < t2->getDeadline();
    });
}

void GestionTodos::supprTodo(Todo &t){
    bool b = false;
    for(auto v=this->listTodo.begin() ; v!=this->listTodo.end(); ++v){
        if(**v==t && *v == &t){ // On verifie avec le premier test que les attributs sont les memes mais avec le second que l'adresse est aussi la meme
            v = this->listTodo.erase(v);
            b = true;
        }
    }
    if (b == false)
        throw invalid_argument("rien n'a ete supprime");
}
