#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_THREADS 10

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* arg){
    int index = *(int*) arg;
    printf("%d\n", primes[index]);
    free(arg);
}

int main(int argc, char* argv[]){
    pthread_t ths[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; i++){
        int* a = malloc(sizeof(int));
        *a = i;

        if(pthread_create(ths + i, NULL, &routine, a)){
            perror("Erro ao iniciar thread");
        }
    }

    for(int i = 0; i < NUM_THREADS; i++){
        if(pthread_join(ths[i], NULL)){
            perror("Erro ao finalizar thread");
        }
    }

    return 0;
}
