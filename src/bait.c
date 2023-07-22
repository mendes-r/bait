#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 100
#define CONFIG_FILE "/.bait.conf"

void help_page(void);
void catch(void);
void release(void);
void grab(void);

void bait(char *cmd){
  if (strcmp(cmd, "catch") == 0 || strcmp(cmd, "") == 0){
    printf("catch\n");
    catch();
  } else if (strcmp(cmd, "release") == 0 || strcmp(cmd, "-r") == 0){
    printf("release\n");
    release();
  } else if (strcmp(cmd, "grab") == 0 || strcmp(cmd, "-g") == 0) {
    printf("grab\n");
    grab();
  } else {
    help_page();
  }
}

void catch(void){
  char *home_dir;
  FILE *file;

  // check the getenv result and size
  home_dir = getenv("HOME");
  // use safer way to concat a string
  strcat(home_dir, CONFIG_FILE);

  printf("DEBUG: Complete directory is %s\n", home_dir);

  file = fopen(home_dir, "a");
  if (file == NULL){
    // deal with no file
    fprintf(stderr, "File open error.\n");
  }

  fprintf(file, "%s\n", home_dir);
  
  fclose(file);
}

void release(void){}

void grab(void){}

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

  if (strlen(cmd) > BUFSIZE) {
    cmd = "help";
  }
  
  bait(cmd);
  return EXIT_SUCCESS;
}
