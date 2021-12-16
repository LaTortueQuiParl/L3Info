#include "Header/gestionjeu.h"

#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct GestionDuJeu{
    int perdu;
    gestionnaireJeu* gj;
    joueur* joueurcourant;
}GestionDuJeu;

void *thread_Joueur(void* arg){
    srand(time(NULL));

    GestionDuJeu* gestDuJeu = (GestionDuJeu*) arg;

    while (gestDuJeu->joueurcourant->nbCartes>0)
    {
        if(gestDuJeu->joueurcourant->humain == 0){
            int rnd = rand()%4+1;
            sleep(rnd);

            printf("%s JOUE %d !\n", gestDuJeu->joueurcourant->pseudo, gestDuJeu->joueurcourant->cartesEnMain[0]);
            gestDuJeu->perdu = jeu(gestDuJeu->joueurcourant, gestDuJeu->gj);
            if(gestDuJeu->perdu == 0){
                printf("%s Sort du jeu.\n",gestDuJeu->joueurcourant->pseudo);    
                pthread_exit(EXIT_SUCCESS);        
            }
        }else{
            char joue[256];
            printf("Tapez j pour jouer\n");
            scanf("%s", joue);
            if(!strncmp(joue, "j", 1)){
                printf("%s JOUE %d !\n", gestDuJeu->joueurcourant->pseudo, gestDuJeu->joueurcourant->cartesEnMain[0]);
                gestDuJeu->perdu = jeu(gestDuJeu->joueurcourant, gestDuJeu->gj);
                if(gestDuJeu->perdu == 0){
                    printf("%s Sort du jeu.\n",gestDuJeu->joueurcourant->pseudo);    
                    pthread_exit(EXIT_SUCCESS);        
                }
            }
        }
    }
    
    pthread_exit(EXIT_SUCCESS);
}

int main(void){

    gestionnaireJeu* gj = initGestionJeu();

    gj->manche = 3;

    joueur* j1 = NewJoueur("TOTO", 0, 1);
    joueur* j2 = NewJoueur("Jean", 0, 2);

    char pseu[10];
    printf("Entrez Votre pseudo : \n");
    scanf("%s", pseu);

    joueur* j3 = NewJoueur(pseu, 1, 3);

    AjoutJoueur(gj,j1);
    AjoutJoueur(gj,j2);
    AjoutJoueur(gj,j3);

    distribuer(gj);
    for(int i=0; i<gj->nbJoueurs*gj->manche;i++){
        printf("%d | ",gj->ordreJeu[i]);
    }
    printf("\n");

//affichage avant le jeu
    for(int i=0; i<gj->nbJoueurs; i++){
        printf("%s\n", gj->listeJoueur[i]->pseudo);
        for(int j=0; j<gj->manche; j++){
            printf("%d | ", gj->listeJoueur[i]->cartesEnMain[j]);
        }
        printf("\n");
    }

    pthread_t threadjoueur[gj->nbJoueurs];
    int* resultat;

    for(int i=0; i<gj->nbJoueurs; i++){
        GestionDuJeu* gestDuJeu = calloc(1, sizeof(GestionDuJeu));
        gestDuJeu->gj = gj;
        gestDuJeu->joueurcourant = gj->listeJoueur[i];
        gestDuJeu->perdu = 1;

        pthread_create(&threadjoueur[i], NULL, thread_Joueur, gestDuJeu);
    }
    
    for(int i=0; i<gj->nbJoueurs; i++){
        pthread_join(threadjoueur[i], NULL);
    }

//affichage apres le jeu
    for(int i=0; i<gj->nbJoueurs; i++){
        printf("%s\n", gj->listeJoueur[i]->pseudo);
        for(int j=0; j<gj->manche; j++){
            printf("%d | ", gj->listeJoueur[i]->cartesEnMain[j]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}