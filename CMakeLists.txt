cmake_minimum_required(VERSION 3.19)
project(AlexsProject C)

set(CMAKE_C_STANDARD 99)

add_executable(AlexsProject main.c struct.h saisie.c saisie.h init.c init.h ouvrier.c ouvrier.h chantier.c chantier.h horaire.c horaire.h)