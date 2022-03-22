#include <stdlib.h>
#include <stdio.h>

int main(void){
    printf("Bonjour ! Veuillez choisir une option s'il vous plait :\n1: Jouer\n2:Quitter\n");
    while(1){
        char* choix;
        scanf("%s", choix);
        
        if(choix == "1"){
            printf("Ah, vous voulez Jouer ?\n");
        }else if(choix == "2"){
            printf("Au revoir !\n");
            return 0;
        }else{
            printf("Il faut faire un choix pour continuer :)\n");
        }
        
        /*switch (choix)
        {
        case 1:
            printf("Ah, vous voulez Jouer ?\n");
            break;

        case 2:
            printf("Au revoir !\n");
            return 0;
            break;

        default:
            printf("Il faut faire un choix pour continuer :)\n");
            break;
        }*/
    }
    return 0;
}