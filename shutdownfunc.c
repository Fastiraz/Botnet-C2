#include "proto.h"
#include <stdlib.h>
#include <stdio.h>

const char *shutdownfunc() {
system("shutdown -s -t 0");
return ("Exctinction de la machine...#");
}