#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "NumberVector.h"
#include "StopWatch.h"
#include "FileManager.h"

void swap(int *a, int *b){ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}

void bubbleSort(int *v, int n){ 
    if (n < 1)return; 
 
    for (int i=0; i<n; i++) 
        if (v[i] > v[i+1]) 
            swap(&v[i], &v[i+1]);  
    bubbleSort(v, n-1); 
} 

int BinarySearch(numberVector_t numberVector, int element)
{
    int high = numberVector.vectorSize - 1;
    int low = 0;
    int mid;

    while (high > low){
        mid = (high + low) / 2;

        #ifdef DEBUG
            printf("mid: %d.\n", mid);
        #endif

        if (element == numberVector.numbers[mid]) return mid;
        else if (element > numberVector.numbers[mid]) low = mid + 1;
        else high = mid - 1;
    }

    return -1;
}

int main()
{
    numberVector_t numberVector;
    int nExecutions, vectorSize, element;
    double averageTime = 0.0;
    clock_t startTime, endTime;

    scanf("%d %d", &vectorSize, &nExecutions);

    numberVector = readNumberBinaryFile(vectorSize);

    bubbleSort(numberVector.numbers, numberVector.vectorSize);

    element = 1234567890;

    for (int i = 0; i < nExecutions; ++i)
    {
        startTime = clock();
        BinarySearch(numberVector, element);
        endTime = clock();

        #ifdef DEBUG
            printf("Elemento: %d, posição: %d.\n", element, BinarySearch(numberVector, element));
        #else
            averageTime+=getExecutionTime(startTime, endTime);
        #endif
    }

    #ifndef DEBUG
        averageTime = averageTime/(double)nExecutions;
        saveTimeToFile(vectorSize, averageTime, nExecutions);
    #endif

    free(numberVector.numbers);
}
