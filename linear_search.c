#include <stdio.h>
#include<stdlib.h>
#include<time.h>
void RandomArray(int arr[],int n){
    for(int i=0;i<n;i++){
        arr[i]=rand()%100000;
    }
}
int RandomKey(int n){
    int rnd=rand()%n;
    return rnd;
}
int search(int arr[], int n, int x) {
    for (int i = 0; i < n; i++)
        if (arr[i] == x)
            return i;
    return -1;
}
int main(void) {
    srand(time(NULL));

    int n;
    printf("Enter the Number _");
    scanf("%d",&n);
    int *arr=(int*)malloc(sizeof(int)*n);
        if(arr==NULL){
        printf("Memory allocation failed \n");
        return 1;
    }
    RandomArray(arr,n);
    int key=RandomKey(n);
    clock_t start=clock();
    for(int i=0;i<10000;i++){
        search(arr, n,arr[key]);
    }
    clock_t end=clock();
    double time_taken=((double)(end-start)/CLOCKS_PER_SEC);
    printf("Time taken to Search %d element : %f second \n",n,time_taken);
    free(arr);
    return 0;
}
