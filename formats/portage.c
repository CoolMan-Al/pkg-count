#include "portage.h"
#include "../error.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sys_count()
{
    FILE *worldFile = fopen("/var/lib/portage/world", "r");
    char *pkgPath = "/var/db/pkg";
    DIR *alldir = opendir(pkgPath);

    if (!worldFile || !alldir)
        die("Could not open /var/lib/portage/world or var/db/pkg", 2);

    char *buffer = NULL;
    size_t len = 0;
    int manual = 0, total = 0;

    while (getline(&buffer, &len, worldFile) != -1)
            manual++;

    struct dirent *categoryName;
    buffer = malloc(256 * sizeof(char));
    while ((categoryName = readdir(alldir)) != NULL)
    {
        if (strcmp(categoryName->d_name, ".") == 0 ||
            strcmp(categoryName->d_name, "..") == 0 ||
            categoryName->d_type != DT_DIR) continue;
        
        strcpy(buffer, pkgPath);
        strcat(buffer, "/");
        strcat(buffer, categoryName->d_name);

        DIR *categoryPath = opendir(buffer);
        struct dirent *pkgName;

        while ((pkgName = readdir(categoryPath)) != NULL)
        {
            if (strcmp(pkgName->d_name, ".") == 0 ||
                strcmp(pkgName->d_name, "..") == 0 ||
                pkgName->d_type != DT_DIR) continue;
            
            total++;
        }
        closedir(categoryPath);
    }
    closedir(alldir);
    free(buffer);

    printf("Portage:\n"
           "  Total: %d\n"
           "    Manual: %d\n"
           "    Auto: %d\n",
           total,
           manual,
           total - manual);
}