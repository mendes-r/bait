#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <display.h>

#define BUFSIZE 100

void help_page(void);
void catch(void);
void release(void);
void grab(void);
void display(void);
FILE *get_config(void);

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
  char curr_dir[BUFSIZE];
  FILE *file;

  file = get_config();

  // TODO check first if already exist
  if(getcwd(curr_dir, sizeof(curr_dir)) == NULL){
    fprintf(stderr, "Error retrieving currrent dir.\n");
    exit(1);
  }

  fprintf(file, "%s\n", curr_dir);
  fclose(file);
}

FILE *get_config(void){
  FILE *file;
  char *config_dir;
  const char *config_name = "/.baitrc";

  // TODO check the getenv result and size
  config_dir = getenv("HOME");
 
  // TODO use safer way to concat a string
  strcat(config_dir, config_name);

  printf("DEBUG: Complete directory is %s\n", config_dir);

  file = fopen(config_dir, "a");
  if (file == NULL){
    // TODO deal with no file
    fprintf(stderr, "File open error.\n");
    exit(1);
  }

  return file;
}

void release(void){
  // TODO one specific entry not all
}

void grab(void){
  draw();
  // TODO grab one entry
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

  if (strlen(cmd) > BUFSIZE) {
    cmd = "help";
  }
  
  bait(cmd);
  return EXIT_SUCCESS;
}
