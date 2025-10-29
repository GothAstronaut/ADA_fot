#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
// Swap func on 
void swap(int *a, int *b) { 
int temp = *a; 
*a = *b; 
*b = temp; 
} 
// Par on func on 
int partition(int arr[], int low, int high) { 
int pivot = arr[high];   
    int i = (low - 1); 
    for (int j = low; j < high; j++) { 
        if (arr[j] <= pivot) { 
            i++; 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
 
// Quick Sort func on 
void quick_sort(int arr[], int low, int high) { 
    if (low < high) { 
        int pi = partition(arr, low, high); 
        quick_sort(arr, low, pi - 1); 
        quick_sort(arr, pi + 1, high); 
    } 
} 
 
// Func on to generate random array 
void generateRandomArray(int arr[], int n) { 
    for (int i = 0; i < n; i++) { 
        arr[i] = rand() % 100000;  // Random numbers up to 1e5 
    } 
} 
 
int main() { 
    int n; 
    printf ("Enter the number of elements: "); 
    scanf("%d", &n); 
 
    int *arr = (int *)malloc(n * sizeof(int)); 
    if (arr == NULL) { 
        printf ("Memory alloca on failed\n"); 
        return 1; 
    } 
 
    generateRandomArray(arr, n); 
 
    // Run mul ple mes to get average 
    clock_t start = clock(); 
    for (int i = 0; i < 100; i++) { 
        // Need fresh random array each me 
generateRandomArray(arr, n); 
quick_sort(arr, 0, n - 1); 
} 
clock_t end = clock(); 
double me_taken = ((double)(end - start) / 
CLOCKS_PER_SEC) / 100.0; 
printf ("Time taken to sort %d elements (average over 100 runs): %f seconds\n", n, me_taken); 
free(arr); 
return 0; 
}