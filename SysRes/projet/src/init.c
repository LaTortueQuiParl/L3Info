#include "init.h"

void init(char* nbJoueur) {
    printf("In function init\n");
    joueur* j1;
    joueur* j2;
    gestionnaireJeu* g;
    g->deck = calloc(100, sizeof(int));
    for (int i = 1; i <= 100; i++) {
        g->deck[i-1] = i;
        printf("carte: %d\n", g->deck[i-1]);
    }
    free(g->deck);
}
