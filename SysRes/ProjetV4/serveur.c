#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "gestionjeu.h"

typedef struct CreationJoueur{
    pthread_t sok;
    int idClient;
    int socket;
    gestionnaireJeu* gestionJeu;
}CreationJoueur;

void *creationJoueur(void *arg){
    CreationJoueur* creaJoueur = arg;
    int socket = creaJoueur->socket;
    char message_Serveur[256] = "Quel est votre pseudo ?\n";
    char reponse_Client[256];

    send(socket, &message_Serveur, strlen(message_Serveur), 0);

    recv(socket, &reponse_Client, sizeof(reponse_Client), 0);

    joueur* j = NewJoueur(1,reponse_Client, creaJoueur->idClient);

    printf("%s | %ld\n", j->pseudo, strlen(j->pseudo));
    AjoutJoueur(creaJoueur->gestionJeu, j);
    printf("%s | %ld\n", creaJoueur->gestionJeu->listeJoueur[0].pseudo, strlen(creaJoueur->gestionJeu->listeJoueur[0].pseudo));
    printf("%d\n", creaJoueur->sok);
    if(creaJoueur->sok == 2){
        printf("%s | %ld\n", creaJoueur->gestionJeu->listeJoueur[1].pseudo, strlen(creaJoueur->gestionJeu->listeJoueur[1].pseudo));    
    }

    printf("Le joueur %s s'est connecte\n", j->pseudo);

    char msgMenu[256] = "1: Jouer\n2: Quitter\n";

    send(socket, msgMenu, sizeof(msgMenu), 0);

    /*char choixClient[256];
    while(1){
        recv(socket, &choixClient, sizeof(choixClient), 0);
        if(!strcmp(choixClient, "1")){
            printf("%s veut Jouer\n", j->pseudo);
        }
        if(!strcmp(choixClient, "2")){
            printf("%s nous quitte ! (ce salaud)\n",j->pseudo);
            break;
        }
    }*/

    close(socket);
    //free(creaJoueur);
    pthread_exit(NULL);
    return creaJoueur;
}

int main(void){
    //char message_Serveur[256] = "Quel est votre pseudo ?";
    //char reponse_Client[256];

    int ID_CLIENT = 1;
    gestionnaireJeu* THE_MIND_GAME = initGestionJeu();

    //Création du socket Serveur
    int socketServeur = socket(AF_INET,SOCK_STREAM, 0);

    //On définis l'adresse du serveur
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(30000);
    sockaddr.sin_addr.s_addr = INADDR_ANY;

    //On bind l'adresse sur le port et l'adresse fournit
    bind(socketServeur, (struct sockaddr *)&sockaddr,sizeof(sockaddr));

    //Le serveur se met sur écoute et peut avoir jusqu'à 5 clients en attente.
    listen(socketServeur, 5);

    int nbJ;
    printf("Entrez le nombre de joueur : ");
    scanf("%u", &nbJ);

    CreationJoueur* creaJoueur = (CreationJoueur*)calloc(nbJ,sizeof(creaJoueur));

    for(int i=0; i<nbJ; i++){
        int socketClient;
        socketClient = accept(socketServeur, NULL, NULL);
        printf("accept\n");

        printf("Client: %d\n", socketClient);
        
        creaJoueur[i].socket = socketClient;
        creaJoueur[i].idClient = ID_CLIENT;
        ID_CLIENT++;
        creaJoueur[i].gestionJeu = THE_MIND_GAME;
        creaJoueur[i].sok = i+1;
        //printf("Pthread : %d\n", creaJoueur[i].sok);
        
        pthread_create(&creaJoueur[i].sok, NULL, &creationJoueur, &creaJoueur[i]);

    }

    for(int i=0; i<nbJ; i++){
        pthread_join(creaJoueur[i].sok, NULL);
    }

    printf("Il y a assez de joueur, la partie peut commencer");

    THE_MIND_GAME->manche = 1;

    distribuer(THE_MIND_GAME);

    /*for(int i=0; i<THE_MIND_GAME->nbJoueurs; i++){
        printf("%s\n", THE_MIND_GAME->listeJoueur[i]->pseudo);
        for(int j=0; j<THE_MIND_GAME->manche; j++){
            printf("%d | ", THE_MIND_GAME->listeJoueur[i]->cartesEnMain[j]);
        }
    }*/

    /*
    //On accepte la connexion du/des client(s)
    int socketClient;
    socketClient = accept(socketServeur, NULL, NULL);

    //On envoie un message au client
    send(socketClient, message_Serveur, sizeof(message_Serveur), 0);

    recv(socketClient, &reponse_Client, sizeof(reponse_Client), 0);

    joueur* j = NewJoueur(1,reponse_Client,identClient);
    identClient++;

    printf("Le joueur %s s'est connecte\n", j->pseudo);

    char msgMenu[256] = "1: Jouer\n2: Quitter\n";

    send(socketClient, msgMenu, sizeof(msgMenu), 0);

    while(1){
        recv(socketClient, &reponse_Client, sizeof(reponse_Client), 0);
        printf("Le client veut : ");
        if(!strcmp(reponse_Client,"1")){
            printf("Jouer\n");
        }
        if(!strcmp(reponse_Client, "2")){
            printf("Quitter\n");
            break;
        }
    }
    */
    //On ferme les sockets
    //close(socketClient);
    close(socketServeur);

    return 0;
}