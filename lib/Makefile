CC = gcc
CFLAGS = -g -Og -Wall -Wextra -std=gnu11

CS_LIB = client_serveur
CS_LIB_A  = $(CS_LIB).a
CS_LIB_SO = $(CS_LIB).so

CSRC = client_tcp.c serveur_tcp.c common.c
HSRC = common.h
OBJ = $(CSRC:%.c=%.o)

.PHONY: all clean realclean

all: $(CS_LIB_A)

clean:
	-$(RM) .depend *~
	-$(RM) $(OBJ)

distclean: clean
	-$(RM) $(CS_LIB_A) $(CS_LIB_SO)

$(CS_LIB_A): $(OBJ)
	ar -rv  $@ $^

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),realclean)

.depend: $(CSRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MM $^ > $@

-include .depend

endif
endif

