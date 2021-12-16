#include "Header/gestionjeu.h"
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct GestionDeJeu{
    gestionnaireJeu* gestjeur;
    joueur* jeur;
    int* nombreJoueurJoue;
}GestionDeJeu;

void *thread_test(void *arg){

    srand( time( NULL ) );
    GestionDeJeu* gestJ = (GestionDeJeu *) arg;

    while(gestJ->jeur->nbCartes>0){

        int rnd = rand() % 5;
        usleep(rnd+10000);
        printf("%s joue !\n", gestJ->jeur->pseudo);
        jouer(gestJ->jeur);

        for(int i=0; i<sizeof(gestJ->gestjeur->ordreJeu); i++){
            printf("%d\n",gestJ->gestjeur->ordreJeu[i]);
        }

        /*if(gestJ->gestjeur->ordreJeu[*gestJ->nombreJoueurJoue] != gestJ->jeur->id){
            printf("Vous avez perdu !");
            break;
        }*/
        gestJ->nombreJoueurJoue++;
        //wait
    }
    pthread_exit(NULL);

}

int main(void){

    int nbJoueurs = 3;

    gestionnaireJeu* gj = initGestionJeu();

    gj->manche = 3;

    int id = 1;

    joueur* j1 = NewJoueur("Bot n°1",0,1);
    joueur* j2 = NewJoueur("Bot n°2",0,2);
    joueur* j3 = NewJoueur("Bot n°3",0,3);

    AjoutJoueur(gj, j1);
    AjoutJoueur(gj, j2);
    AjoutJoueur(gj, j3);

    distribuer(gj);

    for(int i=0; i<gj->nbJoueurs; i++){
        printf("%s\n", gj->listeJoueur[i]->pseudo);
        for(int j=0; j<gj->manche; j++){
            printf("%d | ", gj->listeJoueur[i]->cartesEnMain[j]);
        }
        printf("\n");
    }

    pthread_t thread_Joueur[nbJoueurs];
    printf("Création des threads Joueurs.\n");

    joueur j[3] = {*j1, *j2, *j3};

    for(int i=0; i<nbJoueurs; i++){

        GestionDeJeu* gesDeJeu = (GestionDeJeu*)calloc(1,sizeof(GestionDeJeu));
        gesDeJeu->gestjeur = gj;
        gesDeJeu->jeur = &j[i];
        gesDeJeu->nombreJoueurJoue = 0;

        pthread_create(&thread_Joueur[i], NULL, thread_test, gesDeJeu);
    }
    
    for(int i=0; i<nbJoueurs; i++){
        pthread_join(thread_Joueur[i], NULL);
    }

    for(int i=0; i<gj->nbJoueurs; i++){
        printf("%s\n", gj->listeJoueur[i]->pseudo);
        for(int j=0; j<gj->manche; j++){
            printf("%d | ", gj->listeJoueur[i]->cartesEnMain[j]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}