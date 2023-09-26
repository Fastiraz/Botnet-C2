#include "proto.h"
#include <winsock2.h>
#include <stdio.h>

int hardcollec()
{
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);
	SOCKET sock;
	SOCKADDR_IN sin;
	sin.sin_addr.s_addr    = inet_addr("192.168.1.132");
	sin.sin_family        = AF_INET;
	sin.sin_port        = htons(1054);
	//printf(getenv("set"));
	SYSTEM_INFO siSysInfo;
   // Copie de info hardware dans la strcture SYSTEM_INFO. 
   GetSystemInfo(&siSysInfo); 
   // Affiche le contenue de la strcture system info. 

	char nbproc[128];
	char proctype[128];
	char oemid[128];

	send(sock, nbproc, sizeof(nbproc), 0);
	send(sock, proctype, sizeof(proctype), 0);
   	send(sock, oemid, sizeof(oemid), 0);
    closesocket(sock);
    WSACleanup();
}
