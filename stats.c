#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

int *input;
size_t n;

void *mean(void *arg) {
    double sum = 0;

    for (int i = 0; i < n; i++) {
        sum += input[i];
    }

    printf("The average value is %.2f\n", sum / n); 

    return NULL;
}

void *minimum(void *arg) {
    int min = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (input[i] < min) {
            min = input[i];
        }
    }

    printf("The minimum is %d\n", min);

    return NULL;
}

void *maximum(void *arg) {
    int max = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (input[i] > max) {
            max = input[i];
        }
    }

    printf("The maximum is %d\n", max);

    return NULL;
}

int main(int argc, char *argv[]) {
    n = argc - 1;
    
    input = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        input[i] = atoi(argv[i + 1]);
    }

    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, mean, NULL);
    pthread_create(&thread2, NULL, minimum, NULL);
    pthread_create(&thread3, NULL, maximum, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}
