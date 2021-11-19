#include "init.h"
#include <stdio.h>


int main(int argc, char* argv[]) {
    printf("Il y a %s joueurs dans la partie\n", argv[1]);
    init(argv[1]);
    argc++;
    return 0;
}
