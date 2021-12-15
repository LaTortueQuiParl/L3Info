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

typdef struct GestionClient{
    int socket;
    gestionnaireJeu* gj;
    int idClient;
}GestionClient;

void *creationJoueur(void *arg){
    GestionClient* gestClie = arg;
    int socket = (int*)gestClie->socket;
    char message_Serveur[256] = "Quel est votre pseudo ?\n";
    char reponse_Client[256];

    send(socket, &message_Serveur, strlen(message_Serveur), 0);

    recv(socket, &reponse_Client, sizeof(reponse_Client), 0);

    joueur* j = NewJoueur(1,reponse_Client, idClient);
    idClient++;

    printf("Le joueur %s s'est connecte\n", j->pseudo);

    char msgMenu[256] = "1: Jouer\n2: Quitter\n";

    send(socket, msgMenu, sizeof(msgMenu), 0);

    char choixClient[256];
    while(1){
        recv(socket, &choixClient, sizeof(choixClient), 0);
        if(!strcmp(choixClient, "1")){
            printf("%s veut Jouer\n", j->pseudo);
        }
        if(!strcmp(choixClient, "2")){
            printf("%s nous quitte ! (ce salaud)\n",j->pseudo);
            break;
        }
    }

    close(socket);
    free(arg);
    pthread_exit(NULL);
}

int main(void){
    //char message_Serveur[256] = "Quel est votre pseudo ?";
    //char reponse_Client[256];

    pthread_t clientThread;
    int idCli = 1;
    gestionnaireJeu* gestJeu = initGestionJeu();

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

    while(theMindGame->nbJoueurs<5){
        int socketClient;
        socketClient = accept(socketServeur, NULL, NULL);
        printf("accept\n");

        printf("Client: %d\n", socketClient);

        GestionClient* gestionClient = (GestionClient*)malloc(sizeof(GestionClient));
        
        gestionClient->socket = socketClient;
        gestionClient->idClient = idCli;
        gestionClient->gj = gestJeu;
        idCli++;

        
        pthread_create(&clientThread, NULL, creationJoueur, gestionClient);
    }
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