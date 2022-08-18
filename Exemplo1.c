#include <unistd.h> //interface posix
#include <string.h>
#include <stdlib.h>
//#include <alarm.h>
//#include <signals.h>


int main(){

  char *str = (char*) (malloc(20*sizeof(char)));
  strcpy(str,"Hello World!\n");

  int inteiro;
  //itoa(inteiro, str, 10);
  read (0, &inteiro, sizeof(int));

  write(1, str, 13);

  write(1, &inteiro, sizeof(int));

  return 0;
}
