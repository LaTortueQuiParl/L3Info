#ifndef GESTIONNAIRE_H
#define GESTIONNAIRE_H

#include <stdio.h>

void gest();

typedef struct {
    int* deck; // [ -1, 1, 2, 3, 4, -1, 6, 7...]
    int* cartePosee;
    int* ordreJeu;
    int manche;
    int nbManche;
}gestionnaireJeu;

#endif
