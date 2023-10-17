#include "proto.h"

#include <stdio.h>
#include <Windows.h>
#include <Iphlpapi.h>
#include <intrin.h>

// Fonction de recup des infos systemes

void GetSysInf()
{
    // Récupérer le nom de le hostname 

    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);
    if (GetComputerNameA(computerName, &size))
    {
        printf("Nom de la machine : %s\n", computerName);
    }
    else
    {
        printf("Impossible de récupérer le nom de la machine\n");
    }

    // Récupérer les spécifications du CPU
    
    int cpuInfo[4] = { 0 };
    char cpuBrandString[0x40];
    __cpuid(cpuInfo, 0x80000000);
    unsigned int nExIds = cpuInfo[0];
    memset(cpuBrandString, 0, sizeof(cpuBrandString));
    for (unsigned int i = 0x80000000; i <= nExIds; ++i)
    {
        __cpuid(cpuInfo, i);
        if (i == 0x80000002)
        {
            memcpy(cpuBrandString, cpuInfo, sizeof(cpuInfo));
        }
        else if (i == 0x80000003)
        {
            memcpy(cpuBrandString + 16, cpuInfo, sizeof(cpuInfo));
        }
        else if (i == 0x80000004)
        {
            memcpy(cpuBrandString + 32, cpuInfo, sizeof(cpuInfo));
        }
    }
    printf("Spécifications du CPU : %s\n", cpuBrandString);

    // Récupére le nombre de RAM installer

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memInfo))
    {
        printf("Taille de la mémoire RAM installée : %llu Mo\n", memInfo.ullTotalPhys / (1024 * 1024));
    }
    else
    {
        printf("Impossible de récupérer la taille de la mémoire RAM\n");
    }

    // Récupérer le nom de session actuel

    char userName[UNLEN + 1];
    size = sizeof(userName);
    if (GetUserNameA(userName, &size))
    {
        printf("Nom d'utilisateur : %s\n", userName);
    }
    else
    {
        printf("Impossible de récupérer le nom d'utilisateur\n");
    }

    // Récupérer le pays/localisation

    char country[10];
    int result = GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SISO3166CTRYNAME, country, sizeof(country));
    if (result > 0)
    {
        printf("Pays : %s\n", country);
    }
    else
    {
        printf("Impossible de récupérer le pays\n");
    }
}

