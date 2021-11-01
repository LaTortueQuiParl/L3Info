#include "gestioninteractions.h"

GestionInteractions::GestionInteractions()
{
    this->dernModif = Date();
    this->listInteractions = {};
}

list<Interaction> const GestionInteractions::getInteractions(){
    return this->listInteractions;
};

Date GestionInteractions::getDernModif()
{
    return this->dernModif;
}

void GestionInteractions::setInteractions(const list<Interaction> &l){
    if(!l.empty())
        this->listInteractions = l;
}

void GestionInteractions::setDernModif()
{
    this->dernModif = Date();
}

void GestionInteractions::addInteraction(const Interaction &i){
    Interaction i2 = i;
    for(auto v=this->listInteractions.begin() ; v!=this->listInteractions.end();v++){
        if (*v == i2){
            throw std::invalid_argument("Cette interaction { "
                                        + i2.getContenu()
                                        + " } est deja dans la liste");
            return;
        }
    }
    this->listInteractions.push_back(i);
}

void GestionInteractions::supprInteraction(const Interaction &i){
    for(auto v=this->listInteractions.begin() ; v!=this->listInteractions.end();){
        Interaction k = static_cast<Interaction>(i);
        if(*v==k){
            v = this->listInteractions.erase(v);
        }
        else
            ++v;
    }
    this->dernModif=Date();
}
