#include <unistd.h> //interface posix
#include <string.h>
#include <stdlib.h>
//#include <alarm.h>
//#include <signals.h>


int main(){

  write(1, "Digite seu nome: \n", 18);
  char * nome = (char*) (malloc(20*sizeof(char)));
  read(0, nome, 20*sizeof(char));

  long int ra;
  write(1, "Digite seu RA: \n", 16);
  read(0, &ra, sizeof(long int));

  write(1, "Nome: ", 6);
  write(1, nome, 20);
  write(1, "RA: ", 5);
  write(1, &ra, sizeof(long int));



  return 0;
}
