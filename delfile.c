#include "proto.h"
#include <stdio.h>

const char *supfichier(char* filename) {

  // Supprime ce fichier
  if (remove(filename) != 0) {
  } else {
    return("Fichier supprime#\n");
  }

}