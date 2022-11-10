#include "client_serveur.h"

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "common.h"

#define TRACING_MODULE "serveur"

#define SERVER_BACKLOG 16

int creer_serveur_tcp(int port, int debug)
{
    print_copyright(debug);
    ENTRY("%s(port = %d)", __func__, port);

    int sock;
    TRACE(sock, socket(AF_INET, SOCK_STREAM, 0), "[socket] création de socket TCP = ");
    if (sock < 0) {
        ERROR("socket");
        RETURN(-1);
    }

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = htonl(INADDR_ANY),
    };
    int bound;
    TRACE(bound, bind(sock, (struct sockaddr *)&addr, sizeof addr),
          "[bind] association au port no. %d; statut = ", port);
    if (bound != 0) {
        ERROR("bind");
        close(sock);
        RETURN(-1);
    }

    int listening;
    TRACE(listening, listen(sock, SERVER_BACKLOG), "[listen] socket en écoute; statut = ");
    if (listening != 0) {
        ERROR("listen");
        close(sock);
        RETURN(-1);
    }

    RETURN(sock);
}


static struct sockaddr_in last_client_addr;

int attendre_client_tcp(int socket_serveur, int debug)
{
    ENTRY("%s(socket_serveur = %d)", __func__, socket_serveur);

    socklen_t client_addr_len = sizeof last_client_addr;
    int socket_client;
    TRACE(socket_client, accept(socket_serveur, (struct sockaddr *)&last_client_addr, &client_addr_len),
          "[accept] attente de la connexion d'un client sur la socket no. %d; résultat = ", socket_serveur);
    if (socket_client < 0) {
        ERROR("accept");
        RETURN(-1);
    }
    RETURN(socket_client);
}

char *address_client(void)
{
    return inet_ntoa(last_client_addr.sin_addr);
}
