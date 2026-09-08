#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* routine(){
    printf("Test from threads\n");
    sleep(2);
    printf("Ending thread\n");
}

int main(int argc, char* argv[]){
    pthread_t t1, t2; // Variáveis que armazenam informações da Thread
    if (pthread_create(&t1, NULL, &routine, NULL) != 0){
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine, NULL) != 0){
        return 2;
    }

    if (pthread_join(t1, NULL) != 0){ // Espera que a Thread se encerre antes de finalizar o processo
        return 3;
    }
    if (pthread_join(t2, NULL) != 0){
        return 4;
    }
    return 0;
}

// A função pthread_create recebe os seguintes argumentos: o ponteiro para a variável ta thread (no caso, t1 e t2),
// um atributo de customização da thread, a função que a thread vai executar e o argumento que vai ser passado para a função.

// Todas essas funções retornam um valor 0 caso bem sucedidas, e um valor diferente de 0 caso algum erro ocorra.
