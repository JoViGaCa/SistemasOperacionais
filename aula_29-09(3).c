#include <mpi.h>
#include <stdio.h>
#define GERENTE 0


int main(int argc , char **argv){
  int i, id , size ,len , tag = 666;

  int matrix[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
  int matrix2[3][3] = {{3,2,1}, {6,5,4}, {9,8,7}};

  int recebido[3];
  int recebido2[3];

  MPI_Status stats; // Status da mensagem recebida
  MPI_Init (&argc , &argv);
  MPI_Comm_rank(MPI_COMM_WORLD , &id);
  MPI_Comm_size(MPI_COMM_WORLD , &size); //size == número de processos

  if (id == GERENTE) {
    for (i = 1; i < size; ++i) {
      MPI_Send (matrix[i-1], 3, MPI_INT, i, tag, MPI_COMM_WORLD);
      MPI_Send (matrix2[i-1], 3, MPI_INT, i, tag, MPI_COMM_WORLD);
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

    MPI_Recv (recebido2, 3, MPI_INT, GERENTE, tag, MPI_COMM_WORLD ,&stats);
    printf("Números recebidos: %d %d %d \n\n", recebido2[0], recebido2[1], recebido2[2]);


    for(int i = 0; i < size-1; i++){
      recebido[i] = recebido[i] + recebido2[i];
    }

    MPI_Send(recebido, 3, MPI_INT, GERENTE, tag, MPI_COMM_WORLD);

  }
  MPI_Finalize();
return 0;
}
