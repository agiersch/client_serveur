CC = gcc
CFLAGS = -g -Og -Wall -Wextra -std=gnu11

CS_LIB = client_serveur
CS_LIB_A  = $(CS_LIB).a
CS_LIB_SO = $(CS_LIB).so

CSRC = client_tcp.c serveur_tcp.c
OBJ = $(CSRC:%.c=%.o)

.PHONY: all clean realclean

all: $(CS_LIB_A)

clean:
	-$(RM) .depend *~
	-$(RM) $(OBJ)

distclean: clean
	-$(RM) $(CS_LIB_A) $(CS_LIB_SO)

$(CS_LIB_A): $(OBJ) common.c.in
	sed "s|@@@DATE@@@|$$(date +%c)|" common.c.in > common.c
	$(MAKE) common.o
	ar -rv  $@ $(filter %.o,$^) common.o

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),realclean)

.depend: $(CSRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MM $^ > $@

-include .depend

endif
endif

