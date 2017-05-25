/*
    Minimum Spanning Tree: Prim's algorithm
    Adjacency list
    Priority queue(heap)
    
    
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

void prim(graph_p graph, int numberOfNodes);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("edges.txt", "r");
    int numberOfNodes, numberOfEdges;
    int source, destination, cost, i = 0;
    
    if(!inFile){
    	printf("Fail to open file\n");
        return;
    }
    else
    	printf("Open file successfully!\n");
    
    fscanf(inFile, "%d %d", &numberOfNodes, &numberOfEdges);
    printf("Number of nodes = %d\n", numberOfNodes);
    printf("Number of edges = %d\n", numberOfEdges);
    /* create graph */
    graph_p graph = createGraph(numberOfNodes, UNDIRECTED);
    
    /* make adjacency list */
    while(fscanf(inFile, "%d %d %d", &source, &destination, &cost) != EOF)
        addEdge(graph, source, destination, cost);
    
    displayGraph(graph);
    destroyGraph(graph);
    
    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

void prim(graph_p graph, int numberOfNodes){
    int source = 1;
    int distance[numberOfNodes] = 10000, parent[numberOfNodes];
    bool visited[numberOfNodes] = FALSE;
    
    distance[source] = 0;
    parent[source] = source;
    
    
}