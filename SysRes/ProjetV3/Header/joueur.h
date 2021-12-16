#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    char* pseudo;
    int humain; //0 : Bot ;; 1 : Humain
    unsigned int nbCartes;
    int* cartesEnMain;
    unsigned int id;
}joueur;


joueur* NewJoueur(char* pseu, int isHumain, unsigned int identifiant);
void destroyJoueur(joueur* j);
void ajoutCarteMain(joueur* j, unsigned int carte);
void jouer(joueur* j);