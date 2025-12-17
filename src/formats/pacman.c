#include "pacman.h"
#include "../error.h"

#include <dirent.h>
#include <stdio.h>
#include <string.h>

void sys_count()
{
    char *pacPath = "/var/lib/pacman/local/";
    DIR *pacDir = opendir(pacPath);

    if (!pacDir)
        die("Could not open /var/lib/pacman/local", 2);

    else
    {
        int total = 0, deps = 0;
        char pkgPath[256];
        struct dirent *pacEnt;

        while ((pacEnt = readdir(pacDir)) != nullptr)
        {
            if (strcmp(pacEnt->d_name, ".") == 0 ||
                strcmp(pacEnt->d_name, "..")== 0 ||
                pacEnt->d_type != DT_DIR) continue;

            strcpy(pkgPath, pacPath);
            strcat(pkgPath, pacEnt->d_name);

            DIR *pkgDir = opendir(pkgPath);
            if (!pkgDir)
                die("Could not open package directory", 2);

            struct dirent *pkgEnt;
            while ((pkgEnt = readdir(pkgDir)) != nullptr)
            {
                if (strcmp(pkgEnt->d_name, "desc") == 0 && pkgEnt->d_type == DT_REG)
                {
                    total++;
                    char descPath[256];
                    strcpy(descPath, pkgPath);
                    strcat(descPath, "/desc");

                    FILE *descFile = fopen(descPath, "r");
                    char descBuf[16];

                    while (fgets(descBuf, sizeof(descBuf), descFile))
                    {
                        if (strcmp(descBuf, "%REASON%\n") == 0)
                        {
                            deps++;
                            break;
                        }
                    }
                    fclose(descFile);
                }
            }
            memset(pkgPath, 0,sizeof(pkgPath));
        }
        closedir(pacDir);

        printf("Pacman:\n"
               "  Total: %d\n"
               "    Manual: %d\n"
               "    Auto  : %d\n\n",
               total,
               total - deps,
               deps);
    }
}
