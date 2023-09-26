#include "proto.h"
#include <stdio.h>

void supfichier(char* filename) {

  // Supprime ce fichier
  if (remove(filename) != 0) {
  } else {
    printf("Fichier supprimé\n");
  }

}