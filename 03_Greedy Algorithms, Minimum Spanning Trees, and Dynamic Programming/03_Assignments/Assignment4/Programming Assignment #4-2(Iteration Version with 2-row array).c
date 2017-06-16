/*
    Knapsack Problem.
    Assume w1, w2, w3..., wn, W are strictly positive integers.
    Define m[i, w] to be the maximum value that can be attained with weight less than or equal to w using items up to i (first i items).
    We can define m[i, w] recursively as follows:
    * m[0, w] = 0.
    * m[i, w] = m[i - 1, w] if wi > w (the new item is more than the current weight limit)
    * m[i, w] = max(m[i - 1, w], m[i - 1, w - wi] + vi) if wi <= w 
    The solution can then be found by calculating m[n, W].
    
    * Pseudocode:
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
    * 2 row array trick:
        int current = 1;
        if w[i] <= j then
          m[current, j] := max(m[1 - current, j], m[1 - current, j-w[i]] + v[i])
        else
          m[i, j] := m[1 - current, j]
        end if
        current = 1 - current;
*/
/*
    CPU: Duo E8400 
    Maximum Value = 4243395
    Running time = 51.839 (sec)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(x, y) (x > y) ? x : y;

int findMaxValue(FILE *inFile, int knapsackSize, int numberOfItems);  

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("knapsack_big.txt", "r");
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
    if((maximumValue = malloc(2 * sizeof(int*))) == NULL){
        printf("Malloc maximum value(items) failed.\n");
        return 0;
    }
    for(i = 0; i < 2; i++)
        if((maximumValue[i] = malloc((knapsackSize + 1) * sizeof(int))) == NULL){
            printf("Malloc maximum value(maximumValue[%d]) failed.\n", i);
            return 0;
        }
    /* Set default value in maximumValue */
    for(item = 0; item < 2; item++)
        for(maxWeight = 0; maxWeight <= knapsackSize; maxWeight++)
            maximumValue[item][maxWeight] = 0;
    /* Iteration for subproblems */
    for(item = 1; item <= numberOfItems; item++)
        for(maxWeight = 0; maxWeight <= knapsackSize; maxWeight++){
            if(weight[item] > maxWeight)
                maximumValue[item % 2][maxWeight] = maximumValue[(item - 1) % 2][maxWeight];
            else
                maximumValue[item % 2][maxWeight] = max(maximumValue[(item - 1) % 2][maxWeight], maximumValue[(item - 1) % 2][maxWeight - weight[item]] + value[item]);
        }
    
    return max(maximumValue[0][knapsackSize], maximumValue[1][knapsackSize]);
}