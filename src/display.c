#include <stdio.h>
#include <string.h>

#include <display.h>
#include <ascii_codes.h>

void init_menu(Menu *m){
  m->content = "";
  m->content_size = 0;
  m->nr_items = 0;
}

void _init_draw(){
  printf("%s", FG_RED_N);
}

void _reset_draw(){
  printf("%s", A_RESET);
}

void draw(Menu *m){
  char *line;
  char tmp[m->content_size];
  int index = 0;

  strcpy(tmp, m->content);
  
  _init_draw();

  line = strtok(tmp, ",");
  while (line != NULL){
    printf("[%d] %s\n", index, line);
    line = strtok(NULL, ",");
    index++;
  }
  
  m->nr_items = index;

  _reset_draw();
}

