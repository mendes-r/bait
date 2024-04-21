#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <content.h>

#define HOME "HOME"
#define BAIT_RC "/.bait.list"
#define BUFSIZE 500
#define EMPTY ""


#ifdef DEBUG
#define DEBUGGER(x) printf ("DEBUG\t\t %s\n", x)
#else
#define DEBUGGER(x) do {} while (0)
#endif

FILE *_open_file(char *mode){
  FILE * file;
  char config_dir[BUFSIZE];

  strcpy(config_dir, getenv(HOME));
  strcat(config_dir, BAIT_RC);

  file = fopen(config_dir, mode);
  if (file == NULL){
    fprintf(stderr, "Error opening file in home directory.\n");
  }

  return file;
}

int add_content(Trap *trap, char *item){
  if (trap->n_items > SIZE_LIMIT){
    fprintf(stderr, "The number of items was exceeded.");
    return -1;
  }
  trap->content[trap->n_items] = item;
  trap->n_items = (trap->n_items + 1);
  return 0;
}

int rm_content(Trap *trap, int index){
  FILE *file;

  file = _open_file("w");
  if (file == NULL) {
    return -1;
  }
  
  trap->content[index] = EMPTY;

  fclose(file);
  return 0;
}

int import_content(Trap *trap){
  FILE *file;
  int index = 0;
  // TODO define max length
  char line[256];
  
  file = _open_file("r"); 
  if (file == NULL) {
    return -1;
  }

  DEBUGGER("Reading file ...");
  DEBUGGER("<<<<<");

  while (fgets(line, sizeof(line), file)) {
    // TODO define max length
    char *item = (char *) malloc(256);
    strncpy(item, line, strlen(line)-1);
    trap->content[index] = item;
    DEBUGGER(trap->content[index]);
    index++;
  }

  trap->n_items = index;

  fclose(file);
  return 0;
}

int export_content(Trap *trap){
  FILE *file;

  file = _open_file("w");
  if (file == NULL) {
    return -1;
  }

  DEBUGGER("Exporting file ...");
  DEBUGGER(">>>>>");
  
  for(int i = 0; i < trap->n_items; i++){
    char *item = trap->content[i];
    if (strcmp(item, EMPTY) != 0){
      DEBUGGER(item);
      fprintf(file, "%s\n", item);
    }
  }

  // TODO confirm that file was closed
  fclose(file);
  return 0;
}
