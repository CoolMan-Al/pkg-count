#include "snap.h"

#include <dirent.h>
#include <stdio.h>

#include "../error.h"

void snap_count()
{
    DIR *appdir = opendir("/var/lib/snapd/desktop/applications");
    DIR *totaldir = opendir("/var/lib/snapd/snaps");

    if (!appdir || !totaldir)
        die("Could not open snapd directories", 2);

    // Init as -2 because . and .. count
    int apps = -2, total = -2;
    while (readdir(appdir) != NULL)
        apps++;
    while (readdir(totaldir) != NULL)
        total++;

    closedir(appdir);
    closedir(totaldir);

    printf("Snap:\n"
           "  Total: %d\n"
           "    App    : %d\n"
           "    Runtime: %d\n\n",
           total,
           apps,
           total - apps);
}
