/*
    Clustering Algorithm:
        - Initially, each point in a separate cluster
        - Repeat until only k clusters:
            - Let p, q = closest pair of separated points (determines the current spacing)
            - Merge the clusters containing p & q into a single cluster.
    (Maximum spacing: the minimum distance between nodes in different clusters.)
    Number of clusters k = 4.
*/
/*
    Kruskal's MST Algorithm:
        - Sort edges in order of increasing cost. (O(mlog n), recall m = O(n^2) assuming non-parallel edges)
        - T = empty
            - For i = 1 to m (O(m) iterations)
                - If T U {i} has no cycles (O(n) time to check for cycle [Use BFS or DFS in the graph (V, T) which contains <= n - 1 edges])
                    - Add i to T
        - Return T
*/
/*
    Maximum spacing = 106.
    1. CPU: i5-6500
    Running time =  (sec).

    2. CPU: Duo E8400
    Running time = 0.197(sec).
*/
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
    FILE *inFile = fopen("clustering_big.txt", "r");
    int numberOfNodes, numberOfClusters, numberOfBitsPerLable, i = 0, j = 0;
    __int64 numberOfEdges, positionVertex1, positionVertex2;
    int *hammingVertex1, *hammingVertex2;
    int vertex1, vertex2, cost;
    
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
        positionVertex1 = (vertex1 * 49) - 39;
        fseek(inFile , positionVertex1, SEEK_SET);
        readHammingDistance(inFile, hammingVertex1, numberOfBitsPerLable);
//        printf("\nvertex1\n");
//        outputVertexInfo(vertex1, positionVertex1, hammingVertex1);
        for(vertex2 = vertex1 + 1; vertex2 <= numberOfNodes; vertex2++){
            positionVertex2 = (vertex2 * 49) - 39;
            fseek(inFile , positionVertex2, SEEK_SET);
            readHammingDistance(inFile, hammingVertex2, numberOfBitsPerLable);
//            outputVertexInfo(vertex2, positionVertex2, hammingVertex2);
            cost = decodeHammingDistance(hammingVertex1, hammingVertex2, numberOfBitsPerLable);
//            printf("\ncost = %d\n", cost);
            numberOfClusters = mergeOrNot(&vertices[vertex1], &vertices[vertex2], numberOfClusters, cost);
//            printf("numberOfClusters = %d\n", numberOfClusters);
//            if(numberOfClusters < numberOfNodes){
//                outputVertexInfo(vertex2, positionVertex2, hammingVertex2);
//                printf("\ncost = %d\n", cost);
//                return;
//            }
        }
    }

    printf("Number Of Clusters = %d", numberOfClusters);
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