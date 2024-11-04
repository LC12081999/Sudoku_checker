#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUMITEMS 8

int buffer[NUMITEMS] = {-1};
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

int index_of_item(int buffer[NUMITEMS]) {
    for (int i = 0; i < NUMITEMS; i++) {
        if (buffer[i] != -1) {
            return i;
        }
    }
    return -1;
}

int index_of_not_item(int buffer[NUMITEMS]) {
    for (int i = 0; i < NUMITEMS; i++) {
        if (buffer[i] == -1) {
            return i;
        }
    }
    return -1;
}

void *production(void *arg) {
    srand(time(NULL));

    while(1) {
        int index = index_of_not_item(buffer);
        pthread_mutex_lock(&m);
        if (index == -1) {
            pthread_cond_wait(&c, &m);
        } else {
            buffer[index] = index;

            pthread_cond_signal(&c);
            pthread_mutex_unlock(&m);
        }

        float random_time = (rand() % 901 + 100) / 1000.0;
        unsigned int microseconds = (unsigned int)(random_time * 1000000);
        usleep(microseconds);
    }

    return NULL;
}

void *consumation(void *arg) {
    while(1) {
        pthread_mutex_lock(&m);

        int index = index_of_item(buffer);
        if (index != -1) {
            printf("Consommation de l'élément à l'index %d\n", buffer[index]);
            buffer[index] = -1;
        }
        
        pthread_cond_signal(&c);
        pthread_mutex_unlock(&m);
    }

    return NULL;
}

int main() {
    pthread_t producer, consumer;


    pthread_create(&producer, NULL, production, NULL);
    pthread_create(&consumer, NULL, consumation, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);

    return 0;
}