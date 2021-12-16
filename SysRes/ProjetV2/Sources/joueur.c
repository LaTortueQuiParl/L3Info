#include "joueur.h"


joueur* NewJoueur(int isHumain, char* pseu, unsigned int i){
    joueur* j = (joueur*) calloc(1,sizeof(joueur));
    j->pseudo = pseu;
    j->nbCartes = 0;
    j->id = i;
    return j;
}

void destroyJoueur(joueur j){
    free(j.cartesEnMain);
    free(j.pseudo);
}

void ajoutCarteMain(joueur* j, unsigned int carte){
    j->cartesEnMain[j->nbCartes] = carte;
    j->nbCartes++;
    int c;

    for(int i=0;i<j->nbCartes-1;i++){
        for(int k=i+1;k<j->nbCartes;k++){
            if ( j->cartesEnMain[i] > j->cartesEnMain[k] ) {
                c = j->cartesEnMain[i];
                j->cartesEnMain[i] = j->cartesEnMain[k];
                j->cartesEnMain[k] = c;
            }
        }
    }
}

void jouer(joueur* j){
    int i;

    for(i=1; i<j->nbCartes;i++){
        j->cartesEnMain[i-1] = j->cartesEnMain[i];
    }

    j->cartesEnMain[i-1] = -1;
    j->nbCartes--;
}