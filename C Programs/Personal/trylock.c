#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_THREADS 4

pthread_mutex_t mutex;

// O comando trylock não aguarda a chamada de um unlock; ao invés disso, ele tenta trancar a thread e, caso não consiga, retorna
// um valor diferente de 0 de tal forma que o programa continue a rodar sem precisar travar aguardando por um unlock.

void* routine(void* arg){
    if (pthread_mutex_trylock(&mutex) == 0){ // Retorna 0 se conseguiu trancar; retorna qualquer outra coisa se não conseguiu
        printf("Got lock\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
    else{
        printf("Didn't get lock\n");
    }
}

int main(int argc, char* argv){
    pthread_t ths[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < NUM_THREADS; i++){
        if(pthread_create(ths + i, NULL, &routine, NULL)){
            perror("Erro ao criar thread");
            return 1;
        }
    }

    for(int j = 0; j < NUM_THREADS; j++){
        if(pthread_join(ths[j], NULL)){
            perror("Erro ao join na thread");
            return 1;
        }
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
