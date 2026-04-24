CC=gcc

apt:
	${CC} main.c formats/flatpak.c formats/snap.c formats/apt.c error.c -DAPT -o pkg_count

pac:
	${CC} main.c formats/flatpak.c formats/snap.c formats/pacman.c error.c -DPAC -o pkg_count
