#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>


int main(){
  int pip[2];
  if ((pipe(pip)) < 0){
    printf("Erro na criação do pipe\n");
  }

  pid_t pid;
  pid = fork();
  int status;

  if(pid == 0){

    write(pip[1], "Bora Bill \n", 12);
    exit(0);

  } else {

    wait(&status);
    char buffer[15];
    read(pip[0], buffer, sizeof(buffer));
    printf("Mensagem: %s\n", buffer);

  }

  return 0;
}
