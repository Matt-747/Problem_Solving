#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_THREADS 5

pthread_mutex_t mutex_Fuel;
pthread_cond_t cond_Fuel;

int fuel = 0;

void* fuel_filling(void* arg){
    for(int k = 0; k < 5; k++){
        pthread_mutex_lock(&mutex_Fuel);
        fuel += 60;
        printf("Filled fuel: %d\n", fuel);
        pthread_mutex_unlock(&mutex_Fuel);
        pthread_cond_broadcast(&cond_Fuel); // Envia um sinal para TODAS as threads em espera
        // O comando cond_signal envia o sinal para apenas UMA thread, de tal forma que, se houver mais de uma thread em espera
        // elas não irão receber o sinal
        sleep(1);
    }

    return NULL;
}

void* fuel_consume(void* arg){
    pthread_mutex_lock(&mutex_Fuel);
    while(fuel < 40){
        printf("No fuel, waiting...\n");
        pthread_cond_wait(&cond_Fuel, &mutex_Fuel);
    }
    fuel -= 40;
    printf("Got fuel, there's %d left:\n", fuel);
    pthread_mutex_unlock(&mutex_Fuel);

    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t ths[NUM_THREADS];
    pthread_mutex_init(&mutex_Fuel, NULL);
    pthread_cond_init(&cond_Fuel, NULL);

    for(int i = 0; i < NUM_THREADS; i++){
        if(i == 4){ // A última thread vai ser a que vai encher o "tanque do posto de gasolina"
            if(pthread_create(ths + i, NULL, &fuel_filling, NULL)){
                perror("Erro ao criar thread fuel_filling");
                return 1;
            }
        }
        
        else {  // A segunda thread vai ser a que vai encher o "tanque do carro"
            if(pthread_create(ths + i, NULL, &fuel_consume, NULL)){
                perror("Erro ao criar thread fuel_consume");
                return 2;
            }
        }
            
    }

    for(int j = 0; j < NUM_THREADS; j++){
        if(pthread_join(ths[j], NULL)){
            printf("Erro ao entrar na thread %d\n", j+1);
            return 3;
        }
    }

    pthread_mutex_destroy(&mutex_Fuel);
    pthread_cond_destroy(&cond_Fuel);
    return 0;
}
