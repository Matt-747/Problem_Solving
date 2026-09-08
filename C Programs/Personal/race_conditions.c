#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREAD 4

int mails = 0;
pthread_mutex_t mutex; // Cria a variável mutex

void* routine(){
    for(int i = 0; i < 10000000; i++){
        pthread_mutex_lock(&mutex); // Trava o mutex
        mails++;
        pthread_mutex_unlock(&mutex); // Libera o mutex
    }
}

int main(int argc, char* argv[]){
    pthread_t ths[NUM_THREAD]; // Cria um vetor que vai armazenar as threads criadas
    pthread_mutex_init(&mutex, NULL); // Inicializa a variável mutex

    for(int i = 0; i < NUM_THREAD; i++){
        if(pthread_create(ths + i, NULL, &routine, NULL)){ // Caso retorne um valor diferente de 0
            perror("Erro ao inicializar thread\n");
            return 1;
        }
        printf("Thread %d começou\n", i);
    }

    for(int i = 0; i < NUM_THREAD; i++){
        if (pthread_join(ths[i], NULL)){
            return 2;
        }
        printf("Thread %d terminou de executar\n", i);

    }
    pthread_mutex_destroy(&mutex); // Elimina o espaço da memória do mutex
    printf("Number of mails: %d\n", mails);
    
    return 0;
}

// Criamos dois loops diferentes (um para iniciar as threads e outro para dar start) porque após o primeiro loop que criou a 
// thread 1 termina de executar ele já inicia o comando de join, que faz com que o programa aguarde o processamento da thread
// 1 para poder continuar. Logo, o programa não está realmente rodando em paralelo; as threads estão sendo criadas e encerradas
// umaa a uma sequencialmente. Ao separar os loops, removemos esse problema e todas as threas executam ao mesmo tempo
