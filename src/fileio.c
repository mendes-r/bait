#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HOME "HOME"
#define BAIT_RC "/.baitrc"

void add_content(char *item){
  //TODO
}

void rm_content(int i){
  //TODO
}

FILE *get_content(const char * restrict mode){
  FILE *file;
  char *config_dir;

  config_dir = getenv(HOME);
  if (config_dir == NULL){
    perror("Home directory not retrieved.\n");
    exit(1);
  }
 
  strcat(config_dir, BAIT_RC);

  file = fopen(config_dir, mode);
  if (file == NULL){
    perror("Error opening file in home directory.\n");
    exit(1);
  }

  return file;
}

