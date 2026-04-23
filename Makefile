CC=gcc

deb:
    ${CC} main.c formats/apt.c -o pkg_count

clean:
