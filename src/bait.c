#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 100
#define CONFIG_FILE "/.bait.conf"

void help_page(void);
void catch(void);
void release(void);
void grab(void);
void display(void);
const char *get_config_dir(void);

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
  const char *config_dir;
  char curr_dir[BUFSIZE];
  FILE *file;

  config_dir = get_config_dir();

  printf("DEBUG: Complete directory is %s\n", config_dir);

  file = fopen(config_dir, "a");
  if (file == NULL){
    // TODO deal with no file
    fprintf(stderr, "File open error.\n");
    exit(1);
  }
  
  // TODO check first if already exist
  if(getcwd(curr_dir, sizeof(curr_dir)) == NULL){
    fprintf(stderr, "Error retrieving currrent dir.\n");
    exit(1);
  }

  fprintf(file, "%s\n", curr_dir);
  
  fclose(file);
}

const char *get_config_dir(void){
  const char *c_config_dir;
  char *config_dir;
  // TODO check the getenv result and size
  config_dir = getenv("HOME");
  // TODO use safer way to concat a string
  strcat(config_dir, CONFIG_FILE);
  c_config_dir = config_dir;
  return c_config_dir;
}

void release(void){
  display();
  // TODO one specific entry not all
}

void grab(void){
  display();
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

void display(void){
  // TODO window in the middle of the terminal screen
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
