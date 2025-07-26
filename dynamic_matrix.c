#include <stdio.h>
#include <stdlib.h>

void within_one_buffer();
void arr_default();
void second_arr();

int main() {
    within_one_buffer();
    arr_default();
    second_arr();

    return 0;
}

// Array of pointers to array segments within one buffer

void within_one_buffer() {
    const int m = 4, n = 4;
    int** single_array_matrix = malloc(m * n * sizeof(int) + m * sizeof(int*));
    int* ptr = (int*)(single_array_matrix + m);
    int count = 0;

    for (int i = 0; i < m; ++i) {
        single_array_matrix[i] = ptr + n * i;
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            single_array_matrix[i][j] = ++count;
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", single_array_matrix[i][j]);
        }
    }

    free(single_array_matrix);

    printf("\n");
}

// Array of pointers to arrays

void arr_default() {
    const int m = 4, n = 4;
    int count = 0;

    int** pointer_array = malloc(m * sizeof(int*));
    for (int i = 0; i < m; ++i) {
        pointer_array[i] = malloc(n * sizeof(int));
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            pointer_array[i][j] = ++count;
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", pointer_array[i][j]);
        }
    }

    for (int i = 0; i < m; ++i) {
        free(pointer_array[i]);
    }

    free(pointer_array);

    printf("\n");
}

void second_arr() {
    const int m = 4, n = 4;
    int** pointer_array = malloc(m * sizeof(int*));
    int* values_array = malloc(m * n * sizeof(int));
    int count = 0;

    for (int i = 0; i < m; ++i) {
        pointer_array[i] = values_array + n * i;
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            pointer_array[i][j] = ++count;
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", pointer_array[i][j]);
        }
    }

    free(values_array);
    free(pointer_array);

    printf("\n");
}