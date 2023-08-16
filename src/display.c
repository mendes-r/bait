#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <display.h>
#include <ascii_codes.h>
#include <fileio.h>

#define ASCII_OFFSET 48

void init_menu(Menu *m){
  char *env = getenv("BAIT_LIST_SIZE");
  int max_size = (int) *env - ASCII_OFFSET;

  //Check if list in file is bigger than the limit
  max_size = max_size > SIZE_LIMIT? SIZE_LIMIT: max_size;
  
  m->n_items = get_content(m->content, max_size);
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

