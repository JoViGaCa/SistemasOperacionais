#include <mpi.h>
#include <stdio.h>
#define GERENTE 0


int main(int argc , char **argv){
  int i, id , size ,len , tag = 666;
  char *enviado,recebido[50];
  MPI_Status stats; // Status da mensagem recebida
  MPI_Init (&argc , &argv);
  MPI_Comm_rank(MPI_COMM_WORLD , &id);
  MPI_Comm_size(MPI_COMM_WORLD , &size); //size == número de processos

  if (id == GERENTE) {
    for (i = 1; i < size; ++i) {
      MPI_Recv (&recebido , 50 , MPI_CHAR , i, tag , MPI_COMM_WORLD ,&stats);
      printf("Mensagem recebida do processo %d: %s \n\n", i, recebido);

      enviado = "Chama o bombeiro lá\n\n";
      MPI_Send (enviado, 50, MPI_CHAR, i, tag, MPI_COMM_WORLD);

    }


  } else {
    enviado = "Ô loco tá pegando fogo bicho\n\n";
    MPI_Send (enviado, 50, MPI_CHAR, GERENTE, tag, MPI_COMM_WORLD);

    MPI_Recv (&recebido , 50 , MPI_CHAR , GERENTE, tag , MPI_COMM_WORLD ,&stats);
    printf("Mensagem recebida do processo %d: %s \n\n", 0, recebido);

  }
  MPI_Finalize();
return 0;
}
