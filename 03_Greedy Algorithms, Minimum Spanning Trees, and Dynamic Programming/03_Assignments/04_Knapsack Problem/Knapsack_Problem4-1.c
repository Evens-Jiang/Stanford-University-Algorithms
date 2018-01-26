/*
    Knapsack Problem.
    Assume w1, w2, w3..., wn, W are strictly positive integers.
    Define m[i, w] to be the maximum value that can be attained with weight less than or equal to w using items up to i (first i items).
    We can define m[i, w] recursively as follows:
    * m[0, w] = 0.
    * m[i, w] = m[i - 1, w] if wi > w (the new item is more than the current weight limit)
    * m[i, w] = max(m[i - 1, w], m[i - 1, w - wi] + vi) if wi <= w 
    The solution can then be found by calculating m[n, W].
    
    Pseudocode:
        // Input:
        // Values (stored in array v)
        // Weights (stored in array w)
        // Number of distinct items (n)
        // Knapsack capacity (W)

        for j from 0 to W do:
            m[0, j] := 0

        for i from 1 to n do:
            for j from 0 to W do:
                if w[i] > j then:
                    m[i, j] := m[i-1, j]
                else:
                    m[i, j] := max(m[i-1, j], m[i-1, j-w[i]] + v[i])
*/
/*
    The maximum value = 2493893.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(x, y) (x > y) ? x : y;

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
        for(maxWeight = 0; maxWeight <= knapsackSize; maxWeight++)
            maximumValue[item][maxWeight] = 0;
    /* Iteration for subproblems */
    for(item = 1; item <= numberOfItems; item++)
        for(maxWeight = 0; maxWeight <= knapsackSize; maxWeight++){
            if(weight[item] > maxWeight)
                maximumValue[item][maxWeight] = maximumValue[item - 1][maxWeight];
            else
                maximumValue[item][maxWeight] = max(maximumValue[item - 1][maxWeight], maximumValue[item - 1][maxWeight - weight[item]] + value[item]);
        }
    
    printf("w\\i ");
    for(i = 0; i <= numberOfItems; i++)
        printf("%3d ", i);
    printf("\n\n");
    for(maxWeight = 0; maxWeight <= knapsackSize; maxWeight++){
        for(i = 0; i <= numberOfItems; i++){
            if(i == 0)
                printf("%3d ", maxWeight);
            printf("%3d ", maximumValue[i][maxWeight]);
        }
        printf("\n");
    }
    printf("\n");
    return maximumValue[numberOfItems][knapsackSize];
}