#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 50000
#define NUMBER_SAMPLES 10

long long int compOB = 0, swapOB = 0, callCount = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
//--------------------------------------------------------------------------------------------

void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++){
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++){
            compOB++;
            if (arr[j] > arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
                swapOB++;
            }
        }
    }
}
//--------------------------------------------------------------------------------------------

void selectionSort(int arr[], int n) {
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++) {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          compOB++;
          if (arr[j] < arr[min_idx])
            min_idx = j;
 
        // Swap the found minimum element with the first element
        swapOB++;
        swap(&arr[min_idx], &arr[i]);
    }
}
//--------------------------------------------------------------------------------------------

void insertionSort(int arr[], int n) {
   int i, key, j;
   for (i = 1; i < n; i++) {
        key = arr[i];
        j = i-1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        compOB++;
        while (j >= 0 && arr[j] > key){
           compOB++;
           swapOB++; 
           arr[j+1] = arr[j];
           j = j-1;
        }
        arr[j+1] = key;
   }
}
//--------------------------------------------------------------------------------------------

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int arr[], int low, int high) {
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        compOB++;
        if (arr[j] <= pivot) {
            i++;    // increment index of smaller element
            swapOB++;
            swap(&arr[i], &arr[j]);
        }
    }
    swapOB++;
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        callCount++;
        quickSort(arr, low, pi - 1);
        callCount++;
        quickSort(arr, pi + 1, high);
    }
}
//--------------------------------------------------------------------------------------------
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
     
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    compOB++;
    while (i < n1 && j < n2) {
        compOB+=2;
        if (L[i] <= R[j]) {
            swapOB++;
            arr[k] = L[i];
            i++;
        }
        else {
            compOB++;
            swapOB++;
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    compOB++;
    while (i < n1) {
        compOB++;
        swapOB++;
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    compOB++;
    while (j < n2) {
        compOB++;
        swapOB++;
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        callCount++;
        mergeSort(arr, l, m);
        callCount++;
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}
//--------------------------------------------------------------------------------------------
void printArray(int arr[], int size) {
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/*execucao do algoritmo via linha de comando com passagem de parametros
    ex: ./executavel.x [busca] [vetor]
        ./executavel.x bubble average
    
    para os algoritmos de busca: bubble, selection, insertion, quick e merge
    vetores: best, average, worst
*/

int main(int argc, char *argv[]) {
    FILE *results;
    int arraySize = 1000;
    
    results = fopen("output.txt", "w");
    
    if(!results) {
        printf("ERRO\n");
        return 1;
    }

    while (arraySize <= MAX_SIZE) {    
        printf("Tamanho do vetor -> %d\n", arraySize);

        int arr[arraySize],
            n = sizeof(arr) / sizeof(arr[0]),
            range = (1000 - 1) + 1;

        for(int i = 0; i < NUMBER_SAMPLES; i++){
            srand(time(NULL));
            
            /*==================================================================================
            *   GERACAO DOS VETORES DE TESTES
            * ==================================================================================*/
            if(strcmp(argv[2],"average") == 0){
                for (int j = 0; j < arraySize; j++) {
                    arr[j] = rand() % range + 1;
                }
            }

            else if(strcmp(argv[2],"best") == 0){ //gera ordenado menor para maior
                for (int j = 0; j < arraySize; j++) {
                    arr[j] = j;
                }
            }

            else if(strcmp(argv[2],"worst") == 0){ //ordenado maior para menor
                int k = arraySize;
                for (int j = 0; j < arraySize; j++) {
                    arr[j] = k;
                    k--;
                }
            }

            /* ==================================================================================*/

            /*==================================================================================
            *   EXECUCAO METODOS DE ORDENACAO
            * ==================================================================================*/
            if(i == 0) fprintf (results, "tamanho do vetor -> %d\n", arraySize);
            if(strcmp(argv[1], "bubble") == 0){
                bubbleSort(arr, n);
                fprintf(results, "%lld %lld\n", compOB, swapOB);
            }
            else if(strcmp(argv[1], "selection") == 0) {
                selectionSort(arr, n);
                fprintf(results, "%lld %lld\n", compOB, swapOB);                
            }
            else if(strcmp(argv[1], "insertion") == 0) {
                insertionSort(arr, n);
                fprintf(results, "%lld %lld\n", compOB, swapOB);                
            }
            else if(strcmp(argv[1], "quick") == 0) {
                callCount++;
                quickSort(arr, 0, n - 1); 
                long long int total = callCount * (swapOB + compOB);
                fprintf(results, "%lld\n", total);
            }
            else if(strcmp(argv[1], "merge") == 0) {
                callCount++;
                mergeSort(arr, 0, n-1);
                long long int total = callCount * (swapOB + compOB);
                fprintf(results, "%lld\n", total);
            }
            /* ==================================================================================*/  
            compOB = 0;
            swapOB = 0;  
            callCount = 0;
        }

        arraySize += 1000;
    }
    fclose(results);
    return 0;
}