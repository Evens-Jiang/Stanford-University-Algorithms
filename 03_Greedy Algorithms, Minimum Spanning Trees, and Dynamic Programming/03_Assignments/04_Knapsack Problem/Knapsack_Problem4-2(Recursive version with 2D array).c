/*
    Knapsack Problem.
    Assume w1, w2, w3..., wn, W are strictly positive integers.
    Define m[i, w] to be the maximum value that can be attained with weight less than or equal to w using items up to i (first i items).
    We can define m[i, w] recursively as follows:
    * m[0, w] = 0.
    * m[i, w] = m[i - 1, w] if wi > w (the new item is more than the current weight limit)
    * m[i, w] = max(m[i - 1, w], m[i - 1, w - wi] + vi) if wi <= w 
    The solution can then be found by calculating m[n, W].
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(x, y) (x > y) ? x : y;

int maxValueRecursion(int item, int maxWeight, int *weight, int *value, int **maximumValue);
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

int maxValueRecursion(int item, int maxWeight, int *weight, int *value, int **maximumValue){
    if(maximumValue[item][maxWeight] != -1)
        return maximumValue[item][maxWeight];
    if(item == 0 || maxWeight == 0)
        return 0;
    if(weight[item] > maxWeight){
        maximumValue[item][maxWeight] = maxValueRecursion(item - 1, maxWeight, weight, value, maximumValue);
        return maximumValue[item][maxWeight];
    }
    maximumValue[item][maxWeight] = max(maxValueRecursion(item - 1, maxWeight, weight, value, maximumValue), maxValueRecursion(item - 1, maxWeight - weight[item], weight, value, maximumValue) + value[item]);
    return maximumValue[item][maxWeight];
}
int findMaxValue(FILE *inFile, int knapsackSize, int numberOfItems){
    int i = 1, item, maxWeight, **maximumValue, *weight, *value;
    
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
    if((maximumValue = malloc((numberOfItems + 1) * sizeof(int*))) == NULL){
        printf("Malloc maximum value(items) failed.\n");
        return 0;
    }
    for(i = 0; i <= numberOfItems; i++)
        if((maximumValue[i] = malloc((knapsackSize + 1) * sizeof(int))) == NULL){
            printf("Malloc maximum value(maximumValue[%d]) failed.\n", i);
            return 0;
        }
    /* Set default value in maximumValue */
    for(item = 0; item <= numberOfItems; item++)
        for(maxWeight = 0; maxWeight <= knapsackSize; maxWeight++){
            if(item == 0 || maxWeight == 0)
                maximumValue[item][maxWeight] = 0;
            else
                maximumValue[item][maxWeight] = -1;
        }

    printf("Start recursion...\n\n");
    return maxValueRecursion(numberOfItems, knapsackSize, weight, value, maximumValue);
}