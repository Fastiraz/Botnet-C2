#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 1234

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[1024];
    char clientIP[INET_ADDRSTRLEN];

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

    int choice;
    do {
        // Affichage du menu
        printf("\n=== Menu ===\n");
        printf("1. Envoyer un message au client\n");
        printf("2. Lister les clients\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choice);
        getchar(); // Capture du retour à la ligne après le choix

        switch (choice) {
            case 1:
                // Saisie du message à envoyer
                printf("Entrez un message à envoyer au client : ");
                fgets(buffer, sizeof(buffer), stdin);

                // Envoi du message au client
                if (send(clientSocket, buffer, strlen(buffer), 0) == -1) {
                    perror("Erreur lors de l'envoi du message au client");
                } else {
                    printf("Message envoyé au client : %s\n", buffer);
                }
                break;

            case 2:
                // Affichage des informations sur le client
                printf("Client connecté depuis l'adresse IP : %s\n", clientIP);
                break;

            case 3:
                // Quitter le menu
                printf("Fermeture de la connexion...\n");
                break;

            default:
                printf("Choix invalide. Veuillez entrer 1, 2 ou 3.\n");
                break;
        }
    } while (choice != 3);

    // Fermeture des sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}

