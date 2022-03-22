#include "../Headers/GestionJeu.h"

GestionJeu* initGestionJeu(){
    GestionJeu* gestJeu = (GestionJeu*)malloc(sizeof(GestionJeu));
    gestJeu->paquet = (int*)calloc(100, sizeof(int));
    for(int i=0;i<100;i++){
        gestJeu->paquet[i] = i+1;
    }
    gestJeu->mancheActuel = 0;
    gestJeu->nbJoueurs = 0;
    gestJeu->joueurs = (Joueur*)calloc(4,sizeof(Joueur));
    gestJeu->cartesPosees = (int*)calloc(100, sizeof(int));

    return gestJeu;
}

void AjoutJoueur(GestionJeu* gestJeu, Joueur* j){
    if(gestJeu->nbJoueurs<4){
        gestJeu->joueurs[gestJeu->nbJoueurs] = j;
        gestJeu->nbJoueurs++;
    }else{
        printf("Max joueurs atteinds\n%d Joueurs", gestJeu->nbJoueurs);
    }
}
void Distribution(GestionJeu* gestJeu){
    for(int i=0;i<gestJeu->nbJoueurs;i++){
        for(int j=0; j<gestJeu->mancheActuel; j++){
            
        }
    }
}