#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

#define SHM_SIZE 1024


const int REP = 5;
char dado;
key_t key;
int shmid,flagsid;
char *data;
int  *flags;
pthread_mutex_t mut;
sem_t sem;

int consumer(int n)
{

    printf("Consumer was born!\n");


    char produce;
    int out = 0;
    for(int i = 0; i < REP; i++) {


    while(1){
      pthread_mutex_lock(&mut);
      // sem_wait(&sem);
      while(flags[3] == 0);
      // flags[1] = 1;
      // while(flags[0] && (flags[2] == 0));

      produce = data[out];
      out++;
      if(out == 10){
        out = 0;
      }
      printf("Consumindo %c\n", produce);
      flags[3]--;
      // sem_post(&sem);


      // flags[2] = 0;
      //
      // flags[1] = 0;
      pthread_mutex_unlock(&mut);

    }


    }

    return n;
}

int main()
{
    printf("The Producer x Consumer Problem\n");
    int status;

    key = ftok("/home", 'A');                      //  Segmento
    shmid = shmget(key, 1024, 0644 | IPC_CREAT);   //
    data = (malloc(5*sizeof(char)));               //     1
    data = shmat(shmid, (void *)0, 0);             //

    //Peterson
    key = ftok("/home/downloads", 'B');            //  Segmento
    flagsid = shmget(key, 1024, 0644 | IPC_CREAT); //
    flags = (malloc(4*sizeof(int)));               //     2
    flags = shmat(flagsid, (void *)0, 0);          //

    flags[0] = 1;
    flags[1] = 0;
    flags[2] = 0;
    flags[3] = 0;

    sem_init(&sem, 1, 1);
    consumer(5);


    return 0;

}
