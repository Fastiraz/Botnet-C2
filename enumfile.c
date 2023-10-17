#include <windows.h>
#include "proto.h"
#include <stdio.h>

void enumfile(const char* chemin) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(strcat(chemin, "\\*"), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Impossible d'ouvrir le répertoire %s\n", chemin);
        return;
    }

    printf("Repertoire -> %s :\n", chemin);
    
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            printf("%s\n", findFileData.cFileName);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

