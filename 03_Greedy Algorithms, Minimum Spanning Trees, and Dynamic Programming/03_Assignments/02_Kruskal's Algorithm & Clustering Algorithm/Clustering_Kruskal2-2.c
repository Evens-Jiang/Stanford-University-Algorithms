#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "union_find.h"
    
void outputVertexInfo(int vertex, __int64 positionVertex, int *hammingVertex);
void readHammingDistance(FILE *inFile, int *hammingVertex, int length);
int decodeHammingDistance(int *hammingVertex1, int *hammingVertex2, int length);
int mergeOrNot(vertex_p vertex1, vertex_p vertex2, int numberOfClusters, int cost);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("test_case_part2.txt", "r");
    int numberOfNodes, numberOfClusters, numberOfBitsPerLable, i = 0, j = 0;
    __int64 numberOfEdges, positionVertex1, positionVertex2;
    int *hammingVertex1, *hammingVertex2;
    int vertex1, vertex2, cost, temp;
    
    if(!inFile){
    	printf("Fail to open file\n");
        return;
    }
    else
    	printf("Open file successfully!\n");
    
    fscanf(inFile, "%d %d", &numberOfNodes, &numberOfBitsPerLable);
    printf("Number of nodes = %d\nNumber of bits per lable = %d\n\n", numberOfNodes, numberOfBitsPerLable);
    
    numberOfClusters = numberOfNodes;
    
    if((hammingVertex1 = malloc(numberOfBitsPerLable * sizeof(int))) == NULL || (hammingVertex2 = malloc(numberOfBitsPerLable * sizeof(int))) == NULL){
        printf("Malloc hamming vertex failed.\n");
        return;
    }
    
    numberOfEdges = (__int64) numberOfNodes * (numberOfNodes - 1) / 2;
    printf("Number of edges = %lld\n", numberOfEdges);
    
    vertex_p vertices = malloc((numberOfNodes + 1) * sizeof(vertex_t));
    for(i = 0; i <= numberOfNodes; i++)
        MakeSet(&vertices[i]);
    
    for(vertex1 = 1; vertex1 <= numberOfNodes; vertex1++){
        positionVertex1 = (vertex1 * 21) - 15;
        fseek(inFile , positionVertex1, SEEK_SET);
        readHammingDistance(inFile, hammingVertex1, numberOfBitsPerLable);
//        printf("\nvertex1\n");
//        outputVertexInfo(vertex1, positionVertex1, hammingVertex1);
        for(vertex2 = vertex1 + 1; vertex2 <= numberOfNodes; vertex2++){
            positionVertex2 = (vertex2 * 21) - 15;
            fseek(inFile , positionVertex2, SEEK_SET);
            readHammingDistance(inFile, hammingVertex2, numberOfBitsPerLable);
//            outputVertexInfo(vertex2, positionVertex2, hammingVertex2);
            cost = decodeHammingDistance(hammingVertex1, hammingVertex2, numberOfBitsPerLable);
            temp = numberOfClusters;
            numberOfClusters = mergeOrNot(&vertices[vertex1], &vertices[vertex2], numberOfClusters, cost);
//            printf("numberOfClusters = %d\n", numberOfClusters);
           if(numberOfClusters < temp){
                printf("temp = %d\n", temp);
                printf("\ncost = %d\n", cost);
           }
        }
    }

    printf("Number Of Clusters = %d\n", numberOfClusters);
    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

void outputVertexInfo(int vertex, __int64 positionVertex, int *hammingVertex){
    printf("\nvertex = %3d position = %lld\n", vertex, positionVertex);
    int i = 0;
    for(i = 0; i < 24; i++)
        printf("%d ", hammingVertex[i]);
    return;
}
void readHammingDistance(FILE *inFile, int *hammingVertex, int length){
    int i = 0;
    for(i = 0; i < length; i++)
        fscanf(inFile, "%d", &hammingVertex[i]);
    return;
}
int decodeHammingDistance(int *hammingVertex1, int *hammingVertex2, int length){
    if (length == 0)
        return 0;

    if (hammingVertex1[length - 1] == hammingVertex2[length - 1])
        return decodeHammingDistance(hammingVertex1, hammingVertex2, length - 1);
    
    return 1 + decodeHammingDistance(hammingVertex1, hammingVertex2, length - 1);
}
int mergeOrNot(vertex_p vertex1, vertex_p vertex2, int numberOfClusters, int cost){
    if(cost >= 3)
        return numberOfClusters;
    return Union(vertex1, vertex2, numberOfClusters);
}