#include "pacman.h"
#include "../error.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sys_count()
{
    char *pacPath = "var/lib/pacman/local";
    DIR *pacDir = opendir(pacPath);

    if (!pacDir)
        die("Could not open /var/lib/pacman/local", 2);

    else
    {
        int total = 0, deps = 0;
        char pkgPath[256];
        struct dirent *pkgEnt;

        while ((pkgEnt = readdir(pacDir)) != nullptr)
        {
            if (strcmp(pkgEnt->d_name, ".") == 0 || strcmp(pkgEnt->d_name, "..")== 0)
                continue;
            if (pkgEnt->d_type != DT_DIR)
                continue;

            strcpy(pkgPath, pacPath);
            strcat(pkgPath, "/");
            strcat(pkgPath, pkgEnt->d_name);

            DIR *pkgDir = opendir(pkgPath);
            if (!pkgDir)
                die("Could not open package directory", 2);

            struct dirent *dbEnt;
            while ((dbEnt = readdir(pkgDir)) != nullptr)
            {
                total++;
                if (strcmp(dbEnt->d_name, "dest") == 0)
                {
                    char destPath[256];
                    strcpy(destPath, pkgPath);
                    strcat(destPath, "/dest");

                    FILE *destFile = fopen(destPath, "r");

                }
            }
            memset(pkgPath, 0, 256 * sizeof(char));
        }
        closedir(pacDir);
    }
}
