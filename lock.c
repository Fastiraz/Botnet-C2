#include "proto.h"
#include <stdlib.h>
#include <stdio.h>

void lock(){
system("rundll32.exe user32.dll,LockWorkStation");
}

