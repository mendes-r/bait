#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HOME "HOME"
#define BAIT_RC "/.baitrc"

void add_content(char *content[], int n_items, char *item){
  //TODO
}

void rm_content(char *content[], int i){
  //TODO
}

int import_content(char *content[], int max_size){
  FILE *file;
  char *config_dir, *buffer, *item;
  long size;
  int i = 0;
  
  config_dir = getenv(HOME);
  if (config_dir == NULL){
    perror("Home directory not retrieved.\n");
    exit(1);
  }
 
  strcat(config_dir, BAIT_RC);

  file = fopen(config_dir, "r");
  if (file == NULL){
    perror("Error opening file in home directory.\n");
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);

  buffer= (char *) malloc(size);
  fgets(buffer, size, file);

  for (item = strtok(buffer, ","); (item != NULL && i < max_size); item = strtok(NULL, ",")){
    content[i] = item;
    i++;
  }

  // TODO Because cannot persist the first token
  content[0] = realloc(buffer, strlen(buffer));

  return i;
}

void export_content(char *content[], int n_items){
  // TODO
}
