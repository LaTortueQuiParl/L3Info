#include "todo.h"

Todo::Todo(){}

string Todo::getContenu(){
    return this->contenu;
}
string Todo::getTime(){
    return to_string(this->dateCreation.getJour()) + "/" + to_string(this->dateCreation.getMois()) + "/" + to_string(this->dateCreation.getAnnee());
}
Interaction* Todo::getInteraction(){
    return this->owner;
}

void Todo::setContenu(const string &c){this->contenu = c;}
void Todo::setInteraction(const Interaction &i){*this->owner = i;}

