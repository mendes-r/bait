#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <plotter.h>

#define H1() printf("%s", "\033[1;30;107m")
#define TEXT() printf("%s", "\033[1;37m")
#define RESET() printf("%s", "\033[0m")

void draw(Trap *trap){

  for (int i = 0; i < trap->n_items; i++){
    H1();
      printf("   [%d]", i);
    RESET();
      printf(" - ");
    TEXT();
      printf("%s", trap->content[i]);
      printf("\n");
  }

  printf("\n");
  RESET();
}

