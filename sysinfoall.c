#include "proto.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

const char* sysinfoall() {
   char* sysInfo = system("systeminfo");
    return sysInfo ;
}