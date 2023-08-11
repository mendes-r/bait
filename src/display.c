#include <stdio.h>
#include <string.h>

#include <display.h>
#include <ascii_codes.h>

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

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
  m->content_size=0;
}

void _init_draw(){
  printf("%s", FG_RED_N);
}

void _reset_draw(){
  printf("%s", A_RESET);
}

void draw(Menu *m){
  char *line;
  int index = 0;
  char tmp[m->content_size];
  
  strcpy(tmp, m->content);
  
  clear();
  _init_draw();

  line = strtok(tmp, ",");
  while (line != NULL){
    if(m->select == index) {
      printf("[%s]\n", line);
    } else {
      printf("%s\n", line);
    }
    index++;
    line = strtok(NULL, ",");
  }

  _reset_draw();
}

