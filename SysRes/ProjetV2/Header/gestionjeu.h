#include <stdio.h>
#include <stdlib.h>

#include "joueur.h"

typedef struct {
    int* deck; // [ -1, 1, 2, 3, 4, -1, 6, 7...]
    unsigned int* cartePosee;
    unsigned int* ordreJeu;
    unsigned int manche;
    unsigned int nbManche;
    unsigned int nbJoueurs;
    joueur** listeJoueur; // Liste des joueurs
}gestionnaireJeu;

gestionnaireJeu* initGestionJeu();
void AjoutJoueur(gestionnaireJeu* gj, joueur* j);
void destroyGestionnaire(gestionnaireJeu* gj);
void initCartes(joueur* j);

void distribuer(gestionnaireJeu* gj);

void jeu(gestionnaireJeu* gj);