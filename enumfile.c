#include <windows.h>
#include "proto.h"
#include <stdio.h>
#include <string.h>

void enumfile(char *chemin) { // L'argument qui doit etre envoyé doit etre "C:\\Exemple\\*"

    if (strlen(chemin) > 0 && chemin[strlen(chemin) - 1] == '\n') {
        chemin[strlen(chemin) - 1] = '\0'; // Supprime le saut de ligne
    }

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(chemin, &findFileData);


    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Impossible de trouver des fichiers dans le répertoire spécifié.\n");
        return;
    }

    printf("Fichiers et répertoires dans le répertoire '%s':\n", chemin);

    do {
        if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                printf("Repertoire : %s\n", findFileData.cFileName);
            } else {
                printf("Fichier : %s\n", findFileData.cFileName);
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}
