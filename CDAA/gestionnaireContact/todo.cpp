#include "todo.h"

Todo::Todo()
{

}


void Todo::setContenu(const string &c){this->contenu = c;}
void Todo::setDate(const tm &t){*this->date = t;}
void Todo::setInteraction(const Interaction &i){*this->owner = i;}

string const Todo::getContenu(){return this->contenu;}
tm* Todo::getTime(){return this->date;}
Interaction* Todo::getInteraction(){return this->owner;}
