/*
    Maximum weight independent set
    { 1, 2, 3, 4, 17, 117, 517, 997 }
    Answer = 10100110.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct vertex_set{
    int vertex, weight;
}vertex_set_t, *vertex_set_p;

__int64 findMWIS(vertex_set_p vertices, int index, __int64 *weightRecord);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("mwis.txt", "r");
    int numberOfNodes, i = 0, *chosenPoints, check[] = {1,2,3,4,17,117,517,997};
    __int64 totalWeight = 0, *weightRecord;
    vertex_set_p vertices;
    
    if(!inFile){
    	printf("Fail to open file\n");
        return;
    }
    else
    	printf("Open file successfully!\n");
    
    fscanf(inFile, "%d", &numberOfNodes);
    printf("Number of Nodes = %d\n", numberOfNodes);
    
    if((vertices = malloc((numberOfNodes) * sizeof(vertex_set_t))) == NULL)
        printf("Malloc vertices failed.\n");
    if((weightRecord = malloc((numberOfNodes) * sizeof(__int64))) == NULL)
        printf("Malloc weightRecord failed.\n");
    for(i = 0; i < numberOfNodes; i++)
        weightRecord[i] = 0;
    
    for(i = 0; i < numberOfNodes; i++){
        fscanf(inFile, "%d", &vertices[i].weight);
        totalWeight += (__int64) vertices[i].weight;
        vertices[i].vertex = i;
    }

    printf("totalWeight = %lld\n", totalWeight);
    weightRecord[numberOfNodes - 1] = findMWIS(vertices, numberOfNodes - 1, weightRecord);
    printf("Max weight = %lld\n", weightRecord[numberOfNodes - 1]);

    /* Check chosen points */
    chosenPoints = malloc(numberOfNodes * sizeof(int));
    int ptr = numberOfNodes - 1;
    for (i = 0; i < numberOfNodes; i++)
        chosenPoints[i] = 0;
    while(i >= 0){
        if(i == 0){
            chosenPoints[ptr] = 1;
            break;
        }
        if(weightRecord[i - 1] > weightRecord[i - 2]){
            chosenPoints[ptr--] = i;
            i -= 2;
        }
        else
            i--;
    }
    /* Find match */
    int chosenPointsStart = 0, checkNumber = sizeof(check) / sizeof(int), flag = 0;
    while(chosenPoints[chosenPointsStart] != 0)
        chosenPointsStart++;
    for(ptr = 0; ptr < checkNumber; ptr++){
        for (i = chosenPointsStart; i < numberOfNodes; i++){
            if(chosenPoints[i] == check[ptr]){
                printf("1");
                flag = 1;
                break;
            }
        }
        if(flag == 0)
            printf("0");
        else
            flag = 0;
    }
    printf("\n");
    // printf("Chosen points = { ");
    // for (i = 0; i < numberOfNodes - 1; i++){
    //     if(chosenPoints[i] != 0)
    //         printf("%d, ", chosenPoints[i]);
    // }
    // printf("%d }\n", chosenPoints[i]);

    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

__int64 findMWIS(vertex_set_p vertices, int index, __int64 *weightRecord){
    if(index == 0){
        weightRecord[index] = (__int64)vertices[index].weight;
        return weightRecord[index];
    }
    __int64 weight1, weight2;
    if(index - 1 < 0)
        weight1 = 0;
    else if(weightRecord[index - 1] != 0)
        weight1 = weightRecord[index - 1];
    else{
        weightRecord[index - 1] = findMWIS(vertices, index - 1, weightRecord);
        weight1 = weightRecord[index - 1];
    }
    if(index - 2 < 0)
        weight2 = (__int64)vertices[index].weight;
    else if(weightRecord[index - 2] != 0)
        weight2 = (__int64)vertices[index].weight + weightRecord[index - 2];
    else{
        weightRecord[index - 2] = findMWIS(vertices, index - 2, weightRecord);
        weight2 = (__int64)vertices[index].weight + weightRecord[index - 2];
    }
    if(weight1 > weight2)
        return weight1;
    else
        return weight2;
}