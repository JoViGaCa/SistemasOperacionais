#include <mpi.h>
#include <stdio.h>
#define GERENTE 0


int main(int argc , char **argv){
  int i, id , size ,len , tag = 666;

  int matrix1[3][3] = {{2,0,0}, {0,2,0}, {0,0,2}};
  int matrix[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
  int matrixResult[3][3];
  int recebido;
  int recebido2;
  int resultado;

  MPI_Status stats; // Status da mensagem recebida
  MPI_Init (&argc , &argv);
  MPI_Comm_rank(MPI_COMM_WORLD , &id);
  MPI_Comm_size(MPI_COMM_WORLD , &size); //size == número de processos

  int count = 1;
  int linha = 0;
  int colum = 0;
  int fim = -1;


  if (id == GERENTE) {
    while (1) {
      MPI_Send (&(matrix[linha][colum]), 1, MPI_INT, count, tag, MPI_COMM_WORLD);
      printf("Enviando %d para o processo %d\n", matrix[linha][colum], count);
      MPI_Send (&(matrix1[linha][colum]), 1, MPI_INT, count, tag, MPI_COMM_WORLD);

      MPI_Recv (&(matrixResult[linha][colum]), 1, MPI_INT, count, tag, MPI_COMM_WORLD ,&stats);
      printf("Resultado %d recebido\n", matrixResult[linha][colum]);

      count++;
      if(count == size){
        count = 1;
      }

      linha++;
      if(linha == 3){
        colum++;
        linha = 0;
        if(colum == 3){
          for(int i = 1; i < size; i++){
            MPI_Send (&fim, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
          }
          break;
        }
      }
    }

    for (int i = 0; i < 3; i++){
      for (int j = 0; j < 3; j++){
        printf("| %d |", matrixResult[i][j]);
      }
      printf("\n");
    }


  } else {
    while(1){
      MPI_Recv (&recebido, 1, MPI_INT, GERENTE, tag, MPI_COMM_WORLD ,&stats);
      if(recebido == fim){
        printf("Acabou\n");
        break;
      }
      printf("Números recebidos: %d \n\n", recebido);

      MPI_Recv (&recebido2, 1, MPI_INT, GERENTE, tag, MPI_COMM_WORLD ,&stats);
      if(recebido2 == fim){
        break;
      }
      printf("Números recebidos: %d \n\n", recebido2);

      resultado = recebido + recebido2;

      MPI_Send(&resultado, 1, MPI_INT, GERENTE, tag, MPI_COMM_WORLD);
      printf("Resultado %d enviado \n", resultado);
    }


  }
  MPI_Finalize();
return 0;
}
