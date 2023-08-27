#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <plotter.h>

#define H1() printf("%s", "\033[1;30;107m")
#define TEXT() printf("%s", "\033[1;37m")
#define TEXT_GRAB() printf("%s", "\033[1;102m")
#define TEXT_RELEASE() printf("%s", "\033[1;101m")
#define RESET() printf("%s", "\033[0m")

int _count_level(char *str, char *element){
  int level;
  for (level = 0; str[level]; str[level]=='/' ? level++ : *str++);
  return level;
}

void _draw(Trap *trap){

  for (int i = 0; i < trap->n_items; i++){
   
    char *item = trap->content[i];
    int level = _count_level(item, "/");

    H1();
    printf("[%d]", i);
    
    for(int j = 0; j < level; j++){
      printf(" ");
    }
    
    RESET();
    printf("  ");
    TEXT();
    printf("%s", trap->content[i]);
    printf("\n");
    RESET();
  }

  clean();
}

void _draw_header(char *text, char op) {
  struct winsize w;
  int i, width, len;

  ioctl(0, TIOCGWINSZ, &w);
  width = w.ws_col;
  len = strlen(text);

  clean();

  for (i = 0; i < (width - len); i++){
    printf(" ");
  }

  if (op == 'g') {
    TEXT_GRAB();
  } else if (op == 'r') {
    TEXT_RELEASE();
  } else {
    TEXT();
  }

  printf("%s\n", text);
  RESET();
}

void draw_grab(Trap *trap){
  char *text = "  Grab < ";
  _draw_header(text, 'g');
  _draw(trap);
}

void draw_release(Trap *trap){
  char *text = "  Release x ";
  _draw_header(text, 'r');
  _draw(trap);
}

void clean() {
  RESET();
  system("/usr/bin/stty sane");
}
