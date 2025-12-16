cmake_minimum_required(VERSION 3.31)
project(pkg_count C)
set(CMAKE_C_STANDARD 23)

option(APT "Build with apt support" OFF)
option(PAC "Build with pacman support" OFF)
# Otherwise build with binary counter

if (APT)
    set(ENABLE_APT ON)
elseif (PAC)
    set(ENABLE_PACMAN ON)
else()
    set(ENABLE_NONE ON)
endif()

add_executable(pkg_count
        main.c
        error.c
        formats/flatpak.c
        formats/snap.c
)

target_sources(pkg_count PRIVATE
        $<$<BOOL:${ENABLE_APT}>:formats/apt.c>
        $<$<BOOL:${ENABLE_PACMAN}>:formats/pacman.c>
        $<$<BOOL:${ENABLE_NONE}>:formats/none.c>
)

if (ENABLE_APT)
    add_compile_definitions(USE_APT)
elseif (ENABLE_PACMAN)
    add_compile_definitions(USE_PACMAN)
endif()
