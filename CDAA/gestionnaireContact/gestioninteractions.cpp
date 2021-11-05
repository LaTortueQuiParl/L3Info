#include "gestioninteractions.h"

GestionInteractions::GestionInteractions()
{
    this->dernModif = Date();
    this->listInteractions = {};
}

list<Interaction*> const GestionInteractions::getInteractions(){
    return this->listInteractions;
};

Date GestionInteractions::getDernModif()
{
    return this->dernModif;
}

void GestionInteractions::setInteractions(const list<Interaction*> &l){
    this->listInteractions = l;
    this->listInteractions.sort([] (Interaction* i1, Interaction* i2){
        return i1->getDateCreation() < i2->getDateCreation();
    });
}

void GestionInteractions::setDernModif()
{
    this->dernModif = Date();
}

void GestionInteractions::addInteraction(Interaction &i){
    for(auto v=this->listInteractions.begin() ; v!=this->listInteractions.end();v++){
        if (**v == i){
            throw std::invalid_argument("cette interaction { "
                                        + i.getContenu()
                                        + " } est deja dans la liste");
            return;
        }
    }
    this->listInteractions.push_back(&i);
    this->listInteractions.sort([] (Interaction *i1, Interaction *i2){
        return i1->getDateCreation() < i2->getDateCreation();
    });
}

void GestionInteractions::supprInteraction(Interaction &i){
    bool b = false;
    for(auto v=this->listInteractions.begin() ; v!=this->listInteractions.end(); ++v){
        if(**v==i && *v==&i){
            v = this->listInteractions.erase(v);
            b = true;
        }
    }
    if (b == false)
        throw invalid_argument("rien n'a ete supprime");
    this->dernModif=Date();
}
