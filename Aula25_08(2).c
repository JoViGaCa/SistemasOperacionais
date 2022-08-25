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
  } else {
    if(pid == 0){
      printf("Processo filho, pid = %d\n", getpid());
      execl("/home/alunos/a2270340/jooj", "-l", NULL);
    } else {
      wait(&status);
      printf("Processo pai, pid = %d\n", getpid());
      printf("%d\n", status);
    }
  }

  return 0;
}
