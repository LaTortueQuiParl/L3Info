#include "todo.h"

Todo::Todo(const string &newContenu, Interaction *own){
    setContenu(newContenu);
    setDeadline(Date());
    setTag(false);
    this->owner = own;
}
Todo::Todo(const string &newContenu, Interaction *own, const Date date)
{
    setContenu(newContenu);
    setDeadline(date);
    this->owner = own;
}

string Todo::getContenu(){
    return this->contenu;
}
Date Todo::getDeadline(){
    return this->deadline;
}
Interaction* Todo::getInteraction(){
    return this->owner;
}
const bool &Todo::getTag() const
{
    return tag;
}

void Todo::setContenu(const string &c){this->contenu = c;}
void Todo::setTag(const bool newTag)
{
    this->tag = newTag;
}
void Todo::setDeadline(const Date &date){
    setTag(true);
    this->deadline = date;
}

string Todo::affichage(){
    if (this->getTag() == false)
        return "@todo " + this->getContenu();
    return "@todo" + this->getContenu() + " @date " + this->getDeadline().affichage();
}

bool Todo::operator==(Todo &t){
    return this->getContenu() == t.getContenu() && this->getDeadline() == t.getDeadline() && this->getTag() == t.getTag();
}
