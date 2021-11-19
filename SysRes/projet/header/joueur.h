#ifndef JOUEUR_H
#define JOUEUR_H

typedef struct{
    int nbCartes;
    int* cartes;
    int id;
    int humain; // 1 signifie que le joueur est humain
}joueur;

#endif
