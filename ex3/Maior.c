#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "NumberVector.h"
#include "StopWatch.h"
#include "FileManager.h"

int getLargestNumber(numberVector_t numberVector)
{
    int largestNumber = INT_MIN;
    int actualNumber;

    for(int i = 0; i < numberVector.vectorSize; ++i)
    {
        actualNumber = numberVector.numbers[i];
        if(actualNumber > largestNumber)
            largestNumber = actualNumber;
    }

    return largestNumber;
}

int main()
{
    numberVector_t numberVector;
    int nExecutions, vectorSize, largestNumber;
    double averageTime = 0.0;
    clock_t startTime, endTime;

    scanf("%d %d", &vectorSize, &nExecutions);

    numberVector = readNumberBinaryFile(vectorSize);

    for(int i = 0; i < nExecutions; ++i)
    {
        startTime = clock();
        largestNumber = getLargestNumber(numberVector);
        endTime = clock();
        #ifdef DEBUG
            printf("The largest number is: %d\n", largestNumber);
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
