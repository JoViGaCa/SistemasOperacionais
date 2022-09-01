#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

int imprima(char* str1, ...){

  va_list lista;
  int args = 10;
  char *str2;
  va_start(lista, args);

  for(int i = 0; i < strlen(str1); i++){
    if (str1[i] == '%'){
      str2 = va_arg(lista, char*);
      write(1, str2, strlen(str2));
      return 0;
    }
  }


  // Código para inteiro
  // for(int i = 0; i < strlen(str1); i++){
  //   if(str1[i] == '%'){
  //     printf("%d\n", i);
  //     str1[i] = va_arg(lista, int) + '0';
  //     for(int j = i+1; j < strlen(str1); j++){
  //       str1[j] = str1[j+1];
  //     }
  //   }
  // }

  va_end(lista);

  write(1, str1, strlen(str1));


  return 0;
}


int main(){

  char str[] = "Hello World!!\n\n";

  imprima("Hello World!!\n\n");

  imprima("%s", str);

  return 0;
}
