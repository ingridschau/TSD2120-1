#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_NUM 2

pthread_mutex_t mutexBuffer;

FILE* inn;
FILE* ut;

int balanse = 0;

void* LeggTilPenger(void* args) {
        inn = fopen("inn.txt", "r");
        int tallFraInnFil = 0;

        for (int i = 0; i < 100000; i++){
                fscanf(inn, "%d", &tallFraInnFil);
                pthread_mutex_lock(&mutexBuffer);
                balanse += tallFraInnFil;
                pthread_mutex_unlock(&mutexBuffer);
        }
        fclose(inn);
}

void* TaUtPenger(void* args) {
        ut = fopen("ut.txt", "r");
        int tallFraUtFil = 0;

        for (int i = 0; i < 100000; i++){
                fscanf(ut, "%d", &tallFraUtFil);
                pthread_mutex_lock(&mutexBuffer);
                balanse -= tallFraUtFil;
                pthread_mutex_unlock(&mutexBuffer);
        }
        fclose(ut);
    }

int main(int argc, char* argv[]) {
        pthread_t traad[THREAD_NUM];
        pthread_mutex_init(&mutexBuffer, NULL);
        int i;
        for (i = 0; i < THREAD_NUM; i++) {
                if (i > 0) {
                if (pthread_create(&traad[i], NULL, &LeggTilPenger, NULL) != 0) {
                        perror("Failed to create thread");
                }
                } else {
                if (pthread_create(&traad[i], NULL, &TaUtPenger, NULL) != 0) {
                        perror("Failed to create thread");
                }
                }
        }
        for (i = 0; i < THREAD_NUM; i++) {
                if (pthread_join(traad[i], NULL) != 0) {
                perror("Failed to join thread");
                }
        }
        pthread_mutex_destroy(&mutexBuffer);
        printf("\nBalansen er %d.\n\n", balanse);
        return 0;
}
