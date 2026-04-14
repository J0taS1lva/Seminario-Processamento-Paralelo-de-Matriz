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
    
    // A thread mostra o que está lendo
    printf(" Thread %D | Linha %d | [ ", r, r);

    for (int j = 0; j < TAM; j++) {
        printf("%02d ", Matriz[r][j]); // Valor de leitura
    }

    printf("] | x2 | [ ");

    // Opreação
    for (int j = 0; j < TAM; j++){
        Matriz[r][j] *= 2;
        printf("%02d ", Matriz[r][j]); // Valor de escrita
    }
    printf("] \n");
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

    printf("\n=== TABELA DE EXECUCAO PARALELA ===\n");
    printf(" ID Thread | Linha   | Leitura          | Op | Escrita\n");
    printf("-----------|---------|------------------|----|----------\n");

    // Threads
    for (int i = 0; i <threadNUM; i++){
        t_arg[i].idLinha = i;
        pthread_create(&threads[i], NULL, processLine, (void*)&t_arg[i]);
    }

    // Sincronização
    for (int i = 0; i < threadNUM; i++){
        pthread_join(threads[i], NULL);
    }


    printf(" Processo conluido.\n");
    return 0;
}
