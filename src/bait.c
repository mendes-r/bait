#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <display.h>

#define BUFSIZE 100

void help_page(void);
void catch(void);
void release(void);
void grab(void);
void display(void);
FILE *get_data(const char * restrict mode);

char *cmd;

void bait(){
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

  file = get_data("a");

  // TODO check first if already exist
  if(getcwd(curr_dir, sizeof(curr_dir)) == NULL){
    fprintf(stderr, "Error retrieving currrent dir.\n");
    exit(1);
  }

  fprintf(file, "%s\n", curr_dir);
  fclose(file);
}

void release(void){
  // TODO one specific entry not all
}

void grab(void){
  // TODO grab one entry
  
  FILE *file;
  Frame frame;
  long file_size;
  char *buffer;

  file = get_data("r");

  // get file content
  fseek(file, 0L, SEEK_END);
  file_size = ftell(file);
  rewind(file);

  buffer = calloc(1, file_size+1);
  if (!buffer) {
    fclose(file); 
    fprintf(stderr, "Error allocating memory.\n"); 
    exit(1);
  }

  if(1 != fread(buffer, file_size, 1, file)) {
    fclose(file); 
    free(buffer); 
    fprintf(stderr, "Error retrieving file content.\n");
    exit(1);
  }

  init_frame(&frame);
  frame.content = buffer;
  draw(&frame);

  fclose(file);
  free(buffer);
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

FILE *get_data(const char * restrict mode){
  FILE *file;
  char *config_dir;
  const char *config_name = "/.baitrc";

  // TODO check the getenv result and size
  config_dir = getenv("HOME");
 
  // TODO use safer way to concat a string
  strcat(config_dir, config_name);

  printf("DEBUG: Complete directory is %s\n", config_dir);

  file = fopen(config_dir, mode);
  if (file == NULL){
    // TODO deal with no file
    fprintf(stderr, "File open error.\n");
    exit(1);
  }

  return file;
}

int main(int argc, char *argv[]){
  cmd = ""; 

  if (argc > 1) {
    cmd = argv[1];
  }

  if (strlen(cmd) > BUFSIZE) {
    cmd = "help";
  }

  // update view when terminal is resized
  signal(SIGWINCH, bait);
  bait();

  return EXIT_SUCCESS;
}
