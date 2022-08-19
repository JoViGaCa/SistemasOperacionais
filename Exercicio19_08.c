#include <unistd.h> //interface posix
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

void dentroLoop(int signum){
   write(1, "Dentro de um loop\n", 18);
}

void saindo(int signum){
  write(1, "Saindo...\n", 10);
  exit(0);
}

int main(){
  while(true){
    signal(SIGALRM, dentroLoop);
    signal(SIGINT, saindo);
    alarm(5);
    pause();
  }

  return 0;
}
