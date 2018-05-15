#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./sortsMethods.h"

#define MAX_SIZE 50000

int main(int argc, char *argv[]) {
    int arraySize = 1000,
        arr[arraySize],
        n = sizeof(arr)/sizeof(arr[0]),
        range = (200 - 1) + 1; 

    while(arraySize <= MAX_SIZE) {
        srand(time(NULL));    
        for (int i = 0; i < arraySize; i++) {
            arr[i] = rand() % range + 1;
        }

        printArray(arr, n);
        if(argc < 2) {
            printf("Missing parameter!!");
            return 0;
        } else if(strcmp(argv[1], "bubble") == 0) {
            bubbleSort(arr, n);
        } else if(strcmp(argv[1], "selection") == 0) {
            selectionSort(arr, n);
        } else if(strcmp(argv[1], "insertion") == 0) {
            insertionSort(arr, n);
        } else if(strcmp(argv[1], "quick") == 0) {
            quickSort(arr, 0, n-1);
        } else if(strcmp(argv[1], "merge") == 0) {
            mergeSort(arr, 0, n-1);
        }

        printf("Sorted array: \n");
        printArray(arr, n); 

        arraySize += 1000;
    }

    return 0;
}