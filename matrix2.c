#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SIZE 1  // Base case size

// Allocate memory for a square matrix
int** allocate_matrix(int size) {
    int** matrix = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
        matrix[i] = calloc(size, sizeof(int));  // Zero-initialized
    return matrix;
}

// Free matrix memory
void free_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}

// Fill matrix with random integers
void fill_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = rand() % 10;
}

// Add two matrices
void add_matrix(int** A, int** B, int** result, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] + B[i][j];
}

// Subtract two matrices
void subtract_matrix(int** A, int** B, int** result, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] - B[i][j];
}

// Copy submatrix from src to dest
void copy_submatrix(int** src, int** dest, int row, int col, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            dest[i][j] = src[i + row][j + col];
}

// Paste submatrix from src to dest
void paste_submatrix(int** src, int** dest, int row, int col, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            dest[i + row][j + col] = src[i][j];
}

// Recursive divide and conquer matrix multiplication
void multiply_dc(int** A, int** B, int** C, int size) {
    if (size == MIN_SIZE) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;

    // Allocate submatrices
    int** A11 = allocate_matrix(newSize);
    int** A12 = allocate_matrix(newSize);
    int** A21 = allocate_matrix(newSize);
    int** A22 = allocate_matrix(newSize);
    int** B11 = allocate_matrix(newSize);
    int** B12 = allocate_matrix(newSize);
    int** B21 = allocate_matrix(newSize);
    int** B22 = allocate_matrix(newSize);
    int** C11 = allocate_matrix(newSize);
    int** C12 = allocate_matrix(newSize);
    int** C21 = allocate_matrix(newSize);
    int** C22 = allocate_matrix(newSize);
    int** temp1 = allocate_matrix(newSize);
    int** temp2 = allocate_matrix(newSize);

    // Split matrices
    copy_submatrix(A, A11, 0, 0, newSize);
    copy_submatrix(A, A12, 0, newSize, newSize);
    copy_submatrix(A, A21, newSize, 0, newSize);
    copy_submatrix(A, A22, newSize, newSize, newSize);
    copy_submatrix(B, B11, 0, 0, newSize);
    copy_submatrix(B, B12, 0, newSize, newSize);
    copy_submatrix(B, B21, newSize, 0, newSize);
    copy_submatrix(B, B22, newSize, newSize, newSize);

    // C11 = A11*B11 + A12*B21
    multiply_dc(A11, B11, temp1, newSize);
    multiply_dc(A12, B21, temp2, newSize);
    add_matrix(temp1, temp2, C11, newSize);

    // C12 = A11*B12 + A12*B22
    multiply_dc(A11, B12, temp1, newSize);
    multiply_dc(A12, B22, temp2, newSize);
    add_matrix(temp1, temp2, C12, newSize);

    // C21 = A21*B11 + A22*B21
    multiply_dc(A21, B11, temp1, newSize);
    multiply_dc(A22, B21, temp2, newSize);
    add_matrix(temp1, temp2, C21, newSize);

    // C22 = A21*B12 + A22*B22
    multiply_dc(A21, B12, temp1, newSize);
    multiply_dc(A22, B22, temp2, newSize);
    add_matrix(temp1, temp2, C22, newSize);

    // Combine results
    paste_submatrix(C11, C, 0, 0, newSize);
    paste_submatrix(C12, C, 0, newSize, newSize);
    paste_submatrix(C21, C, newSize, 0, newSize);
    paste_submatrix(C22, C, newSize, newSize, newSize);

    // Free all temp matrices
    free_matrix(A11, newSize); free_matrix(A12, newSize);
    free_matrix(A21, newSize); free_matrix(A22, newSize);
    free_matrix(B11, newSize); free_matrix(B12, newSize);
    free_matrix(B21, newSize); free_matrix(B22, newSize);
    free_matrix(C11, newSize); free_matrix(C12, newSize);
    free_matrix(C21, newSize); free_matrix(C22, newSize);
    free_matrix(temp1, newSize); free_matrix(temp2, newSize);
}

// Main
int main() {
    srand(time(NULL));
    int sizes[] = {64, 128, 256, 512}; // Powers of 2 only
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Matrix Size\tExecution Time (seconds)\n");

    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];

        int** A = allocate_matrix(size);
        int** B = allocate_matrix(size);
        int** C = allocate_matrix(size);

        fill_matrix(A, size);
        fill_matrix(B, size);

        clock_t start = clock();
        multiply_dc(A, B, C, size);
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%d x %d\t\t%.6f\n", size, size, time_taken);

        free_matrix(A, size);
        free_matrix(B, size);
        free_matrix(C, size);
    }

    return 0;
}
