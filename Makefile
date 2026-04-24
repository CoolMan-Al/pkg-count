CC = gcc -o pkg_count
CFLAGS ?=
apt :
	${CC} ${CFLAGS} main.c formats/flatpak.c formats/snap.c formats/apt.c error.c -DAPT
pacman :
	${CC} ${CFLAGS} main.c formats/flatpak.c formats/snap.c formats/pacman.c error.c -DPACMAN
portage:
	${CC} ${CFLAGS} main.c formats/flatpak.c formats/snap.c formats/portage.c error.c -DPORTAGE