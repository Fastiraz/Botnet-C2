#include <windows.h>
#include "proto.h"
#include <stdio.h>
#define PREFETCH_DIRECTORY "C:\\Windows\\Prefetch" 

const char *deletePrefetchFiles() {
  WIN32_FIND_DATA findData;
  HANDLE hFind;
  char path[MAX_PATH];

  // Concatenation entier pour le dir prefetch

  snprintf(path, MAX_PATH, "%s\\*", PREFETCH_DIRECTORY);

  // Trouver le premier fichier prefetch du dossier
  
  hFind = FindFirstFile(path, &findData);
  if (hFind == INVALID_HANDLE_VALUE) {
    return ("Impossible de trouver le fichier#");
  }

  // Iteration de tout les fichier du dossier preftech
  do {
    // Passe le dossier parent et le dossir actuel
    if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0) {
      continue;
    }

    // Concatenation du path complet
    snprintf(path, MAX_PATH, "%s\\%s", PREFETCH_DIRECTORY, findData.cFileName);

    // Suppression des fichiers
    if (!DeleteFile(path)) {
      //printf("Impossible de supprimer le fichier '%s' (%d)\n", path, GetLastError());
    }
  } while (FindNextFile(hFind, &findData));

  // Ferme le handle du prefetch directory
  FindClose(hFind);
  return ("Touts les prefetch ont ete supprime...#");

}