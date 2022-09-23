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
   FILE *arq = fopen("id.txt", "r");
   fscanf(arq, "%d", &shmid);
   //crair id
   shmid = shmget(key, SIZE, 0644);

   //Vincular os processos
   data = (char*) shmat(shmid, (void*)0, 0);

   char buffer[20];
   strcpy(buffer, data);
   printf("%s\n", buffer);

   return 0;
}
