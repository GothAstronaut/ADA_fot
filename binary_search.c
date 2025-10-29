#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int binary_search(int arr[],int key,int n){
    int start=0;
    int end=n-1;
    while(start<=end){
        int mid = start + (end - start) / 2;
        if(arr[mid]==key) return mid;
        if(arr[mid]>key) end=mid-1;
        else start=mid+1;
    }
    return -1;
}

int generateRandomKey(int arr[],int n){
    int key=(rand()%n);
    return key;
}
int main(){
    // time complexity is O(logN) and the space complexity is O(1)
    srand(time(NULL));

    //double time_taken;
    int n;
    printf("Enter number of elements (n): ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
     if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    for(int i=0;i<n;i++){
        arr[i]=i+1;
    }
    clock_t start=clock();
    int keyy=generateRandomKey(arr,n);
    for(int i=0;i<1000000;i++){
    binary_search(arr,arr[keyy],n);
    }
    printf("The key is :-> %d \n",keyy);
    clock_t end=clock();
    double time_taken=((double)(end-start)/CLOCKS_PER_SEC);
    printf("Time taken to sort %d element : %f second \n",n,time_taken);
    free(arr);
    return 0;
}
