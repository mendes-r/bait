#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <plotter.h>
#include <content.h>
#include <ascii_codes.h>

void init_menu(Menu *m){
  // TODO alloc memory for content?
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

