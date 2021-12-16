#include "../Header/gestionjeu.h"
#include <time.h>

gestionnaireJeu* initGestionJeu(){
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
    gj->listeJoueur = (joueur**) calloc(10,sizeof(joueur*));
    
    return gj;
}

void AjoutJoueur(gestionnaireJeu* gj, joueur* j){
    gj->listeJoueur[gj->nbJoueurs] = j;
    gj->nbJoueurs++;
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
    int carteDistrib[gj->nbJoueurs*gj->manche];
    joueur joueursassoc[gj->nbJoueurs*gj->manche];
    for(int jou=0 ; jou<gj->nbJoueurs; jou++){
        gj->listeJoueur[jou]->cartesEnMain = (int*) calloc(gj->manche,sizeof(int));
    }
    int k=0;
    for(int i=0 ; i<gj->manche ; i++){
        for(int j=0 ; j<gj->nbJoueurs ; j++){
            int cartedistribuee = rand() % 100;
            while (gj->deck[cartedistribuee]==-1)
            {
                cartedistribuee = rand() % 100;
            }

            ajoutCarteMain(gj->listeJoueur[j], gj->deck[cartedistribuee]);
            carteDistrib[k] = cartedistribuee;
            joueursassoc[k] = *gj->listeJoueur[j];
            gj->deck[cartedistribuee] = -1;
            k++;
        }
    }

    int c;
    joueur intermediare;

    for(int i=0;i<((gj->nbJoueurs*gj->manche));i++){
        for(int k=i+1;k<(gj->nbJoueurs*gj->manche);k++){
            if ( carteDistrib[i] > carteDistrib[k] ) {
                c = carteDistrib[i];
                carteDistrib[i] = carteDistrib[k];
                carteDistrib[k] = c;
                intermediare = joueursassoc[i];
                joueursassoc[k] = intermediare;
            }
        }
    }
    for(int i=0;i<((gj->nbJoueurs*gj->manche)-1);i++){
        gj->ordreJeu[i] = joueursassoc[i].id;    
    }

}

void jeu(gestionnaireJeu* gj){
    
}