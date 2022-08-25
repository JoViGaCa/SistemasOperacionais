#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  pid_t pid;
  pid = fork();
  if(pid < 0){
    printf("Deu ruim\n");
  } else {
    if(pid == 0){
      printf("Processo filho\n");
    } else {
      printf("Processo pai\n");
    }
  }
  return 0;
}
