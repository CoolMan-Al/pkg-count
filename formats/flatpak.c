#include "flatpak.h"
#include "../error.h"

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void flat_count()
{
    char *sysPath = "/var/lib/flatpak";
    char *usrPath = "~/.local/share/flatpak";

    char *apps = "/app";
    char *runs = "/runtime";

    char appPath[32];
    char runPath[32];

    
    DIR *appDir = opendir(appPath);
    DIR *runDir = opendir(runPath);

    if (!appDir || !runDir)
        die("Could not open app or runtime directory", 2);

    // Init as -2 because . and .. count
    int apps = -2, runs = -2;
    while (readdir(appDir) != NULL)
        apps++;
    while (readdir(runDir) != NULL)
        runs++;

    closedir(appDir);
    closedir(runDir);

    printf("Flatpak:\n"
    "  Total: %d\n"
    "    App    : %d\n"
    "    Runtime: %d\n\n",
    apps + runs,
    apps,
    runs);
}
