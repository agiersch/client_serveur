/*
 * Exemple simple de serveur TCP
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "client_serveur.h"

/* Paramètres */
#define DEFAULT_PORT 6666
#define DEBUG_LEVEL 1

int gestion_client(int socket_client)
{
    char message[256];
    int nlus = read(socket_client, message, sizeof message);
    if (nlus < 0) {
        fprintf(stderr, "Erreur de lecture du message du client: %s\n", strerror(errno));
        close(socket_client);
        return -1;
    }

    printf("Message reçu (%d): <%.*s>\n", nlus, nlus, message);

    const char salut[] = "Salut à toi le client";
    const int taille_salut = strlen(salut) + 1;
    int necrits = write(socket_client, salut, taille_salut);
    if (necrits != taille_salut) {
        fprintf(stderr, "Erreur d'envoi de message au client: %s", strerror(errno));
        close(socket_client);
        return -1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int port_number = DEFAULT_PORT;
    if (argc > 1)
        port_number = atoi(argv[1]);
    
    fprintf(stderr, "Création du serveur sur le port %d\n", port_number);
    int socket_serveur = creer_serveur_tcp(port_number, DEBUG_LEVEL);
    if (socket_serveur < 0) {
        fprintf(stderr, "Échec de la création du serveur\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        int socket_client = attendre_client_tcp(socket_serveur, DEBUG_LEVEL);
        if (socket_client < 0) {
            fprintf(stderr, "Échec de l'attente du client\n");
            close(socket_serveur);
            exit(EXIT_FAILURE);
        }

        switch(fork()) {
        case -1:
            perror("fork");
            close(socket_client);
            close(socket_serveur);
            exit(EXIT_FAILURE);

        case 0:
            close(socket_serveur);
            int statut = gestion_client(socket_client);
            close(socket_client);
            exit(statut);
        }

        close(socket_client);
    }
        
    return 0;
}
