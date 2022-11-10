
EXEMPLE = serveur_tcp

CC = gcc
CFLAGS = -g -Og -Wall -Wextra -I./lib

.PHONY: all

all: serveur_tcp client_tcp

serveur_tcp: serveur_tcp.c lib/client_serveur.a
	$(CC) $(CFLAGS) $^ -o $@

client_tcp: client_tcp.c lib/client_serveur.a
	$(CC) $(CFLAGS) $^ -o $@
