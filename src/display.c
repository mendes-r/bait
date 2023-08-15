#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <display.h>
#include <ascii_codes.h>

#define ASCII_OFFSET 48
#define DELIMETER "\n"

void init_menu(Menu *m, FILE *file){
  int max_size, i = 0;
  long size;
  char *item; 
  char *env;

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer= (char *) malloc(size);
  fgets(buffer, size, file);

  env = getenv("BAIT_LIST_SIZE");
  max_size = (int) *env - ASCII_OFFSET;

  // check if list in file is bigger than allowed size
  max_size = max_size > MAX_SIZE? MAX_SIZE: max_size;
  
  for (item = strtok(buffer, "\n"); (item != NULL && i < max_size); item = strtok(NULL, "\n")){
    m->content[i] = item;
    i++;
  }
  m->n_items = i; 
  // TODO Because cannot persist the first token
  m->content[0] = realloc(buffer, strlen(buffer));
}

void destroy_menu(Menu *m){
  // TODO
  free(m->content[0]);
}

void _init_draw(){
  printf("%s", FG_RED_N);
}

void _reset_draw(){
  printf("%s", A_RESET);
}

void draw(Menu *m){
  _init_draw();

  for (int i = 0; i < m->n_items; i++){
    printf("[%d] %s\n", i, m->content[i]);
  }

  _reset_draw();
}

