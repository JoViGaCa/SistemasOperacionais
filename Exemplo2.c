#include <unistd.h> //interface posix
#include <string.h>
#include <stdlib.h>
//#include <alrm.h>
#include <signal.h>

void handler(int signum){

   write(1, "Sinal recebido\n", 15);

}


int main(){

  signal(SIGALRM, handler);

  alarm(5);

  pause();

  return 0;
}
