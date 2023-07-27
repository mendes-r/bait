#include <stdio.h>
#include <string.h>

#include <display.h>
#include <ascii_codes.h>

void init_menu(Menu *m){
  m->row=1;
  m->col=1;
  m->pad[0]=0;
  m->pad[1]=0;
  m->pad[2]=0;
  m->pad[3]=0;
  m->marg[0]=0;
  m->marg[1]=0;
  m->marg[2]=0;
  m->marg[3]=0;
  m->select=0;
  m->content="";
}

void _init_draw(){
  printf("%s", FG_RED_N);
}

void _reset_draw(){
  printf("%s", A_RESET);
}

void draw(Menu *m){
  char *line;

  _init_draw();

  line = strtok(m->content, "\r\n");
  while (line != NULL){
    printf("%s\n", line);
    line = strtok(NULL, "\r\n");
  }

  _reset_draw();
}

