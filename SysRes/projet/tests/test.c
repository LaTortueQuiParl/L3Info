#include <stdio.h>

#define RED     "\33[1;31m"
#define GREEN   "\33[1;32m"
#define YELLOW  "\33[1;33m"
#define BLUE    "\33[1;34m"
#define MAGENTA "\33[1;35m"
#define CYAN    "\33[1;36m"
#define RESET   "\33[0m"
#define BOLD    "\33[1m"
#define NOBOLD    "\33[22m"


int rate = 0;
int reussi = 0;

void affichage(){
    printf("\n");
    int total = reussi + rate;
    printf(BOLD);
    printf("Synthesis | Tested: ");
    printf(BLUE "%d" RESET, total);
    printf(" | Passed: ");
    printf(GREEN "%d" RESET, reussi);
    printf(" | Failed: ");
    printf(RED "%d" RESET, rate);
    printf(NOBOLD);
    printf("\n\n");
}

int main(){
    affichage();
    return 0;
}
