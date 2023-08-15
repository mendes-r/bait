#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>

#include <display.h>

#define BUFSIZE 100

void help_page(void);
void catch(void);
void release(void);
void grab(void);
FILE *get_data(const char * restrict mode);
int get_input();

char *cmd;

void bait(){
  if (strcmp(cmd, "catch") == 0 || strcmp(cmd, "") == 0){
    catch();
  } else if (strcmp(cmd, "release") == 0 || strcmp(cmd, "-r") == 0){
    release();
  } else if (strcmp(cmd, "grab") == 0 || strcmp(cmd, "-g") == 0){
    grab();
  } else{
    help_page();
  }
}

void catch(void){
  char curr_dir[BUFSIZE];
  FILE *file;

  file = get_data("a");

  // TODO check first if already exist
  if (getcwd(curr_dir, sizeof(curr_dir)) == NULL){
    fprintf(stderr, "Error retrieving current dir.\n");
    exit(1);
  }
  printf("DEBUG: %s\n", curr_dir);
  fprintf(file, "%s\n", curr_dir);
  fclose(file);
}

void release(void){
  FILE *file;
  Menu menu;
  short found = 0;

  file = get_data("r");

  init_menu(&menu, file);
  draw(&menu);
  
  while (!found){
    int input;
    input = get_input();
    
    if (input < menu.n_items){
      // TODO remove string from file
      // TODO implement linked list instead of array
      found = 1;
      break;
    }
    
  }

  destroy_menu(&menu);
  fclose(file);
}

void grab(void){
  FILE *file;
  Menu menu;
  short found = 0;

  file = get_data("r");

  init_menu(&menu, file);
  draw(&menu);
  
  while (!found){
    int input;
    input = get_input();
    
    for (int i = 0; i < menu.n_items; i++){
      if (input == i) {
        printf("cd %s\n", menu.content[i]);
        found = 1;
        break;
      }
    }
    
  }

  destroy_menu(&menu);
  fclose(file);
}

int get_input(){
  // src: https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar-for-reading-a-single-character-only
  int c;
  static struct termios oldattr, newattr;

  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

  c=getchar();
  
  //TODO This command needs to always run, even after a KILL SIGN
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

  // ANSII offset
  return (c - 48);
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
