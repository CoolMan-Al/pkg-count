#if defined(APT)
    #include "formats/apt.h"
    define
#elif defined(PAC)
    #include "formats/pacman.h"
#endif

#include "formats/flatpak.h"
#include "formats/snap.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define VERSION 0.4

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)
            printf("Package Counter\nVersion: %.2f\n", VERSION);

        else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
            printf("Usage: pkg_count [OPTION]\n"
                   "  -v, --version\t"
                   "output version information and exit\n"
                   "  -h, --help\t"
                   "display this page and exit\n");

        else
            printf("pkg_count: Unknown Option '%s'\n"
                   "Try pkg_count --help for more information.",
                   argv[1]);
    }
    else
    {
        sys_count();

        if (access("/usr/bin/flatpak", X_OK) == 0)
            flat_count();

        if (access("/usr/bin/snap", X_OK) == 0)
            snap_count();
    }
    return 0;
}
