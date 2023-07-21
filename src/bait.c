#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG "Debug: "
#define BUFSIZE 10

void help_page(void);
void catch(void);
void release(void);
void grab(void);

void bait(char *cmd){
  printf("%s%s\n", DEBUG, cmd);

  if (strcmp(cmd, "catch") == 0 || strcmp(cmd, "") == 0){
    catch();
    printf("catch\n");
  } else if (strcmp(cmd, "release") == 0 || strcmp(cmd, "-r") == 0){
    release();
    printf("release\n");
  } else if (strcmp(cmd, "grab") == 0 || strcmp(cmd, "-g") == 0) {
    grab();
    printf("grab\n");
  } else {
    help_page();
  }

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
  char *cmd = ""; 

  if (argc > 1) {
    cmd = argv[1];
  }

  printf("%s%s\n", DEBUG, cmd);

  if (strlen(cmd) > BUFSIZE) {
    cmd = "help";
  }
 
  bait(cmd);
  return EXIT_SUCCESS;
}
