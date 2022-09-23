#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>


int main(int argc, char* argv[]){
  int pip[2];
  if ((pipe(pip)) < 0){
    printf("Erro na criação do pipe\n");
    exit(0);
  }

  FILE *arq_e = fopen(argv[1], "r");
  FILE *arq_s = fopen(argv[2], "w");

  pid_t pid;
  pid = fork();

  if(pid == 0){
    char buffer[200];
    read(pip[0], buffer, sizeof(buffer));
    fputs(buffer,arq_s);
    exit(0);
  } else {
    char buffer[200];
    fgets(buffer, sizeof(buffer), arq_e);
    write(pip[1], buffer, sizeof(buffer));
    exit(0);
  }
  return 0;
}
