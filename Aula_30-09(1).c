#include <mpi.h>
#include <stdio.h>
#define GERENTE 0


int main(int argc , char **argv){
  int i, id , size ,len , tag = 666;

  int matrix1[3][3] = {{2,0,0}, {0,2,0}, {0,0,2}};
  int matrix[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
  int recebido[3];
  int recebido2[3];
  int resultado;

  MPI_Status stats; // Status da mensagem recebida
  MPI_Init (&argc , &argv);
  MPI_Comm_rank(MPI_COMM_WORLD , &id);
  MPI_Comm_size(MPI_COMM_WORLD , &size); //size == número de processos

  if (id == GERENTE) {
    for (i = 1; i < size; ++i) {
        MPI_Send (matrix[(i-1)/3], 3, MPI_INT, i, tag, MPI_COMM_WORLD);
        MPI_Send (matrix1[(i-1)%3], 3, MPI_INT, i, tag, MPI_COMM_WORLD);
    }

    for (i = 1; i < size; ++i) {
      MPI_Recv (&resultado, 1, MPI_INT, i, tag, MPI_COMM_WORLD ,&stats);
      printf("| %d |", resultado);
      if (((i-1)%3) == 2){
        printf("\n");
      }
    }


  } else {

    MPI_Recv (recebido, 3, MPI_INT, GERENTE, tag, MPI_COMM_WORLD ,&stats);
    printf("Números recebidos: %d %d %d \n\n", recebido[0], recebido[1], recebido[2]);

    MPI_Recv (recebido2, 3, MPI_INT, GERENTE, tag, MPI_COMM_WORLD ,&stats);
    printf("Números recebidos: %d %d %d \n\n", recebido2[0], recebido2[1], recebido2[2]);

    resultado = recebido[0] * recebido2[0] + recebido[1] * recebido2[1] + recebido[2] * recebido2[2];

    MPI_Send(&resultado, 1, MPI_INT, GERENTE, tag, MPI_COMM_WORLD);

  }
  MPI_Finalize();
return 0;
}
