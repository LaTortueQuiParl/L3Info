#include "Header/gestionjeu.h"

int main(void){

    gestionnaireJeu* gj = initGestionJeu();

    gj->manche = 3;

    int id = 1;
    char pseu[256] = "pseudo";

    joueur* j1 = NewJoueur(1,pseu, id);
    joueur* j2 = NewJoueur(1,pseu, id);
    joueur* j3 = NewJoueur(1,pseu, id);

    AjoutJoueur(gj,j1);
    AjoutJoueur(gj,j2);
    AjoutJoueur(gj,j3);

    distribuer(gj);

    for(int i=0; i<gj->nbJoueurs; i++){
        printf("%s\n", gj->listeJoueur[i]->pseudo);
        for(int j=0; j<gj->manche; j++){
            printf("%d | ", gj->listeJoueur[i]->cartesEnMain[j]);
        }
    }

    return 0;
}