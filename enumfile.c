#include <windows.h>
#include "proto.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
                                    //L'argument qui doit etre envoyé est un path + * (Exemple C:\\windows\\systeme\\*)

char *enumfile(char *chemin) {
    if (strlen(chemin) > 0 && chemin[strlen(chemin) - 1] == '\n') {
        chemin[strlen(chemin) - 1] = '\0'; // Supprime le saut de ligne
    }

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(chemin, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return strdup("Impossible de trouver des fichiers dans le répertoire spécifié.#\n");
    }

    char *result = NULL; // Initialisation du résultat
    char temp[1024]; // Tampon temporaire pour la construction de la chaîne

    do {
        if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
            char line[1024];
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                snprintf(line, sizeof(line), "Répertoire : %s\n", findFileData.cFileName);
            } else {
                snprintf(line, sizeof(line), "Fichier : %s\n", findFileData.cFileName);
            }

            if (result) {
                int result_len = strlen(result);
                int line_len = strlen(line);
                char *new_result = (char *)malloc(result_len + line_len + 1); // +1 for null-terminator
                strcpy(new_result, result);
                strcpy(new_result + result_len, line);
                free(result);
                result = new_result;
            } else {
                result = strdup(line);
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
    strcat (result, "#");
    return result;
}