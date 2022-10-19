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

int reverseTheOrder(numberVector_t numberVector)
{
    int vectorSize = numberVector.vectorSize;

    for(int i = 0; i < vectorSize/2; ++i)
    {
        swap((numberVector.numbers+i), (numberVector.numbers+vectorSize-i));
    }

    return 1;
}

int main()
{
    numberVector_t numberVector;
    int nExecutions, vectorSize;
    double averageTime = 0.0;
    clock_t startTime, endTime;

    scanf("%d %d", &vectorSize, &nExecutions);

    numberVector = readNumberBinaryFile(vectorSize);

    for(int i = 0; i < nExecutions; ++i)
    {
        #ifdef DEBUG
            printf("Primeiros da lista antes: %d, %d, %d.\n",numberVector.numbers[0], numberVector.numbers[1], numberVector.numbers[2]);
        #endif

        startTime = clock();
        reverseTheOrder(numberVector);
        endTime = clock();

        #ifdef DEBUG
            printf("Primeiros da lista depois: %d, %d, %d.\n",numberVector.numbers[0], numberVector.numbers[1], numberVector.numbers[2]);
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
