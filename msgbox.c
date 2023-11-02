#include "proto.h"
#include <windows.h>

const char *afficherMessageBox(const char *titre, const char *texte, int numeroType) {
    UINT typeMessage = 0;

// Touts les types de messages box disponibles.

    switch (numeroType) {
        case 1:
            typeMessage = MB_OK;
            break;
        case 2:
            typeMessage = MB_YESNO;
            break;
        case 3:
            typeMessage = MB_OKCANCEL;
            break;
        case 4:
            typeMessage = MB_ABORTRETRYIGNORE;
            break;
        case 5:
            typeMessage = MB_RETRYCANCEL;
            break;
        case 6:
            typeMessage = MB_YESNOCANCEL;
            break;
        case 7:
            typeMessage = MB_ICONINFORMATION;
            break;
        case 8:
            typeMessage = MB_ICONWARNING;
            break;
        case 9:
            typeMessage = MB_ICONERROR;
            break;
        // Ajoutez d'autres cas pour d'autres types de MessageBox si nécessaire

        default:
            typeMessage = MB_OK; // Par défaut, affiche une MessageBox avec un seul bouton "OK"
            break;
    }

    MessageBox(NULL, texte, titre, typeMessage);
    return ("La victime a bien recu le message... #");
}
