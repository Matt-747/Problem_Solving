#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_THREADS 2

pthread_mutex_t mutex_Fuel;
pthread_cond_t cond_Fuel; // Cria uma variável de condição

int fuel = 0; // Variável global que armazena a qtd de combustível ainda presente

void* fuel_filling(void* arg){
    for(int k = 0; k < 5; k++){ // Enche o tanque 5 vezes
        pthread_mutex_lock(&mutex_Fuel);
        fuel += 15;
        printf("Filled fuel: %d\n", fuel);
        pthread_mutex_unlock(&mutex_Fuel);
        pthread_cond_signal(&cond_Fuel); // Envia um sinal para a thread em espera para que ela possa continuar sua execução
        sleep(1);
    }
}

void* fuel_consume(void* arg){
    pthread_mutex_lock(&mutex_Fuel);
    while(fuel < 40){ // Para evitar que a quantidade de combustível seja negativa
        printf("No fuel, waiting...\n");
        pthread_cond_wait(&cond_Fuel, &mutex_Fuel);
        // Ao entrar no While, chama a função wait. Ela: desbloqueia o mutex (mutex_unlock); aguarda a chamada da função signal;
        // bloqueia o mutex novamente.

        // Nesse caso, após a primeira iteração do while, a thread irá aguardar a execução da thread que preenche o combustível
        // até que, após a chamada de cond_signal, a condição >= 40 seja satisfeita para que esta saia do loop e continue sua
        // execução.
    }
    fuel -= 40;
    printf("Got fuel, there's %d left:\n", fuel);
    pthread_mutex_unlock(&mutex_Fuel);

}

int main(int argc, char* argv){
    pthread_t ths[NUM_THREADS];
    pthread_mutex_init(&mutex_Fuel, NULL);
    pthread_cond_init(&cond_Fuel, NULL);

    for(int i = 0; i < NUM_THREADS; i++){
        if(i == 0) // A primeira thread vai ser a que vai encher o "tanque do posto de gasoline"
            if(pthread_create(ths + i, NULL, &fuel_filling, NULL)){
                perror("Erro ao criar thread fuel_filling");
                return 1;
            }

        else // A segunda thread vai ser a que vai encher o "tanque do carro"
            if(pthread_create(ths + i, NULL, &fuel_consume, NULL)){
                perror("Erro ao criar thread fuel_consume");
                return 2;
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
