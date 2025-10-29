#include<stdio.h> 
#include<stdlib.h> 
#include<time.h> 
//.clock() returns the CPU me your program has used , measures in clock ticks (not in sec) 
//.CLOCKS_PER_SEC tells you how many cks correspond to one sec so you can convert the value from clock() into sec 
void merge(int arr[],int le ,int mid,int right){ 
int i,j,k; 
int n1=mid-le +1; 
int n2=right-mid; 
    int *L=(int*)malloc(n1*sizeof(int)); 
    int *R=(int*)malloc(n2*sizeof(int)); 
    for(i=0;i<n1;i++){ 
        L[i]=arr[le +i]; 
    } 
    for(j=0;j<n2;j++){ 
        R[j]=arr[mid+1+j]; 
    } 
    k=le ; 
    i=0,j=0; 
    while(i<n1 && j<n2){ 
        if(L[i]<=R[j]){ 
            arr[k]=L[i]; 
            i++; 
        } 
        else{ 
            arr[k]=R[j]; 
            j++; 
        } 
        k++; 
    } 
    while(i<n1){ 
        arr[k]=L[i]; 
        i++; 
        k++; 
    } 
    while(j<n2){ 
        arr[k]=R[j]; 
        j++; 
        k++; 
    } 
    free(L); 
    free(R); 
 
} 
 
void merge_sort(int arr[],int lo,int hi){ 
    if(lo<hi){ 
        int mid=(lo+hi)/2; 
        merge_sort(arr,lo,mid); 
        merge_sort(arr,mid+1,hi); 
        merge(arr,lo,mid,hi); 
    } 
 
} 
void generateRandomArray(int arr[],int n){ 
    for(int i=0;i<n;i++){ 
        arr[i]=rand()%100000; 
    } 
} 
int main(){ 
    int n; 
    printf ("Enter the Number _"); 
    scanf("%d",&n); 
 
    int *arr=(int*)malloc(n*sizeof(int)); 
    if(arr==NULL){ 
        printf ("Memory allocation failed \n"); 
        return 1; 
    } 
 
    generateRandomArray(arr,n); 
    clock_t start=clock(); // clock_t is data type 
    for(int i=0;i<100;i++){ 
        merge_sort(arr,0,n-1); 
    } 
    clock_t end=clock(); 
    double me_taken=((double)(end-start)/CLOCKS_PER_SEC/100.0); 
    printf ("Time taken to sort %d element : %f second \n",n, me_taken); 
    free(arr); 
    return 0; 
} 
