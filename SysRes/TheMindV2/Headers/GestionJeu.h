#include "Joueur.h"

typedef struct GestionJeu
{
    unsigned int mancheActuel;
    unsigned int nbMancheTot;
    Joueur** joueurs;
    unsigned int nbJoueurs;
    int* cartesPosees;
    int* paquet;
}GestionJeu;

GestionJeu* initGestionJeu();

void AjoutJoueur(GestionJeu* gestJeu, Joueur* j);
void Distribution(GestionJeu* gestJeu);