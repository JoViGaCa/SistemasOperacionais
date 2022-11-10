#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
  char nome;
  int tempo, chegada, prioridade;
  int exec, termino, espera;
} Processo;

int count = 0;

Processo* lerProcessos(FILE *arqe){
  Processo * proc = (Processo*) malloc(sizeof(Processo));
  int i = 0;
  char aux1[50];
  fscanf(arqe, "%s",aux1);
  char* token;
  token = strtok(aux1, "|");

  while(token != NULL){
    count++;
    proc = (Processo*) realloc(proc, (i+1)*sizeof(Processo));
    proc[i].nome = token[0];
    token = strtok(NULL, "|");
    i++;
  }

  return proc;
}

void lerTempos(FILE *arqe, Processo * proc){

  int i = 0;
  char aux1[50];
  fscanf(arqe, "%s",aux1);
  char* token;
  token = strtok(aux1, "|");

  while(token != NULL){
    proc[i].tempo = atoi(token);
    token = strtok(NULL, "|");
    i++;
  }
  return;
}

void lerChegada(FILE* arqe, Processo* proc){
  int i = 0;
  char aux1[50];
  fscanf(arqe, "%s",aux1);
  char* token;
  token = strtok(aux1, "|");

  while(token != NULL){
    proc[i].chegada = atoi(token);
    token = strtok(NULL, "|");
    i++;
  }
  return;
}

void lerPrioridade(FILE * arqe, Processo * proc){
  int i = 0;
  char aux1[50];
  fscanf(arqe, "%s",aux1);
  char* token;
  token = strtok(aux1, "|");

  while(token != NULL){
    proc[i].prioridade = atoi(token);
    token = strtok(NULL, "|");
    i++;
  }
  return;
}

void applyFCFS(Processo * proc){
  //Não preemprivo
  int tempo_atual = 0;
  Processo * ordenado = (Processo*) malloc(count*sizeof(Processo));

  for(int i = 0; i < count; i++){
    ordenado[i] = proc[i];
  }

  bool troca = true;
  Processo aux;

  while(troca){
    troca = false;
    for(int i = 0; i < count-2; i++){
      if(ordenado[i].chegada > ordenado[i+1].chegada){
        aux = ordenado[i];
        ordenado[i] = ordenado[i+1];
        ordenado[i+1] = aux;
        troca = true;
      }
    }
  }

  for(int i = 0; i < count; i++){
    printf("[%d]--%c--",tempo_atual, ordenado[i].nome);
    tempo_atual += ordenado[i].tempo;
    ordenado[i].termino = tempo_atual;
  }
  printf("[%d]\n", tempo_atual);

  float tmr = 0;
  for(int i = 0; i < count; i++){
    tmr += (ordenado[i].termino - ordenado[i].chegada);
  }
  tmr = tmr/count;

  float tme = 0;
  for(int i = 0; i < count; i++){
    tme += (ordenado[i].termino - ordenado[i].chegada - ordenado[i].tempo);
  }
  tme = tme/count;


  printf("Tempo médio de resposta: %.2f\n", tmr);
  printf("Tempo médio de espera: %.2f\n", tme);


  free(ordenado);
  printf("\n\n");
  return;
}

void applyPrioridadeNPremp(Processo * proc){
  int tempo_atual = 0;
  Processo * ordenado = (Processo*) malloc(count*sizeof(Processo));

  for(int i = 0; i < count; i++){
    ordenado[i] = proc[i];
  }

  bool troca = true;
  Processo aux;

  while(troca){
    troca = false;
    for(int i = 0; i <= count-2; i++){
      if(ordenado[i].prioridade > ordenado[i+1].prioridade){
        aux = ordenado[i];
        ordenado[i] = ordenado[i+1];
        ordenado[i+1] = aux;
        troca = true;
      }
    }
  }

  for(int i = 0; i < count; i++){
    printf("[%d]--%c--",tempo_atual, ordenado[i].nome);
    tempo_atual += ordenado[i].tempo;
    ordenado[i].termino = tempo_atual;
  }
  printf("[%d]\n", tempo_atual);

  float tmr = 0;
  for(int i = 0; i < count; i++){
    tmr += (ordenado[i].termino - ordenado[i].chegada);
  }
  tmr = tmr/count;

  float tme = 0;
  for(int i = 0; i < count; i++){
    tme += (ordenado[i].termino - ordenado[i].chegada - ordenado[i].tempo);
  }
  tme = tme/count;



  printf("Tempo médio de resposta: %.2f\n", tmr);
  printf("Tempo médio de espera: %.2f\n", tme);


  free(ordenado);
  printf("\n\n");
  return;
}

void applyPrioridadePremp(Processo * proc){
  int tempo_total = 0, tempo_atual = 0;
  int aux1 = 0, imprime = 0, diferenca = 0;
  Processo exec, aux;
  Processo * executaveis = (Processo*) malloc(sizeof(Processo));


  //calcula o tempo total
  for(int i = 0; i < count; i++){
    tempo_total += proc[i].tempo;
  }

  for(int i = 0; i < count; i++){
    proc[i].exec = 0;
  }

  int contador = 0;


  printf("[%d]", tempo_atual);
  while(tempo_atual < tempo_total){
    // criar vetor com os executáveis, que já chegaram
    contador = 0;
    for(int i = 0; i < count; i++){
      if(proc[i].chegada <= tempo_atual){
        contador++;
        executaveis = (Processo*) realloc(executaveis, contador*sizeof(Processo));
        executaveis[contador-1] = proc[i];
      }
    }
    // organizar por Prioridade
    bool troca = true;

    while(troca){
      troca = false;
      for(int i = 0; i <= contador-2; i++){
        if(executaveis[i].prioridade > executaveis[i+1].prioridade){
          aux = executaveis[i];
          executaveis[i] = executaveis[i+1];
          executaveis[i+1] = aux;
          troca = true;
        }
      }
    }


    // executar o de maior Prioridade
    while(diferenca == 0){
      diferenca = executaveis[aux1].exec - executaveis[aux1].tempo;
      aux1++;
    }
    printf("%d --", aux1);
    exec = executaveis[aux1];
    executaveis[aux1].exec++;


    tempo_atual++;
    diferenca = 0;
    aux1 = 0;

    //printf("--%c--[%d]", exec.nome, tempo_atual);

    // aumentar a espera do que não foram
    //



  }

  return;
}


int main(){
  FILE* arqe = fopen("entrada1.txt", "r");
  if(arqe == NULL){
    printf("Erro ao abrir arquivos.\n");
    exit(0);
  }
 char c;
 char tipo[10];
 Processo * processos;

  while((c = fgetc(arqe)) != EOF){
    fseek(arqe, -1, SEEK_CUR);
    strcpy(tipo, "Nulo");
    fscanf(arqe, "%s",tipo);

    if((strcmp(tipo, "Processo")) == 0){
      processos = lerProcessos(arqe);
    }

    if((strcmp(tipo, "Tempo")) == 0){
      lerTempos(arqe, processos);
    }

    if((strcmp(tipo, "Chegada")) == 0){
      lerChegada(arqe, processos);
    }

    if((strcmp(tipo, "Prioridade")) == 0){
      lerPrioridade(arqe, processos);
    }

    if((strcmp(tipo, "Nulo")) == 0){
      break;
    }

  }

  //applyFCFS(processos);

  //applyPrioridadeNPremp(processos);

  applyPrioridadePremp(processos);


  free(processos);
  fclose(arqe);
  return 0;
}
