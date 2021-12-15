#include "gestionjeu.h"
#include <time.h>

const gestionnaireJeu* initGestionJeu(){
    gestionnaireJeu* gj = (gestionnaireJeu*) calloc(1,sizeof(gestionnaireJeu));
    gj->deck = (int*) calloc(100,sizeof(int));
    for(int i=0; i<100 ; i++){
        gj->deck[i] = i+1;
    }
    gj->cartePosee = (unsigned int*) calloc(100,sizeof(unsigned int));
    gj->ordreJeu = (unsigned int*) calloc(80,sizeof(unsigned int));
    gj->manche = 0;
    gj->nbManche = 0;
    gj->nbJoueurs = 0;
    gj->listeJoueur = (joueur**) calloc(4,sizeof(joueur*));
    
    return gj;
}

void AjoutJoueur(gestionnaireJeu* gj, joueur* j){
    gj->listeJoueur[gj->nbJoueurs] = (joueur*) calloc(4,sizeof(joueur));
    gj->listeJoueur[gj->nbJoueurs] = j;
    gj->nbJoueurs++;
    if(gj->nbJoueurs == 2){
        gj->nbManche = 12;
    }else if(gj->nbJoueurs == 3){
        gj->nbManche = 10;
    }else if(gj->nbJoueurs == 4){
        gj->nbManche = 8;
    }
}

void destroyGestionnaire(gestionnaireJeu* gj){
    for(int i=0 ; i<gj->nbJoueurs ; i++){
        destroyJoueur(gj->listeJoueur[i]);
    }
    free(gj->listeJoueur);
    free(gj->cartePosee);
    free(gj->deck);
    free(gj->ordreJeu);
    free(gj);
}

void distribuer(gestionnaireJeu* gj){
    srand(time(NULL));
    for(int jou=0 ; jou<gj->nbJoueurs; jou++){
        gj->listeJoueur[jou]->cartesEnMain = (int*) calloc(gj->manche,sizeof(int));
    }
    for(int i=0 ; i<gj->manche ; i++){
        for(int j=0 ; j<gj->nbJoueurs ; j++){
            
            int cartedistribuee = rand() % 100;
            while (gj->deck[cartedistribuee]==-1)
            {
                cartedistribuee = rand() % 100;
            }

            ajoutCarteMain(gj->listeJoueur[j], gj->deck[cartedistribuee]);
            gj->deck[cartedistribuee] = -1;
        }
    }
}

void jeu(gestionnaireJeu* gj){
    
}