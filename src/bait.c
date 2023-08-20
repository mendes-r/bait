#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>

#include <plotter.h>
#include <content.h>

#define BUFSIZE 500
#define ASCII_OFFSET 48

void help_page(void);
void catch(void);
void release(void);
void grab(void);
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
  Trap trap;
  char curr_dir[BUFSIZE];

  import_content(&trap);

  if (getcwd(curr_dir, sizeof(curr_dir)) == NULL){
    fprintf(stderr, "Error retrieving current dir.\n");
    exit(1);
  }

  add_content(&trap, curr_dir);
  export_content(&trap);
}

void release(void){
  Trap trap;
  short found = 0;

  import_content(&trap);
  draw(&trap);

  while (!found){
    int input;
    input = get_input();
    
    for (int i = 0; i < trap.n_items; i++){
      if (input == i) {
        rm_content(&trap, i);
        export_content(&trap);
        found = 1;
        break;
      }
    }
  }
}

void grab(void){
  Trap trap;
  short found = 0;

  import_content(&trap);
  draw(&trap);
  
  while (!found){
    int input;
    input = get_input();
    
    for (int i = 0; i < trap.n_items; i++){
      if (input == i) {
        printf("cd %s\n", trap.content[i]);
        found = 1;
        break;
      }
    }
  }
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
  
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

  return (c - ASCII_OFFSET);
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
