#include <stdio.h>
#include <time.h>

long long fib_array[100]; 

long long fib(int n) {
    if (n <= 1) {
        return n;
    }

    // If already computed, return it
    if (fib_array[n] != 0) {
        return fib_array[n];
    }

    // Otherwise, compute and store it
    fib_array[n] = fib(n - 1) + fib(n - 2);
    return fib_array[n];
}

int main() {
    int terms;
    printf("Enter the number of terms (up to 92): ");
    scanf("%d", &terms);

    // Initialize array with 0s
    for (int i = 0; i < 100; i++) {
        fib_array[i] = 0;
    }

    clock_t start = clock();

    printf("Fibonacci Series: ");
    for (int i = 0; i < terms; i++) {
        printf("%lld", fib(i));
        if (i < terms - 1) printf(", "); // avoid trailing comma
    }
    printf("\n");

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Time taken = %f seconds\n", time_taken);

    return 0;
}
