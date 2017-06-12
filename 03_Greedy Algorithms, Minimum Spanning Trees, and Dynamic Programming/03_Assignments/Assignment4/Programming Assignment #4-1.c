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

    The maximum value = 2493893.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max(int a, int b);
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

int max(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

int findMaxValue(FILE *inFile, int knapsackSize, int numberOfItems){
    int i = 1, w = 0, **maximumValue, *weight, *value;
    
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
            printf("Malloc maximum value(%d knapsack size) failed.\n", i);
            return 0;
        }
    for(i = 0; i <= numberOfItems; i++)
        for(w = 0; w <= knapsackSize; w++)
            maximumValue[i][w] = 0;
    for(i = 1; i <= numberOfItems; i++)
        for(w = 0; w <= knapsackSize; w++){
            if(weight[i] > w)
                maximumValue[i][w] = maximumValue[i - 1][w];
            else
                maximumValue[i][w] = max(maximumValue[i - 1][w], maximumValue[i - 1][w - weight[i]] + value[i]);
        }
    return maximumValue[numberOfItems][knapsackSize];
}