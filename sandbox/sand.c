#include <stdio.h>
#include <stdlib.h>

void main(void){
  fprintf(stdin, "echo IN\n");
  fprintf(stdout, "echo OUT\n");
  fprintf(stderr, "echo ERROR\n");
}
