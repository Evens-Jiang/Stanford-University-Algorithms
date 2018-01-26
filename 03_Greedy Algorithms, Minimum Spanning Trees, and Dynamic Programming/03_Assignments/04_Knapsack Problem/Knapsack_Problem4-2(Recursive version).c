#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(x, y) (x > y) ? x : y;

int maxValueRecursion(int item, int maxWeight, int *weight, int *value);
int findMaxValue(FILE *inFile, int knapsackSize, int numberOfItems);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("knapsack1.txt", "r");
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

    printf("Maximum Value = %d\n", findMaxValue(inFile, knapsackSize, numberOfItems));

    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

int maxValueRecursion(int item, int maxWeight, int *weight, int *value){
    if(item == 0 || maxWeight == 0)
        return 0;
    if(weight[item] > maxWeight){
        return maxValueRecursion(item - 1, maxWeight, weight, value);
    }
    return max(maxValueRecursion(item - 1, maxWeight, weight, value), maxValueRecursion(item - 1, maxWeight - weight[item], weight, value) + value[item]);
}
int findMaxValue(FILE *inFile, int knapsackSize, int numberOfItems){
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
    return maxValueRecursion(numberOfItems, knapsackSize, weight, value);
}