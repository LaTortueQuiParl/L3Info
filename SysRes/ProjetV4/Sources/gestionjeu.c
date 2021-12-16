#include "../Header/gestionjeu.h"
#include <time.h>

gestionnaireJeu *initGestionJeu() {
  gestionnaireJeu *gj = (gestionnaireJeu *)calloc(1, sizeof(gestionnaireJeu));
  gj->deck = (int *)calloc(100, sizeof(int));
  for (int i = 0; i < 100; i++) {
    gj->deck[i] = i + 1;
  }
  gj->cartePosee = (unsigned int *)calloc(100, sizeof(unsigned int));
  gj->ordreJeu = (unsigned int *)calloc(80, sizeof(unsigned int));
  gj->manche = 0;
  gj->nbManche = 0;
  gj->nbJoueurs = 0;
  gj->listeJoueur = (joueur **)calloc(256, sizeof(joueur *));

  return gj;
}

void AjoutJoueur(gestionnaireJeu *gj, joueur *j) {
  gj->listeJoueur[gj->nbJoueurs] = j;
  gj->nbJoueurs++;
}

void destroyGestionnaire(gestionnaireJeu *gj) {
  for (int i = 0; i < gj->nbJoueurs; i++) {
    destroyJoueur(gj->listeJoueur[i]);
  }
  free(gj->listeJoueur);
  free(gj->cartePosee);
  free(gj->deck);
  free(gj->ordreJeu);
  free(gj);
}

void distribuer(gestionnaireJeu *gj) {
  srand(time(NULL));

  int cartedistrib[gj->nbJoueurs * gj->manche];

  for (int jou = 0; jou < gj->nbJoueurs; jou++) {
    gj->listeJoueur[jou]->cartesEnMain = (int *)calloc(gj->manche, sizeof(int));
  }
  int k = 0;
  for (int i = 0; i < gj->manche; i++) {
    for (int j = 0; j < gj->nbJoueurs; j++) {
      int cartedistribuee = rand() % 100;
      while (gj->deck[cartedistribuee] == -1) {
        cartedistribuee = rand() % 100;
      }

      ajoutCarteMain(gj->listeJoueur[j], gj->deck[cartedistribuee]);

      cartedistrib[k] = gj->deck[cartedistribuee];
      gj->ordreJeu[k] = gj->listeJoueur[j]->id;
      k++;

      gj->deck[cartedistribuee] = -1;
    }
  }
  for (int i = 0; i < (gj->nbJoueurs * gj->manche) - 1; i++) {
    for (int j = i + 1; j < (gj->nbJoueurs * gj->manche); j++) {
      if (cartedistrib[i] > cartedistrib[j]) {
        int c = cartedistrib[i];
        cartedistrib[i] = cartedistrib[j];
        cartedistrib[j] = c;
        int ji = gj->ordreJeu[i];
        gj->ordreJeu[i] = gj->ordreJeu[j];
        gj->ordreJeu[j] = ji;
      }
    }
  }
}

int jeu(joueur *j, gestionnaireJeu *gj) {
  int i = 0;
  while (gj->ordreJeu[i] == -1) {
    i++;
  }
  if (gj->ordreJeu[i] == j->id) {
    gj->cartePosee[i] = j->cartesEnMain[0];
    jouer(j);
    gj->ordreJeu[i] = -1;
    return 1;
  } else {
    printf("%s Vous a fait perdre !\n", j->pseudo);
    return 0;
  }
}