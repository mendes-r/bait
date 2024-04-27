#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <plotter.h>
#include <content.h>

#define CMD_SIZE 10
#define BUFF_SIZE 500
#define ASCII_OFFSET 48
#define LOWER_Q 65 // 113 ascii - 48 offset

// src: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
#define MOV_CURSOR_UP(x) printf("\033[%sA", x)
#define ERASE_BELOW() printf("%s", "\033[0J")
#define RESET() printf("%s", "\033[0m")

#ifdef DEBUG
#define DEBUGGER(x) printf ("DEBUG\t\t %s\n", x)
#else
#define DEBUGGER(x) do {} while (0)
#endif

void help_page(void);
void catch(void);
void release(void);
void grab(void);
int get_input();
int starts_with(char *, char*);
void bait(char *cmd){
  if (strcmp(cmd, "--catch") == 0 || strcmp(cmd, "c") == 0){
    DEBUGGER("Catch init ...");
    catch();
  } else if (strcmp(cmd, "--release") == 0 || strcmp(cmd, "r") == 0){
    DEBUGGER("Release init ...");
    release();
  } else if (strcmp(cmd, "--grab") == 0 || starts_with("g", cmd) || strcmp(cmd, "g") == 0){
    DEBUGGER("Grab init ...");
    grab();
  } else{
    DEBUGGER("Help init ...");
    help_page();
  }
}

void catch(void){
  Trap trap;
  char curr_dir[BUFF_SIZE];

  import_content(&trap);

  if (getcwd(curr_dir, sizeof(curr_dir)) == NULL){
    fprintf(stderr, "Error retrieving current dir.\n");
    exit(1);
  }

  DEBUGGER("... current directory:");
  DEBUGGER(curr_dir);
  
  if (trap.n_items >= SIZE_LIMIT) {
    fprintf(stdout, "Limit reached. Release a entry.\n");
    exit(0);
  }

  add_content(&trap, curr_dir);
  export_content(&trap);
}

void release(void){
  Trap trap;
  short found = 0;
  int input, i;

  import_content(&trap);
  draw_release(&trap);

  do {
    input = get_input();

    for (i = 0; i < trap.n_items; i++){
      if (input == i) {
        rm_content(&trap, i);
        export_content(&trap);
        found = 1;

#ifdef DEBUG
        char index[15];
        sprintf(index, "%d", i);
        DEBUGGER("... remove index:");
        DEBUGGER(index);
#endif

        break;
      }
    }
  } while (input != LOWER_Q && !found);

  char rows[3];
  sprintf(rows, "%d", (trap.n_items + 1));

  DEBUGGER("... rows erased:");
  DEBUGGER(rows);

#ifndef DEBUG
  MOV_CURSOR_UP(rows);
  ERASE_BELOW();
#endif
}

void grab(void){
  Trap trap;
  int input, i;
  char *dir;
  short found = 0;

  import_content(&trap);
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
  
  char rows[3];
  sprintf(rows, "%d", (trap.n_items + 1));
  
#ifndef DEBUG
  MOV_CURSOR_UP(rows);
  ERASE_BELOW();
#endif

  if (found) {
    DEBUGGER("... grab directory:");
    DEBUGGER(dir);
    fprintf(stderr, "cd %s\n", dir);
  }
}

int starts_with(char *pre, char *str){
    return strncmp(pre, str, strlen(pre)) == 0;
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
  printf("\t--help | h\n");
  printf("\t--catch | c\n");
  printf("\t--release | r\n");
  printf("\t--grab | g\n");
  printf("\t... press 'q' to exit\n");
  printf("\n");
}

void sig_handler(int sign) {
  Trap trap;
  import_content(&trap);

  char rows[3];
  sprintf(rows, "%d", (trap.n_items + 1));

  MOV_CURSOR_UP(rows);
  ERASE_BELOW();
  clean();
  exit(2);
}

int main(int argc, char *argv[]){
  char *cmd = (char *) malloc(CMD_SIZE); 

  // hand ctrl + c
  signal(SIGINT, sig_handler);

  // update view when terminal is resized
  // signal(SIGWINCH, bait);

  if (strlen(argv[1]) > CMD_SIZE || argc < 1) {
    cmd = "help";
  } else {
    cmd = argv[1];
    // TODO if g3 retrieve the 3
  }
  
  bait(cmd);
  return EXIT_SUCCESS;
}
