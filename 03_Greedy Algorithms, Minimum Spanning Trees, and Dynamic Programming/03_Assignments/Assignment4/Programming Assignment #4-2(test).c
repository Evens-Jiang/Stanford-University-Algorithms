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
                    
    Maximum Value = 4243395
    Running time = 20714.998 (sec)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(x, y) (x > y) ? x : y;

typedef struct max_value_node{
    int weight;
    __int64 value;
    struct max_value_node *next;
}max_value_node_t, *max_value_node_p;

typedef struct max_value_head{
    int numberOfNode;
    max_value_node_p head;
}max_value_head_t, *max_value_head_p;

max_value_node_p createMaxValueNode(int value, int weight);
max_value_head_p createMaxValueHead(int numberOfItems);
__int64 findValue(max_value_head_p maximumValue, int item, int maxWeight);
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

max_value_node_p createMaxValueNode(int value, int weight){
    max_value_node_p newNode = malloc(sizeof(max_value_node_t));
    newNode->value = value;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

max_value_head_p createMaxValueHead(int numberOfItems){
    max_value_head_p newHead;
    if((newHead = malloc((numberOfItems + 1) * sizeof(max_value_head_t))) == NULL){
        printf("Malloc max value head array failed.\n");
        return 0;
    }
    int i = 0;
    for(i = 0; i <= numberOfItems; i++){
        newHead[i].numberOfNode = 1;
        newHead[i].head = createMaxValueNode(0, 0);
    }
    return newHead;
}

__int64 findValue(max_value_head_p maximumValue, int item, int maxWeight){
    if(item == 0 || maxWeight == 0)
        return 0;
    max_value_node_p nodePtr = maximumValue[item].head;
    while(nodePtr->weight > maxWeight && nodePtr->next != NULL)
        nodePtr = nodePtr->next;
    return nodePtr->value;
}

int findMaxValue(FILE *inFile, int knapsackSize, int numberOfItems){
    int i = 1, item, maxWeight, *weight, *value, tempValue;
    max_value_head_p maximumValue;
    max_value_node_p newNodePtr;
    
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
    maximumValue = createMaxValueHead(numberOfItems);

    for(item = 1; item <= numberOfItems; item++)
        for(maxWeight = 0; maxWeight <= knapsackSize; maxWeight++){
            if(weight[item] > maxWeight){
                tempValue = findValue(maximumValue, item - 1, maxWeight);
                if(tempValue > (maximumValue[item].head)->value){
                    newNodePtr = createMaxValueNode(tempValue, maxWeight);
                    newNodePtr->next = maximumValue[item].head;
                    maximumValue[item].head = newNodePtr;
                }
            }
            else{
                tempValue = max(findValue(maximumValue, item - 1, maxWeight), findValue(maximumValue, item - 1, maxWeight - weight[item]) + (__int64)value[item]);
                if(tempValue > (maximumValue[item].head)->value){
                    newNodePtr = createMaxValueNode(tempValue, maxWeight);
                    newNodePtr->next = maximumValue[item].head;
                    maximumValue[item].head = newNodePtr;
                }
            }
        }
//    printf("w\\i ");
//    for(i = 0; i <= numberOfItems; i++)
//        printf("%3d ", i);
//    printf("\n\n");
//    for(maxWeight = 0; maxWeight <= knapsackSize; maxWeight++){
//        for(i = 0; i <= numberOfItems; i++){
//            if(i == 0)
//                printf("%3d ", maxWeight);
//            printf("%3d ", maximumValue[i][maxWeight]);
//        }
//        printf("\n");
//    }
//    printf("\n");
    
    return (maximumValue[numberOfItems].head)->value;
}