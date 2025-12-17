# Note: The code for deciding which package format to compile with was generated using Proton Lumo.
cmake_minimum_required(VERSION 3.31)
project(pkg-count C)
set(CMAKE_C_STANDARD 23)

option(APT "Build with apt support" OFF)
option(RPM "Build with rpm support" OFF)
option(PAC "Build with pacman support" OFF)
# ELSE      Build with binary counter

if (APT)
    set(ENABLE_APT ON)
elseif (RPM)
    set(ENABLE_RPM ON)
elseif (PAC)
    set(ENABLE_PACMAN ON)
else()
    set(ENABLE_NONE ON)
endif()

add_executable(pkg-count
        src/main.c
        src/error.c
        src/formats/flatpak.c
        src/formats/snap.c
)

target_sources(pkg-count PRIVATE
        $<$<BOOL:${ENABLE_APT}>:src/formats/apt.c>
        $<$<BOOL:${ENABLE_RPM}>:src/formats/rpm.c>
        $<$<BOOL:${ENABLE_PACMAN}>:src/formats/pacman.c>
        $<$<BOOL:${ENABLE_NONE}>:src/formats/none.c>
)

if (ENABLE_APT)
    add_compile_definitions(USE_APT)
elseif (ENABLE_RPM)
    add_compile_definitions(USE_RPM)
elseif (ENABLE_PACMAN)
    add_compile_definitions(USE_PACMAN)
endif()
