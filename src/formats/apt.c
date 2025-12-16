#include "apt.h"
#include "../error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sys_count()
{
    FILE *totalfile = fopen("/var/lib/dpkg/status", "r");
    FILE *depfile = fopen("/var/lib/apt/extended_states", "r");

    if (!totalfile || !depfile)
        die("Could not open /var/lib/dpkg/status OR /var/lib/apt/extended_states", 2);

    else
    {
        char *buffer = nullptr;
        int total = 0, deps = 0;

        size_t len = 0;
        while (getline(&buffer, &len, totalfile) != -1)
            if (strstr(buffer, "Package: "))
                total++;

        len = 0;
        while (getline(&buffer, &len, depfile) != -1)
            if (strstr(buffer, "Package: "))
                deps++;

        fclose(totalfile);
        fclose(depfile);
        free(buffer);

        printf("Dpkg:\n"
               "  Total: %d\n"
               "    Manual: %d\n"
               "    Auto  : %d\n\n",
               total,
               total - deps,deps);
    }
}
