//
// Created by alzy on 11/12/2025.
//

#include "error.h"

#include <stdio.h>
#include <stdlib.h>

void die(char *message, int status)
{
    fprintf(stderr, "ERROR: %s\n", message);
    exit(status);
}
