#include "proto.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

const char* sysinfoall() {
    FILE* fp;
    char buffer[1024];
    char* sysInfo = NULL;

    // Ouvre un processus pour exécuter la commande systeminfo et redirige la sortie dans un flux
    fp = popen("systeminfo", "r");
    if (fp == NULL) {
        return NULL;
    }

    // Lit la sortie de la commande et la stocke dans sysInfo
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Alloue de la mémoire pour la chaîne sysInfo et copie le contenu
        if (sysInfo == NULL) {
            sysInfo = strdup(buffer);
        } else {
            sysInfo = realloc(sysInfo, strlen(sysInfo) + strlen(buffer) + 1);
            strcat(sysInfo, buffer);
        }
    }

    pclose(fp); // Ferme le flux
    strcat(sysInfo, "#");
    return sysInfo;
}
