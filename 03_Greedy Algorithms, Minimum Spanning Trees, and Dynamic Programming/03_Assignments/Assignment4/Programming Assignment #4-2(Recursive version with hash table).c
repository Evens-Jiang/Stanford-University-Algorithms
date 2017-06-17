/*
    Knapsack Problem.
    (Need to change data structure.Too slow.)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(x, y) (x > y) ? x : y;
#define prime1 97 
#define prime2 101

int maxValueRecursion(int item, int maxWeight, int *weight, int *value, int **hashTable, int ***checkHash);
int findMaxValue(FILE *inFile, int knapsackSize, int numberOfItems);

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

    printf("Maximum Value = %d\n", findMaxValue(inFile, knapsackSize, numberOfItems));

    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

int maxValueRecursion(int item, int maxWeight, int *weight, int *value, int **hashTable, int ***checkHash){
    if(item == 0 || maxWeight == 0){
        return 0;
    }
    int x = item % prime1, y = maxWeight % prime2, checkX = item / prime1, checkY = maxWeight / prime2;
    if(checkX == checkHash[x][y][0] && checkY == checkHash[x][y][1]){
        return hashTable[x][y];
    }
    if(weight[item] > maxWeight){
        hashTable[x][y] = maxValueRecursion(item - 1, maxWeight, weight, value, hashTable, checkHash);
        checkHash[x][y][0] = checkX;
        checkHash[x][y][1] = checkY;
        return hashTable[x][y];
    }
    hashTable[x][y] = max(maxValueRecursion(item - 1, maxWeight, weight, value, hashTable, checkHash), maxValueRecursion(item - 1, maxWeight - weight[item], weight, value, hashTable, checkHash) + value[item]);
    checkHash[x][y][0] = checkX;
    checkHash[x][y][1] = checkY;
    return hashTable[x][y];
}
int findMaxValue(FILE *inFile, int knapsackSize, int numberOfItems){
    int i = 1, j, *weight, *value, **hashTable, ***checkHash;
    
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

    if((hashTable = malloc(prime1 * sizeof(int*))) == NULL){
        printf("Malloc hashTable(i) failed.\n");
        return 0;
    }
    if((checkHash = malloc(prime1 * sizeof(int**))) == NULL){
        printf("Malloc checkHash(i) failed.\n");
        return 0;
    }

    for(i = 0; i < prime1; i++){
        if((hashTable[i] = malloc(prime2 * sizeof(int))) == NULL){
            printf("Malloc hashTable[%d] failed.\n", i);
            return 0;
        }
        if((checkHash[i] = malloc(prime2 * sizeof(int*))) == NULL){
            printf("Malloc checkHash[%d] failed.\n", i);
            return 0;
        }
    }
    for (i = 0; i < prime1; i++)
        for (j = 0; j < prime2; j++)
            if((checkHash[i][j] = malloc(2 * sizeof(int))) == NULL){
                printf("Malloc checkHash[%d][%d] failed.\n", i, j);
                return 0;
            }
    /* Set default value in hashTable & checkHash */
    for (i = 0; i < prime1; i++)
        for (j = 0; j < prime2; j++)
            hashTable[i][j] = checkHash[i][j][0] = checkHash[i][j][1] = -1;

    printf("Start recursion...\n\n");
    return maxValueRecursion(numberOfItems, knapsackSize, weight, value, hashTable, checkHash);
}