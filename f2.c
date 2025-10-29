#include <stdio.h>
#include <time.h>

// Iterative Fibonacci
long long fib_iterative(int n) {
    if (n <= 1) return n;

    long long t1 = 0, t2 = 1, next;
    for (int i = 2; i <= n; i++) {
        next = t1 + t2;
        t1 = t2;
        t2 = next;
    }
    return t2;
}

int main() {
    int n;
    printf("Enter n (up to 92): ");
    scanf("%d", &n);

    int repeats = 100000;  // run multiple times to get measurable time
    clock_t start = clock();

    long long result = 0;
    for (int i = 0; i < repeats; i++) {
        result = fib_iterative(n);
    }

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Iterative Fibonacci of %d = %lld\n", n, result);
    printf("Time taken = %f seconds (for %d runs)\n", time_taken, repeats);

    return 0;
}
