#include "proto.h"
#include <stdlib.h>
#include <stdio.h>

const char *lock(){
system("rundll32.exe user32.dll,LockWorkStation");
printf("DLL INVOKE");
return ("Session verouille...");
}

