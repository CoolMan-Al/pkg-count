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
    DIR *pkgDir = opendir(pkgPath);

    if (!worldFile || !pkgDir)
        die("Could not open /var/lib/portage/world or var/db/pkg", 2);

    int world = 0, total = 0;

    char *buffer = NULL; size_t len = 0;
    while (getline(&buffer, &len, worldFile) != -1) world++;

    struct dirent *pkgCategory;
    buffer = malloc(256 * sizeof(char));
    while ((pkgCategory = readdir(pkgDir)) != NULL)
    {
        if (strcmp(pkgCategory->d_name, ".") == 0 ||
            strcmp(pkgCategory->d_name, "..") == 0 ||
            pkgCategory->d_type != DT_DIR) 
        continue;
        
        strcpy(buffer, pkgPath);
        strcat(buffer, "/");
        strcat(buffer, pkgCategory->d_name);

        DIR *categoryPath = opendir(buffer);
        struct dirent *pkgName;

        while ((pkgName = readdir(categoryPath)) != NULL)
        {
            if (strcmp(pkgName->d_name, ".") == 0 ||
                strcmp(pkgName->d_name, "..") == 0 ||
                pkgName->d_type != DT_DIR) 
            continue;
            total++;
        }
        closedir(categoryPath);
    }
    closedir(pkgDir);
    free(buffer);

    printf("Portage:\n"
           "  Total: %d\n"
           "    World: %d\n"
           "    Dep  : %d\n",
           total,
           world,
           total - world);
}