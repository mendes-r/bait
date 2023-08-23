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
#define LOWER_Q 65 // 113 ascii - 48 offset

// src: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
#define SAVE_CURSOR_POS() printf("%s", "\0337");
#define RESTORE_CURSOR_POS() printf("%s", "\0338");
#define ERASE_BELOW() printf("%s", "\033[0J");

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
  int input, i;

  import_content(&trap);

  SAVE_CURSOR_POS();
  draw_release(&trap);

  do {
    input = get_input();

    for (i = 0; i < trap.n_items; i++){
      if (input == i) {
        rm_content(&trap, i);
        export_content(&trap);
        found = 1;
        break;
      }
    }
  } while (input != LOWER_Q && !found);

  RESTORE_CURSOR_POS();
  ERASE_BELOW();
}

void grab(void){
  Trap trap;
  int input, i;
  char *dir;
  short found = 0;

  import_content(&trap);

  SAVE_CURSOR_POS();
  draw_grab(&trap);
  
  do {
    input = get_input();
    
    for (i = 0; i < trap.n_items; i++){
      if (input == i) {
        dir = trap.content[i];
        found = 1;
        break;
      }
    } 
  } while (input != LOWER_Q && !found);
  
  RESTORE_CURSOR_POS();
  ERASE_BELOW();

  if (found) 
    fprintf(stderr, "cd %s\n", dir);
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
