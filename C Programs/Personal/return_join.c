#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define NUM_THREAD 6

void* roll_dice(){
    unsigned int seed = time(NULL) ^ pthread_self();

    int value = (rand_r(&seed) % 6) + 1; // Pega um valor de 1 a 6, pois rand % 6 só vai de 0 a 5
    int* result = malloc(sizeof(int)); // Aloca memória para retornar o valor
    *result = value; // O valor do ponteiro é o valor da rolagem

    return (void *) result;
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    pthread_t ths[NUM_THREAD];
    int* res; // Armazena o resultado das rolagens

    for(int i = 0; i < NUM_THREAD; i++){
        if(pthread_create(ths + i, NULL, &roll_dice, NULL)){
            perror("Erro ao inicializar thread");
            return 1;
        }
    }

    for(int i = 0; i < NUM_THREAD; i++){
        if(pthread_join(ths[i], (void**) &res)){
            perror("Erro ao aguardar a thread");
            return 2;
        }
        printf("Resultado thread %d: %d\n", i, *res);
        free(res); // Ao final da thread, libera o ponteiro alocado de resultado
    }

    return 0;
}
