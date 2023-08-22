#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <plotter.h>

#define H1() printf("%s", "\033[1;30;107m")
#define TEXT() printf("%s", "\033[1;37m")
#define TEXT_GRAB() printf("%s", "\033[1;32m")
#define TEXT_RELEASE() printf("%s", "\033[1;31m")
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

}

void draw_grab(Trap *trap){
  TEXT_GRAB();
  printf("Grab:\n");
  RESET();

  _draw(trap);

}

void draw_release(Trap *trap){
  TEXT_RELEASE();
  printf("Release:\n");
  RESET();

  _draw(trap);
}
