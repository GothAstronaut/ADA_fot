#include <stdio.h>
#include <time.h>

void printFibonacci(int n) {
    if (n <= 0) {
        printf("Number of terms must be positive.\n");
        return;
    }

    long long t1 = 0, t2 = 1;  // first two terms
    printf("Fibonacci Series: ");

    for (int i = 1; i <= n; i++) {
        printf("%lld", t1);

        if (i < n) printf(", ");  // avoid trailing comma

        long long nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }

    printf("\n");
}

int main() {
    int terms;
    printf("Enter the number of terms (up to 92): ");
    scanf("%d", &terms);

    clock_t start, end;
    double cpu_time_used;

    start = clock();  // start measuring time

    printFibonacci(terms);

    end = clock();  // end measuring time

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Execution time: %f seconds\n", cpu_time_used);

    return 0;
}
