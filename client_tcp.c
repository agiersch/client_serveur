/*
 * Exemple simple de client TCP
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "client_serveur.h"

/* Paramètres */
#define DEFAULT_HOST "127.0.0.1"
#define DEFAULT_PORT 6666
#define DEBUG_LEVEL 2

int main(int argc, char *argv[])
{
    const char *serveur = DEFAULT_HOST;
    int port = DEFAULT_PORT;
    if (argc > 1)
        serveur = argv[1];
    if (argc > 2)
        port = atoi(argv[2]);

    fprintf(stderr, "Connexion au serveur %s sur le port %d\n", serveur, port);
    int sock = creer_client_tcp(serveur, port, DEBUG_LEVEL);
    if (sock < 0) {
        fprintf(stderr, "Échec de la connexion au serveur\n");
        exit(EXIT_FAILURE);
    }

    const char message[] = "Bonjour serveur";
    const int taille_message = strlen(message) + 1;
    int necrits = write(sock, message, strlen(message) + 1);
    if (necrits != taille_message) {
        fprintf(stderr, "Erreur d'envoi du message au serveur: %s\n", strerror(errno));
        close(sock);
        exit(EXIT_FAILURE);
    }

    char message_serveur[256];
    int nlus = read(sock, message_serveur, sizeof message_serveur);
    if (nlus < 0) {
        fprintf(stderr, "Erreur de lecture du message du serveur: %s\n", strerror(errno));
        close(sock);
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Message du serveur (%d): <%.*s>\n", nlus, nlus, message_serveur);
}
