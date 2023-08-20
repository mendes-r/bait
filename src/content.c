#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <content.h>

#define HOME "HOME"
#define BAIT_RC "/.baitrc"

int add_content(Trap *trap, char *item){
  if (trap->n_items > SIZE_LIMIT){
    perror("The number of items was exceeded.");
    return -1;
  }
  trap->content[trap->n_items] = item;
  trap->n_items = (trap->n_items + 1);
  return trap->n_items;
}

int rm_content(Trap *trap, int index){
  //TODO implement and if n_items is already 0
  trap->n_items = (trap->n_items - 1);
  return trap->n_items;
}

int import_content(Trap *trap){
  FILE *file;
  char *config_dir, *buffer, *item;
  long size;
  int index = 0;
  
  config_dir = getenv(HOME);
  if (config_dir == NULL){
    perror("Home directory not retrieved.\n");
    return -1;
  }
 
  strcat(config_dir, BAIT_RC);

  file = fopen(config_dir, "r");
  if (file == NULL){
    perror("Error opening file in home directory.\n");
    return -1;
  }

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);

  buffer= (char *) malloc(size);
  fgets(buffer, size, file);

  for (item = strtok(buffer, ","); (item != NULL && index < SIZE_LIMIT); item = strtok(NULL, ",")){
    trap->content[index] = item;
    index++;
  }

  // TODO Because cannot persist the first token
  trap->content[0] = realloc(buffer, strlen(buffer));

  return index;
}

int export_content(Trap *trap){
  // TODO
  return -1;
}
