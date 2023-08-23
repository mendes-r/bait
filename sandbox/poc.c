#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main(void){
  char *input;
  pid_t pid;

  pid = fork();

  if (pid == 0) {
    // stderr will alway print even inside the eval command
    fprintf(stderr, "Starting test: ");
    scanf("%s", input);
    exit(0);
  } else {
    int returnStatus;
    waitpid(pid, &returnStatus, 0);
    // stdout is the real input to the eval command
    fprintf(stdout, "cd /home/visceroii/Developer/");
  }

}
