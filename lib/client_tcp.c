#include "client_serveur.h"

#include <assert.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "common.h"

#define TRACING_MODULE "client"

/* Fait la résolution de nom : nom de domaine -> adresse IP.
 * Retour: 0 si succès; EAI_xxx si échec (cf. getaddrinfo)
 */
static int resolve_name_to_address(const char *name,  struct in_addr *addr)
{
    struct addrinfo gai_hints = {
        .ai_flags = 0,
        .ai_family = AF_INET,
        .ai_socktype = 0,
        .ai_protocol = 0,
    };
    struct addrinfo *gai_addr;
    int gai_error = getaddrinfo(name, NULL, &gai_hints, &gai_addr);
    if (gai_error == 0) {
        *addr = ((struct sockaddr_in *)gai_addr->ai_addr)->sin_addr;
        freeaddrinfo(gai_addr);
    }
    return gai_error;
}

int creer_client_tcp(const char *nom, int port, int debug)
{
    print_copyright(debug);
    ENTRY("%s(adresse = \"%s\", port = %d)", __func__, nom, port);

    struct sockaddr_in adresse = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
    };
    int gai_error;
    TRACE(gai_error, resolve_name_to_address(nom, &adresse.sin_addr),
          "[getaddrinfo] résolution de nom pour \"%s\"; statut = ", nom);
    if (gai_error) {
        GAI_ERROR("getaddrinfo", gai_error);
        RETURN(-1);
    }

    int sock;
    TRACE(sock, socket(AF_INET, SOCK_STREAM, 0), "[socket] création de socket TCP = ");
    if (sock < 0) {
        ERROR("socket");
        RETURN(-1);
    }

    int connected;
    TRACE(connected, connect(sock, (struct sockaddr *)&adresse, sizeof adresse),
          "[connect] connexion au serveur \"%s\"(%s):%d (sock = %d); statut = ",
          nom, inet_ntoa(adresse.sin_addr), port, sock);
    if (connected != 0) {
        ERROR("connect");
        RETURN(-1);
    }

    RETURN(sock);
}
