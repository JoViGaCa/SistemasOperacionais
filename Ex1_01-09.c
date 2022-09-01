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
      wait(&status);
      printf("Eu sou o processo %d, filho de %d\n\n", getpid(), getppid());
      sleep(1);
      exit(0);
    } else {
      wait(&status);
      printf("Eu sou o processo %d, O Criador\n\n", getpid());
      exit(0);
    }
  }

  return 0;
}
