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
__int64 maxValueRecursion(int item, int maxWeight, int *weight, int *value, max_value_head_p maximumValue);
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

    printf("Maximum Value = %lld\n", findMaxValue(inFile, knapsackSize, numberOfItems));

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

__int64 maxValueRecursion(int item, int maxWeight, int *weight, int *value, max_value_head_p maximumValue){
    if(item == 0 || maxWeight == 0)
        return 0;
    max_value_node_p newNodePtr;
    __int64 tempValue;
    if(weight[item] > maxWeight){
        tempValue = findValue(maximumValue, item - 1, maxWeight);
        if(tempValue > (maximumValue[item].head)->value){
            newNodePtr = createMaxValueNode(tempValue, maxWeight);
            newNodePtr->next = maximumValue[item].head;
            maximumValue[item].head = newNodePtr;
        }
        return (maximumValue[item].head)->value;
    }
    tempValue = max(findValue(maximumValue, item - 1, maxWeight), findValue(maximumValue, item - 1, maxWeight - weight[item]) + (__int64)value[item]);
    if(tempValue > (maximumValue[item].head)->value){
        newNodePtr = createMaxValueNode(tempValue, maxWeight);
        newNodePtr->next = maximumValue[item].head;
        maximumValue[item].head = newNodePtr;
    }
    return (maximumValue[item].head)->value;
}
int findMaxValue(FILE *inFile, int knapsackSize, int numberOfItems){
    int i = 1, item, maxWeight, *weight, *value;
    max_value_head_p maximumValue;
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
    /* Set default value in maximumValue */
    maximumValue = createMaxValueHead(numberOfItems);

    printf("Start recursion...\n\n");
    return maxValueRecursion(numberOfItems, knapsackSize, weight, value, maximumValue);
}