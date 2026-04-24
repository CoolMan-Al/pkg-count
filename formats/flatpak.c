#include "flatpak.h"
#include "../error.h"

#include <dirent.h>
#include <stdio.h>

void flat_count()
{
    DIR *appdir = opendir("/var/lib/flatpak/app");
    DIR *rundir = opendir("/var/lib/flatpak/runtime");

    if (!appdir || !rundir)
        die("Could not open app or runtime directory in /var/lib/flatpak", 2);

    // Init as -2 because . and .. count
    int apps = -2, runs = -2;
    while (readdir(appdir) != NULL)
        apps++;
    while (readdir(rundir) != NULL)
        runs++;

    closedir(appdir);
    closedir(rundir);

    printf("Flatpak:\n"
    "  Total: %d\n"
    "    App    : %d\n"
    "    Runtime: %d\n\n",
    apps + runs,
    apps,
    runs);
}
