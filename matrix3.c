#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SIZE 1

// Allocate memory for a square matrix
int** allocate_matrix(int size) {
    int** matrix = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
        matrix[i] = calloc(size, sizeof(int));
    return matrix;
}

// Free memory
void free_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}

// Fill matrix with random numbers
void fill_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = rand() % 10;
}

// Matrix addition
void add_matrix(int** A, int** B, int** result, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] + B[i][j];
}

// Matrix subtraction
void subtract_matrix(int** A, int** B, int** result, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] - B[i][j];
}

// Copy submatrix
void copy_submatrix(int** src, int** dest, int row, int col, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            dest[i][j] = src[i + row][j + col];
}

// Paste submatrix
void paste_submatrix(int** src, int** dest, int row, int col, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            dest[i + row][j + col] = src[i][j];
}

// Strassen’s matrix multiplication
void strassen(int** A, int** B, int** C, int size) {
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

    // Copy input matrices into quadrants
    copy_submatrix(A, A11, 0, 0, newSize);
    copy_submatrix(A, A12, 0, newSize, newSize);
    copy_submatrix(A, A21, newSize, 0, newSize);
    copy_submatrix(A, A22, newSize, newSize, newSize);
    copy_submatrix(B, B11, 0, 0, newSize);
    copy_submatrix(B, B12, 0, newSize, newSize);
    copy_submatrix(B, B21, newSize, 0, newSize);
    copy_submatrix(B, B22, newSize, newSize, newSize);

    // Allocate temporary matrices
    int** M1 = allocate_matrix(newSize);
    int** M2 = allocate_matrix(newSize);
    int** M3 = allocate_matrix(newSize);
    int** M4 = allocate_matrix(newSize);
    int** M5 = allocate_matrix(newSize);
    int** M6 = allocate_matrix(newSize);
    int** M7 = allocate_matrix(newSize);
    int** Atemp = allocate_matrix(newSize);
    int** Btemp = allocate_matrix(newSize);

    // M1 = (A11 + A22) * (B11 + B22)
    add_matrix(A11, A22, Atemp, newSize);
    add_matrix(B11, B22, Btemp, newSize);
    strassen(Atemp, Btemp, M1, newSize);

    // M2 = (A21 + A22) * B11
    add_matrix(A21, A22, Atemp, newSize);
    strassen(Atemp, B11, M2, newSize);

    // M3 = A11 * (B12 - B22)
    subtract_matrix(B12, B22, Btemp, newSize);
    strassen(A11, Btemp, M3, newSize);

    // M4 = A22 * (B21 - B11)
    subtract_matrix(B21, B11, Btemp, newSize);
    strassen(A22, Btemp, M4, newSize);

    // M5 = (A11 + A12) * B22
    add_matrix(A11, A12, Atemp, newSize);
    strassen(Atemp, B22, M5, newSize);

    // M6 = (A21 - A11) * (B11 + B12)
    subtract_matrix(A21, A11, Atemp, newSize);
    add_matrix(B11, B12, Btemp, newSize);
    strassen(Atemp, Btemp, M6, newSize);

    // M7 = (A12 - A22) * (B21 + B22)
    subtract_matrix(A12, A22, Atemp, newSize);
    add_matrix(B21, B22, Btemp, newSize);
    strassen(Atemp, Btemp, M7, newSize);

    // C11 = M1 + M4 - M5 + M7
    add_matrix(M1, M4, Atemp, newSize);
    subtract_matrix(Atemp, M5, Btemp, newSize);
    add_matrix(Btemp, M7, Atemp, newSize);
    paste_submatrix(Atemp, C, 0, 0, newSize);

    // C12 = M3 + M5
    add_matrix(M3, M5, Atemp, newSize);
    paste_submatrix(Atemp, C, 0, newSize, newSize);

    // C21 = M2 + M4
    add_matrix(M2, M4, Atemp, newSize);
    paste_submatrix(Atemp, C, newSize, 0, newSize);

    // C22 = M1 - M2 + M3 + M6
    subtract_matrix(M1, M2, Atemp, newSize);
    add_matrix(Atemp, M3, Btemp, newSize);
    add_matrix(Btemp, M6, Atemp, newSize);
    paste_submatrix(Atemp, C, newSize, newSize, newSize);

    // Free all matrices
    free_matrix(A11, newSize); free_matrix(A12, newSize);
    free_matrix(A21, newSize); free_matrix(A22, newSize);
    free_matrix(B11, newSize); free_matrix(B12, newSize);
    free_matrix(B21, newSize); free_matrix(B22, newSize);
    free_matrix(M1, newSize); free_matrix(M2, newSize);
    free_matrix(M3, newSize); free_matrix(M4, newSize);
    free_matrix(M5, newSize); free_matrix(M6, newSize);
    free_matrix(M7, newSize); free_matrix(Atemp, newSize);
    free_matrix(Btemp, newSize);
}

// Main function to test execution time
int main() {
    srand(time(NULL));
    int sizes[] = {64, 128, 256, 512}; // Only powers of 2
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
        strassen(A, B, C, size);
        clock_t end = clock();

        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%d x %d\t\t%.6f\n", size, size, elapsed);

        free_matrix(A, size);
        free_matrix(B, size);
        free_matrix(C, size);
    }

    return 0;
}
