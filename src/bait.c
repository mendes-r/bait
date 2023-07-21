#include <stdlib.h>
#include <stdio.h>

void bait(char *cmd){
  printf("%s", cmd);
}

void catch(void){

}

void release(void){

}

void grab(void){

}

void help_page(void){
  printf("\n");
  printf("usage: bait [<command>]\n");
  printf("\n");
  printf("These are the commands used with 'bait':\n");

  printf("\n");
  printf("\thelp | -h\n");
  printf("\tcatch | <empty>\n");
  printf("\trelease | -r\n");
  printf("\tgrab | -g ... press 'q' to exit\n");
  printf("\n");
}

int main(int argc, char *argv[]){

  // skip program name
  --argc;
  ++argv;

  // no arguments or empty string
  if (argc < 1 || argv == 0) {
    help_page();
    exit(1);
  }
 
  bait(argv[0]);
  return EXIT_SUCCESS;
}
