#include <stdio.h>
#include <time.h>

// Function to calculate nth Fibonacci using Tabulation (DP)
long long nthFibonacci(int n) {
    if (n <= 1) return n;

    // Create dp array
    long long dp[n + 1];

    // Base cases
    dp[0] = 0;
    dp[1] = 1;

    // Fill dp array iteratively (bottom-up)
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    // Print series as well
    printf("Fibonacci Series up to %d terms: ", n);
    for (int i = 0; i <= n; i++) {
        printf("%lld", dp[i]);
        if (i < n) printf(", ");
    }
    printf("\n");

    return dp[n]; // Return nth Fibonacci
}

int main() {
    int n;
    printf("Enter n (up to 92): ");
    scanf("%d", &n);

    clock_t start = clock();

    long long result = nthFibonacci(n);

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("The %dth Fibonacci number is: %lld\n", n, result);
    printf("Time taken = %f seconds\n", time_taken);

    return 0;
}
