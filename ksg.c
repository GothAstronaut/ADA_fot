#include <stdio.h>
#include <stdlib.h>

// Structure for an item
struct Item {
    int weight;
    int value;
};

// Comparator for qsort (sort by value/weight ratio descending)
int compare(const void *a, const void *b) {
    struct Item *item1 = (struct Item *)a;
    struct Item *item2 = (struct Item *)b;
    double r1 = (double)item1->value / item1->weight;
    double r2 = (double)item2->value / item2->weight;
    return (r2 > r1) - (r2 < r1);  // equivalent to (r2 - r1) but safe for double
}

// Greedy Knapsack function
double fractionalKnapsack(int W, struct Item arr[], int n) {
    // Sort items by value/weight ratio
    qsort(arr, n, sizeof(struct Item), compare);

    double totalValue = 0.0;
    int currWeight = 0;

    for (int i = 0; i < n; i++) {
        if (currWeight + arr[i].weight <= W) {
            // Take the whole item
            currWeight += arr[i].weight;
            totalValue += arr[i].value;
        } else {
            // Take fraction of the item
            int remain = W - currWeight;
            totalValue += arr[i].value * ((double)remain / arr[i].weight);
            break; // Knapsack full
        }
    }

    return totalValue;
}

int main() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    struct Item items[n];
    printf("Enter weight and value of each item:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &items[i].weight, &items[i].value);
    }

    double maxValue = fractionalKnapsack(W, items, n);
    printf("Maximum value in Knapsack = %.2f\n", maxValue);

    return 0;
}

