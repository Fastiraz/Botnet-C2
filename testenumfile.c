#include <windows.h>
#include <stdio.h>
#include <string.h>

void ListFilesAndDirectoriesInDirectory(const char *directoryPath) {
    WIN32_FIND_DATA findFileData;
    char searchPath[MAX_PATH];
    strcpy(searchPath, directoryPath);
    strcat(searchPath, "\\*");
    
    HANDLE hFind = FindFirstFile(searchPath, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Impossible de trouver des fichiers dans le répertoire spécifié.\n");
        return;
    }

    printf("Fichiers et répertoires dans le répertoire '%s':\n", directoryPath);

    do {
        if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                printf("Répertoire : %s\n", findFileData.cFileName);
            } else {
                printf("Fichier : %s\n", findFileData.cFileName);
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Utilisation : %s <chemin_du_répertoire>\n", argv[0]);
        return 1;
    }

    const char *directoryPath = argv[1];
    ListFilesAndDirectoriesInDirectory(directoryPath);

    return 0;
}
