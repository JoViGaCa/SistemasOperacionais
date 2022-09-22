#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>

#define SIZE 1024

int main(int argc, char * argv[]){
  key_t key;
  int shmid;
  char *data;

  //criar chave
  key = ftok("/tmp", 'A');
  //crair id
  shmid = shmget(key, SIZE, 0644| IPC_CREAT);

  //Vincular os processos
  data = (char*) shmat(shmid, (void*)0, 0);

  if(argc == 2){
    printf("Escrevendo no segmento: %s\n\n", argv[1]);
    strcpy(data,argv[1]);
  } else {
    printf("O segmento contém: %s \n\n", data);
  }
  if(argc > 1 && !strcmp(argv[1], "apagar")){
    //desvincular data
    shmdt(data);
    //destruir
    shmctl(shmid, IPC_RMID, NULL);
    printf("Deletando o segmento\n\n");
  }

  return 0;
}
