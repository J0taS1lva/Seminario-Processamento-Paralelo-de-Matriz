#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAM 4 // Tamanho da Matriz
#define threadNUM TAM

int Matriz[TAM][TAM];

typedef struct {
    int idLinha;
} thread_dado;

void* processLine(void* arg){
    thread_dado* dado = (thread_dado*)arg; // Transforma o (void*) no tipo de dado
    int r = dado->idLinha;

    for (int j = 0; j < TAM; j++){
        Matriz[r][j] *= 2;
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[threadNUM];
    thread_dado t_arg[threadNUM];

    // Inicia a Matriz
    for (int i = 0; i < TAM; i++){
        for (int j = 0; j < TAM; j++){
            Matriz[i][j] = i + j;
        }
    }

    // Threads
    for (int i = 0; i <threadNUM; i++){
        t_arg[i].idLinha = i;
        pthread_create(&threads[i], NULL, processLine, (void*)&t_arg[i]);
    }

    // Sincronização
    for (int i = 0; i < threadNUM; i++){
        pthread_join(threads[i], NULL);
    }


    printf("Processo conluido.");
    return 0;
}
