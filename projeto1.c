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
  int tempo_atual = 0, tempo_total = 0, aux1 = 0;
  Processo * executaveis = (Processo*) malloc(count*sizeof(Processo));
  Processo exec, aux;
  char ultimo = ' ';

  int contador = 0;

  for(int i = 0; i < count; i++){
    tempo_total += proc[i].tempo;
  }


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


    //achar o de menor Prioridade
    for(int i = 0; i < contador; i++){
      aux1=i;
      if(executaveis[i].tempo != executaveis[i].exec){
        break;
      }
    }
    exec = executaveis[aux1];
    for(int i = 0; i < count; i++){
      if(proc[i].nome == exec.nome){
        proc[i].termino = tempo_atual + proc[i].tempo;
        proc[i].exec+= proc[i].tempo;
      }
    }


    aux1 = 0;
    if(ultimo != exec.nome){
      printf("[%d]--%c--", tempo_atual, exec.nome);
      ultimo = exec.nome;
    }
    tempo_atual+= exec.tempo;



  }
  printf("[%d]\n", tempo_atual);

  float tmr = 0;
  for(int i = 0; i < count; i++){
    tmr += (proc[i].termino - proc[i].chegada);

  }
  tmr = tmr/count;

  float tme = 0;
  for(int i = 0; i < count; i++){
    tme += (proc[i].termino - proc[i].chegada - proc[i].tempo);
  }
  tme = tme/count;



  printf("Tempo médio de resposta: %.2f\n", tmr);
  printf("Tempo médio de espera: %.2f\n", tme);


  free(executaveis);
  printf("\n\n");
  return;
}

void applyPrioridadePremp(Processo * proc){
  int tempo_total = 0, tempo_atual = 0;
  int aux1 = 0, imprime = 0;
  Processo exec, aux;
  Processo * executaveis = (Processo*) malloc(sizeof(Processo));
  char ultimo = ' ';

  //calcula o tempo total
  for(int i = 0; i < count; i++){
    tempo_total += proc[i].tempo;
  }

  for(int i = 0; i < count; i++){
    proc[i].exec = 0;
    proc[i].espera = 0;
  }

  int contador = 0;


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



    //achar o de menor Prioridade
    for(int i = 0; i < contador; i++){
      aux1=i;
      if(executaveis[i].tempo != executaveis[i].exec){
        break;
      }
    }
    //executar
    exec = executaveis[aux1];
    for(int i = 0; i < count; i++){
      if(proc[i].nome == exec.nome){
        proc[i].exec++;
      } else {
        if(proc[i].chegada < tempo_atual && proc[i].exec != proc[i].tempo){
          proc[i].espera++;
        }

      }
    }


    aux1 = 0;
    if(ultimo != exec.nome){
      for(int i = 0; i < count; i++){
        if(proc[i].nome == ultimo && proc[i].exec == proc[i].tempo){
          proc[i].termino = tempo_atual;
        }
      }
      printf("[%d]--%c--", tempo_atual, exec.nome);
      ultimo = exec.nome;
    }
    tempo_atual++;
  }
  printf("[%d]", tempo_atual);

  float tmr = 0, tme = 0;
  for(int i = 0; i < count; i++){
    tmr += executaveis[i].termino - executaveis[i].chegada;
    tme += executaveis[i].espera;
  }

  tmr = tmr/count;
  tme = tme/count;

  printf("\nTempo médio de resposta: %.2f\n", tmr);
  printf("Tempo médio de espera: %.2f\n", tme);

  free(executaveis);

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

  printf("Escalonamento por FCFS:\n");
  applyFCFS(processos);
  printf("\n\n");

  printf("Escalonamento por Prioridade não preemptiva:\n");
  applyPrioridadeNPremp(processos);
  printf("\n\n");

  printf("Escalonamento por Prioridade Preemptiva:\n");
  applyPrioridadePremp(processos);


  free(processos);
  fclose(arqe);
  return 0;
}
