#include "proto.h"
#include <stdlib.h>
#include <stdio.h>

const char *restart(){
system("shutdown -r -t 0");
return ("Reboot du pc en cours...#");
}