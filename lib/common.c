#include "common.h"

#include <stdio.h>

static const char NAME[] = "Petite bibliothèque client-serveur";
static const char COPYRIGHT[] = "Copyright (c) 2022, Arnaud Giersch <arnaud.giersch@univ-fcomte.fr>";

void print_copyright(int enabled)
{
    static int printed = 0;
    if (!enabled || printed)
        return;

    fprintf(stderr, "%s\n%s\n", NAME, COPYRIGHT);
    printed = 1;
}
