#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(){
  pid_t pid;
  int status;
  pid = fork();
  if(pid < 0){
    printf("Deu ruim\n");
    exit(-1);
  } else {
    if(pid == 0){
      pid = fork();
      if(pid == 0){
        pid = fork();
        if(pid == 0){
          pid = fork();
          if(pid == 0){
            exit(5);
          }
          wait(&status);
          exit(4*WEXITSTATUS(status));
        }
        wait(&status);
        exit(3*WEXITSTATUS(status));
      }
      wait(&status);
      exit(2*WEXITSTATUS(status));
    } else {
      wait(&status);
      printf("O resultado é %d\n", WEXITSTATUS(status)*1);
      exit(0);
    }
  }

  return 0;
}
