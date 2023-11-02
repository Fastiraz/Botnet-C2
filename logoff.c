#include "proto.h"
#include <stdlib.h>
#include <stdio.h>

const char *logoff(){
system("shutdown -l");
return ("Utilisateur deconnecte...#");
}
