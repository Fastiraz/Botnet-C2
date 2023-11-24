#include "proto.h"
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdbool.h>

void closeProcesses(const char* processName) {
    const char* processes[] = {"ProcMon.exe", "ProcessHacker.exe", "ida.exe", "cheatengine.exe", "wireshark.exe", "autopsy.exe"};

    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    bool processFound = false;

    for (int i = 0; i < sizeof(processes) / sizeof(processes[0]); ++i) {
        if (strcmp(processes[i], processName) == 0) {
            processFound = true;
            break;
        }
    }

    if (!processFound) {
        printf("%s n'est pas dans la liste des processus à fermer.\n", processName);
        Sleep(3000); // Attendre 3 secondes avant de vérifier à nouveau
        return;
    }

    while (1) {
        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (hProcessSnap == INVALID_HANDLE_VALUE) {
            printf("Valeur handle invalide.\n");
            Sleep(3000); // Attendre 3 secondes avant de vérifier à nouveau
            continue;
        }

        pe32.dwSize = sizeof(PROCESSENTRY32);

        if (!Process32First(hProcessSnap, &pe32)) {
            printf("Erreur de récupération du premier processus.\n");
            CloseHandle(hProcessSnap);
            Sleep(3000); // Attendre 3 secondes avant de vérifier à nouveau
            continue;
        }

        do {
            if (strcmp(pe32.szExeFile, processName) == 0) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);

                if (hProcess != NULL) {
                    TerminateProcess(hProcess, 0);
                    CloseHandle(hProcess);
                    printf("%s a été fermé.\n", processName);
                    CloseHandle(hProcessSnap);
                    Sleep(3000); // Attendre 3 secondes avant de vérifier à nouveau
                    return;
                }
            }
        } while (Process32Next(hProcessSnap, &pe32));

        CloseHandle(hProcessSnap);
        printf("%s n'est pas en cours d'exécution.\n", processName);
        Sleep(3000); // Attendre 3 secondes avant de vérifier à nouveau
    }
}

