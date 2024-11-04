#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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
int valid_thread[27] = {0};

typedef struct {
    int row;
    int column;
} parameters;

void *check_row(void *arg) {
    parameters *param = (parameters *)(arg);
    int numbers[9] = {0};

    int row = param->row;

    for (int i = 0; i < 9; i++) {
        int num = sudoku[row][i];
        if (numbers[num - 1] == 1 || num < 1 || num > 9) {
            return NULL;
        } else {
            numbers[num - 1] = 1;
        }
    }

    valid_thread[row] = 1;
    return NULL;
}

void *check_column(void *arg) {
    parameters *param = (parameters *)(arg);
    int numbers[9] = {0};

    int column = param->column;

    for (int i = 0; i < 9; i++) {
        int num = sudoku[i][column];
        if (numbers[num - 1] == 1 || num < 1 || num > 9) {
            return NULL;
        } else {
            numbers[num - 1] = 1;
        }
    }

    valid_thread[column + 9] = 1;
    return NULL;
}

void *check_square(void *arg) {
    parameters *param = (parameters *)(arg);
    int numbers[9] = {0};

    int row = param->row;
    int column = param->column;

    int limit_row = row + 3;
    int limit_column = column + 3;

    for (int i = row; i < limit_row; i++) {
        for (int j = column; j < limit_column; j++) {
            int num = sudoku[i][j];
            if (numbers[num - 1] == 1 || num < 1 || num > 9) {
                return NULL;
            } else {
                numbers[num - 1] = 1;
            }
        }
    }

    valid_thread[18 + (row / 3) * 3 + (column / 3)] = 1;
    return NULL;
}



int main(int argc, char *argv[]) {
    pthread_t threads[27];
    int thread_index = 0;


    for (int i = 0; i < 9; i++) {
        parameters *param = (parameters *)malloc(sizeof(parameters));
        param->column = 0;
        param->row = i;
        pthread_create(&threads[thread_index++], NULL, check_row, param);
    }

    for (int i = 0; i < 9; i++) {
        parameters *param = (parameters *)malloc(sizeof(parameters));
        param->column = i;
        param->row = 0;
        pthread_create(&threads[thread_index++], NULL, check_column, param);
    }

    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            parameters *param = (parameters *)malloc(sizeof(parameters));
            param->column = i;
            param->row = j;
            pthread_create(&threads[thread_index++], NULL, check_square, param);
        }
    }

    for (int i = 0; i < 27; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < 27; i++) {
        if (valid_thread[i] == 0) {
            printf("Le sudoku n'est pas valide\n");
            return 0;
        }
    }

    printf("Le sudoku est valide\n");
    return 0;
}