#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void){

    //Message de communication entre le serveur et le client
    char msgduserveur[256];
    char response[256];

    //création du socket
    int socketClient = socket(AF_INET, SOCK_STREAM, 0);

    //On définit l'adresse du socket et son port
    struct sockaddr_in addrServer;
    addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(30000);

    int connexion_statut = connect(socketClient, (const struct sockaddr *)&addrServer, sizeof(addrServer));
    if(connexion_statut == -1){
        printf("Value of : %d\n", errno);
        printf("Il y a eu une erreur lors de la connexion de votre socket.\n\n");
    }

    //On récupere des données du serveur
    recv(socketClient, &msgduserveur, sizeof(msgduserveur), 0);

    //On affiche ce que le serveur a envoyé
    printf("Message du serveur : %s\n", msgduserveur);
    
    scanf("%s", response);

    send(socketClient, &response, sizeof(response), 0);

    recv(socketClient, &msgduserveur, sizeof(msgduserveur), 0);

    while(1)
    {
    
        printf("Menu :\n%s", msgduserveur);
        scanf("%s", response);
        
        send(socketClient, &response, sizeof(response), 0);
        if(!strcmp(response,"2")){
            break;
        }    
    }
    
    //on ferme le socket
    close(socketClient);

    return 0;
}