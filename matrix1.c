#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to allocate memory for a square matrix
int** allocate_matrix(int size) {
    int** matrix = (int**) malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
        matrix[i] = (int*) malloc(size * sizeof(int));
    return matrix;
}

// Function to fill a matrix with random values
void fill_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = rand() % 10; // Values from 0 to 9
}

// Function to multiply two matrices
void multiply_matrices(int** A, int** B, int** result, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            result[i][j] = 0;
            for (int k = 0; k < size; k++)
                result[i][j] += A[i][k] * B[k][j];
        }
}

// Function to free a matrix
void free_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}

int main() {
    srand(time(NULL)); // Seed random number generator
    int sizes[] = {100, 200, 300, 400, 500}; // Different matrix sizes to test
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Matrix Size\tExecution Time (seconds)\n");

    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];

        int** A = allocate_matrix(size);
        int** B = allocate_matrix(size);
        int** C = allocate_matrix(size);

        fill_matrix(A, size);
        fill_matrix(B, size);

        clock_t start = clock();
        multiply_matrices(A, B, C, size);
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%d x %d\t\t%.6f\n", size, size, time_taken);

        free_matrix(A, size);
        free_matrix(B, size);
        free_matrix(C, size);
    }

    return 0;
}
