#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "NumberVector.h"
#include "StopWatch.h"
#include "FileManager.h"

int LinearSearch(numberVector_t numberVector, int element)
{
    int vectorSize = numberVector.vectorSize;

    for (int i = 0; i < vectorSize; ++i)
        if (element == numberVector.numbers[i])
            return i;
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

    element = 1234567890;

    for (int i = 0; i < nExecutions; ++i)
    {
        startTime = clock();
        LinearSearch(numberVector, element);
        endTime = clock();

        #ifdef DEBUG
            printf("Elemento: %d, posição: %d.\n", element, LinearSearch(numberVector, element));
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
