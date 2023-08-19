#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ascii_codes.h>

void _init_draw(){
  printf("%s", FG_RED_N);
}

void _reset_draw(){
  printf("%s", A_RESET);
}

void draw(Trap *trap){
  _init_draw();

  for (int i = 0; i < trap->n_items; i++){
    printf("[%d] %s\n", i, trap->content[i]);
  }

  _reset_draw();
}

