#include "proto.h"

#include <stdio.h>
#include <Windows.h>
#include <Iphlpapi.h>
#include <intrin.h>

// Fonction de recup des infos systemes

char* GetSysInf() {
    char* sysInfo = (char*)malloc(4096); // Allouer un espace mémoire pour stocker les informations
    
    if (sysInfo == NULL) {
        return NULL; // Échec de l'allocation de mémoire
    }

    // Récupérer le nom de la machine
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);
    if (GetComputerNameA(computerName, &size)) {
        sprintf(sysInfo, "Nom de la machine : %s\n", computerName);
    } else {
        sprintf(sysInfo, "Impossible de récupérer le nom de la machine\n");
    }

    // Récupérer les spécifications du CPU
    int cpuInfo[4] = { 0 };
    char cpuBrandString[0x40];
    __cpuid(cpuInfo, 0x80000000);
    unsigned int nExIds = cpuInfo[0];
    memset(cpuBrandString, 0, sizeof(cpuBrandString));
    for (unsigned int i = 0x80000000; i <= nExIds; ++i) {
        __cpuid(cpuInfo, i);
        if (i == 0x80000002) {
            memcpy(cpuBrandString, cpuInfo, sizeof(cpuInfo));
        } else if (i == 0x80000003) {
            memcpy(cpuBrandString + 16, cpuInfo, sizeof(cpuInfo));
        } else if (i == 0x80000004) {
            memcpy(cpuBrandString + 32, cpuInfo, sizeof(cpuInfo));
        }
    }
    sprintf(sysInfo + strlen(sysInfo), "Spécifications du CPU : %s\n", cpuBrandString);

    // Récupérer le nombre de RAM installée
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memInfo)) {
        sprintf(sysInfo + strlen(sysInfo), "Taille de la mémoire RAM installée : %llu Mo\n", memInfo.ullTotalPhys / (1024 * 1024));
    } else {
        sprintf(sysInfo + strlen(sysInfo), "Impossible de récupérer la taille de la mémoire RAM\n");
    }

    // Récupérer le nom de session actuel
    char userName[UNLEN + 1];
    size = sizeof(userName);
    if (GetUserNameA(userName, &size)) {
        sprintf(sysInfo + strlen(sysInfo), "Nom d'utilisateur : %s\n", userName);
    } else {
        sprintf(sysInfo + strlen(sysInfo), "Impossible de récupérer le nom d'utilisateur\n");
    }

    // Récupérer le pays/localisation
    char country[10];
    int result = GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SISO3166CTRYNAME, country, sizeof(country));
    if (result > 0) {
        sprintf(sysInfo + strlen(sysInfo), "Pays : %s\n", country);
    } else {
        sprintf(sysInfo + strlen(sysInfo), "Impossible de récupérer le pays\n");
    }
    
    strcat (sysInfo, "#");
    return sysInfo;
}

