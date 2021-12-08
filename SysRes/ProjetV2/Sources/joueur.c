#include "joueur.h"


joueur* NewJoueur(int isHumain){
    joueur* j = (joueur*) calloc(1,sizeof(joueur));
    j->pseudo = (unsigned char*) calloc(8,sizeof(unsigned char));
    if(isHumain == 0){
        sprintf(j->pseudo,"bot n%d",botId);
        j->id = botId;
        botId++;
    }else{
        printf("Veuillez entrer votre pseudo : ");
        scanf("%s", j->pseudo);
        j->id = joueurId;
    }
    j->nbCartes = 0;

    return j;
}

void destroyJoueur(joueur* j){
    free(j->cartesEnMain);
    free(j->pseudo);
    free(j);
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