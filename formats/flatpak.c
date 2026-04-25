#include "flatpak.h"
#include "../error.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void flCounter(int *apps, int *runs, char *appPath, char *runPath) 
{
    DIR *appDir = opendir(appPath);
    DIR *runDir = opendir(runPath);

    if (!appDir || !runDir)
        return;

    struct dirent *entry;

    while ((entry = readdir(appDir)) != NULL) 
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0 ||
            entry->d_type != DT_DIR) 
        continue;
        (*apps)++;
    }
        
    while ((entry = readdir(runDir)) != NULL) 
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0 ||
            entry->d_type != DT_DIR) 
        continue;
        (*runs)++;
    }

    closedir(appDir);
    closedir(runDir);
}

void flat_count()
{
    char *sysApps = "/var/lib/flatpak/app";
    char *sysRuns = "/var/lib/flatpak/runtime";
    
    char *home_dir = getenv("HOME"); 

    char usrApps[64]; 
    strcpy(usrApps,home_dir);
    strcat(usrApps,"/.local/share/flatpak/app");

    char usrRuns[64];
    strcpy(usrRuns,home_dir);
    strcat(usrRuns,"/.local/share/flatpak/runtime");

    int apps = 0, runs = 0;
    flCounter(&apps, &runs, sysApps, sysRuns);
    flCounter(&apps, &runs, usrApps, usrRuns);
   
    printf( "Flatpak:\n"
            "  Total: %d\n"
            "    App    : %d\n"
            "    Runtime: %d\n\n",
            apps + runs,
            apps,
            runs);
}
