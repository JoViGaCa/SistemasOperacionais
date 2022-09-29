#include <mpi.h>
#include <stdio.h>
#define GERENTE 0


int main(int argc , char **argv){
  int i, id , size ,len , tag = 666;

  int matrix[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
  int recebido[3];

  MPI_Status stats; // Status da mensagem recebida
  MPI_Init (&argc , &argv);
  MPI_Comm_rank(MPI_COMM_WORLD , &id);
  MPI_Comm_size(MPI_COMM_WORLD , &size); //size == número de processos

  if (id == GERENTE) {
    for (i = 1; i < size; ++i) {
      MPI_Send (matrix[i-1], 3, MPI_INT, i, tag, MPI_COMM_WORLD);
    }

    for (i = 1; i < size; ++i) {
      MPI_Recv (matrix[i-1], 3, MPI_INT, i, tag, MPI_COMM_WORLD ,&stats);
    }

    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        printf("| %d |", matrix[i][j]);
      }
      printf("\n");
    }

  } else {

    MPI_Recv (recebido, 3, MPI_INT, GERENTE, tag, MPI_COMM_WORLD ,&stats);
    printf("Números recebidos: %d %d %d \n\n", recebido[0], recebido[1], recebido[2]);

    for(int i = 0; i < size-1; i++){
      recebido[i]++;
    }

    MPI_Send(recebido, 3, MPI_INT, GERENTE, tag, MPI_COMM_WORLD);

  }
  MPI_Finalize();
return 0;
}
