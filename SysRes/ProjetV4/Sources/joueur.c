#include "../Header/joueur.h"

joueur *NewJoueur(char *pseu, int isHumain, unsigned int i) {
  joueur *j = (joueur *)calloc(1, sizeof(joueur));
  j->pseudo = pseu;
  j->nbCartes = 0;
  j->id = i;
  j->humain = isHumain;

  return j;
}

void destroyJoueur(joueur *j) {
  free(j->cartesEnMain);
  free(j->pseudo);
  free(j);
}

void ajoutCarteMain(joueur *j, unsigned int carte) {
  j->cartesEnMain[j->nbCartes] = carte;
  j->nbCartes++;
  int c;

  for (int i = 0; i < j->nbCartes - 1; i++) {
    for (int k = i + 1; k < j->nbCartes; k++) {
      if (j->cartesEnMain[i] > j->cartesEnMain[k]) {
        c = j->cartesEnMain[i];
        j->cartesEnMain[i] = j->cartesEnMain[k];
        j->cartesEnMain[k] = c;
      }
    }
  }
}

void jouer(joueur *j) {
  for (int i = 0; i < j->nbCartes - 1; i++) {
    j->cartesEnMain[i] = j->cartesEnMain[i + 1];
  }
  j->cartesEnMain[j->nbCartes - 1] = -1;
  j->nbCartes--;
}