#include <stdlib.h>
#include <stdio.h>

extern unsigned int botId;
extern unsigned int joueurId;

typedef struct
{
    unsigned char* pseudo;
    int humain; //0 : Bot ;; 1 : Humain
    unsigned int nbCartes;
    int* cartesEnMain;
    unsigned int id;
}joueur;


joueur* NewJoueur(int isHumain);
void destroyJoueur(joueur* j);
void ajoutCarteMain(joueur* j, unsigned int carte);
void jouer(joueur* j);