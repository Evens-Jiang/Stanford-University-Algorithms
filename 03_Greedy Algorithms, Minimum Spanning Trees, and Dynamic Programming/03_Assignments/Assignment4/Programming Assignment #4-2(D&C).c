/*
    Knapsack Problem using divide and conquer strategy.
    https://www.cs.colostate.edu/~cs575dl/Sp2015/Lectures/Knapsack.pdf
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

__int64 maxValueRecursion(int item1, int item2, int maxWeight, int *weight, int *value);
__int64 findMaxValue(FILE *inFile, int knapsackSize, int numberOfItems);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("knapsack2.txt", "r");
    int knapsackSize, numberOfItems;
    
    if(!inFile){
    	printf("Fail to open file\n");
        return;
    }
    else
    	printf("Open file successfully!\n");
    
    fscanf(inFile, "%d %d", &knapsackSize, &numberOfItems);
    printf("Knapsack Size = %d\n", knapsackSize);
    printf("Number Of Items = %d\n", numberOfItems);

    printf("Maximum Value = %lld\n", findMaxValue(inFile, knapsackSize, numberOfItems));

    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

__int64 maxValueRecursion(int item1, int item2, int maxWeight, int *weight, int *value){
    int numberOfItems = item2 - item1 + 1, i = 0, halfNumberOfItem = (numberOfItems - 1) / 2 + item1;
    __int64 tempValue = 0, resultValue = 0;
    if(numberOfItems <= 0 || maxWeight == 0)
        return 0;
    if(numberOfItems == 1 && weight[item1] > maxWeight)
        return 0;
    if(numberOfItems == 1 && weight[item1] <= maxWeight)
        return (__int64) value[item1];
    for(i = 1; i < maxWeight; i++){
        tempValue = maxValueRecursion(item1, halfNumberOfItem, i, weight, value) + maxValueRecursion(halfNumberOfItem + 1, item2, maxWeight - i, weight, value);
        if(tempValue > resultValue)
            resultValue = tempValue;
    }
    printf("%2d %2d %2d %d\n", item1, item2, maxWeight, resultValue);
    return resultValue;
}
__int64 findMaxValue(FILE *inFile, int knapsackSize, int numberOfItems){
    int i = 1, item, maxWeight, *weight, *value;
    if((weight = malloc((numberOfItems + 1) * sizeof(int))) == NULL){
        printf("Malloc weight failed.\n");
        return 0;
    }
    if((value = malloc((numberOfItems + 1) * sizeof(int))) == NULL){
        printf("Malloc value failed.\n");
        return 0;
    }
    value[0] = weight[0] = 0;
    while(fscanf(inFile, "%d %d", &value[i], &weight[i]) != EOF)
        i++;

    printf("Start recursion...\n\n");
    return maxValueRecursion(1, numberOfItems, knapsackSize, weight, value);
}