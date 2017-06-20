#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bellman_ford.h"

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("g1.txt", "r");
    int numberOfVertices, numberOfEdges;
    
    if(!inFile){
    	printf("Fail to open file\n");
        return;
    }
    else
    	printf("Open file successfully!\n");
    
    fscanf(inFile, "%d %d", &numberOfVertices, &numberOfEdges);
    printf("Number of vertices = %d\n", numberOfVertices);
    printf("Number of edges = %d\n", numberOfEdges);

    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}