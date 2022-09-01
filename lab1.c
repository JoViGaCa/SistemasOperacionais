#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(){
  pid_t pid;
  int status;
  int* dado = (int*) malloc(sizeof(int));
  pid = fork();
  FILE* arq = fopen("teste.txt","w+");
  if (pid < 0){
    printf("Deu ruim\n\n");
    exit(-1);
  }
  if (pid == 0){
    printf("Processo filho, pid = %d\n", getpid());
    printf("Digite um número:\n");
    *dado = 355;
    // pause();
    fprintf(arq, "%d", *dado);
    printf("Dado do filho: %d\n", *dado);
    exit(0);
  } else {
    wait(&status);
    rewind(arq);
    fscanf(arq,"%d", dado);
    printf("O número digitado foi: %d\n", *dado);

    exit(0);
  }



  return 0;
}
