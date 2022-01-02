#include "../Headers/Joueur.h"

void PoserCarte(Joueur* j){
    int carteJouer = j->cartesEnMain[0];
    for(int i=0; i<j->nbCartes-1; i++){
        j->cartesEnMain[i] = j->cartesEnMain[i+1];
    }
    j->cartesEnMain[j->nbCartes] = -1;
    printf("Le joueur %s a joué la carte : %d", j->pseudo, carteJouer);
}