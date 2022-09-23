#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>


int main(){
  int pip1[2];
  int pip2[2];
  int pip3[2];
  if ((pipe(pip1)) < 0){
    printf("Erro na criação do pipe\n");
  }
  if ((pipe(pip2)) < 0){
    printf("Erro na criação do pipe\n");
  }
  if ((pipe(pip3)) < 0){
    printf("Erro na criação do pipe\n");
  }

  pid_t pid;
  pid = fork();
  int status;

  if(pid == 0){

    pid = fork();

    if(pid == 0){

      pid = fork();

      if(pid == 0){
        // processo 4
        write(pip3[1],"Este é processo 4\n", 20);
        exit(0);

      } else {
        // processo 3
        wait(&status);
        char buffer[20];
        read(pip3[0], buffer, sizeof(buffer));
        write(1, "Mensagem recebida pelo processo 3\n", 35);
        write(pip2[1], buffer, sizeof(buffer));
        exit(0);
      }
    }else{
      //processo 2
      wait(&status);
      char buffer[20];
      read(pip2[0], buffer, sizeof(buffer));
      write(1, "Mensagem recebida pelo processo 2\n", 35);
      write(pip1[1], buffer, sizeof(buffer));
      exit(0);
    }
  } else {

    wait(&status);
    char buffer[20];
    read(pip1[0], buffer, sizeof(buffer));
    write(1, "Mensagem recebida pelo processo 1\n", 35);
    write(1, buffer, sizeof(buffer));
    exit(0);

  }

  return 0;
}
