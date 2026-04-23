#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void die(char *message, int status)
{
    fprintf(stderr, "ERROR: %s\n", message);
    exit(status);
}
