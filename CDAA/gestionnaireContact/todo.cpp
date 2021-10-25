#include "todo.h"



Todo::Todo(const string &newContenu, const string &newContenuTag, const string &newTag, Interaction *own)
{
    this->contenu = newContenu;
    this->contenuTag = newContenuTag;
    this->tag = "@"+newTag;
    this->owner = own;
    this->dateCreation = Date();
}

string Todo::getContenu(){
    return this->contenu;
}
string Todo::getTime(){
    return to_string(this->dateCreation.getJour()) + "/" + to_string(this->dateCreation.getMois()) + "/" + to_string(this->dateCreation.getAnnee());
}
Interaction* Todo::getInteraction(){
    return this->owner;
}
const string &Todo::getTag() const
{
    return tag;
}
const string &Todo::getContenuTag()
{
    return contenuTag;
}

void Todo::setContenu(const string &c){this->contenu = c;}
void Todo::setTag(const string &newTag)
{
    this->tag = newTag;
}
void Todo::setContenuTag(const string &newContenuTag)
{
    contenuTag = newContenuTag;
}

bool Todo::operator==(Todo &t){
    return this->getContenu() == t.getContenu() && this->getContenuTag() == t.getContenuTag() && this->getTime() == t.getTime() && this->getTag() == t.getTag();
}
