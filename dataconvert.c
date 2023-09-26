#include <time.h>
#include <windows.h>
#include <stdio.h>
#include "proto.h"

int dateconvert( FILETIME * valeur)
{
	SYSTEMTIME stUTC, stLocal;

	// Convertie la date du denriere accés au fichier en temps local.
    FileTimeToSystemTime( valeur, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

    // Craft d'une string pour afficher la date.
    printf("[%02d/%02d/%d - %02d:%02d] ",
    stLocal.wDay ,stLocal.wMonth, stLocal.wYear,
    stLocal.wHour, stLocal.wMinute);

}