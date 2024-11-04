#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int sudoku[9][9] = {
    {5, 3, 4, 6, 8, 7, 9, 1, 2},
    {6, 7, 2, 1, 9, 5, 3, 4, 8},
    {1, 9, 8, 3, 4, 2, 5, 6, 7},
    {8, 5, 9, 7, 6, 1, 4, 2, 3},
    {4, 2, 6, 8, 5, 3, 7, 9, 1},
    {7, 1, 3, 9, 2, 4, 8, 5, 6},
    {9, 6, 1, 5, 3, 7, 2, 8, 4},
    {2, 8, 7, 4, 1, 9, 6, 3, 5},
    {3, 4, 5, 2, 8, 6, 1, 7, 9}
};

int searched_number = -1;
int found = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *search(void *arg) {
    int column = (int)(arg);
    for (int i = 0; i < 9; i++) {
        pthread_mutex_lock(&m);
        if (found) {
            pthread_mutex_unlock(&m);
            return NULL;
        }
        if (sudoku[i][column] == searched_number) {
            found = 1;
            pthread_mutex_unlock(&m);
            return NULL;
        }
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main() {
    pthread_t threads[9];

    for (int i = 0; i < 9; i++) {
        pthread_create(&threads[i], NULL, search, i);
    }

    for (int i = 0; i < 9; i++) {
        pthread_join(threads[i], NULL);
    }

    if (found) {
        printf("Le nombre a été trouvé.");
    } else {
        printf("Le nombre n'a pas été trouvé.");
    }

    pthread_mutex_destroy(&m);

    return 0;
}