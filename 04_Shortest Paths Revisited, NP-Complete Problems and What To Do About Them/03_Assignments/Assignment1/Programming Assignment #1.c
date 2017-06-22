/*
    Bellman-Ford Algorithm.
    All-pairs shortest path algorithm.
    
    g1 & g2 both have negative cycles.
    Shortest path of g3 = -19.
    
    1. CPU: i5-6500
        Running time =  (sec)
	2. CPU: Duo E8400
        Running time = 11.478 (sec)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bellman_ford.h"
#include "floyd_warshall.h"

void main(void){
    clock_t begin = clock();
    int k = 0;
    char graphFile[3][7] = {"g1.txt", "g2.txt", "g3.txt"};
    for(k = 0; k < 3; k++){
        FILE *inFile = fopen(graphFile[k], "r");
        int numberOfVertices, numberOfEdges;
        int vertexU, vertexV, weight, i = 0;
        graph_p graph;
        
        if(!inFile){
            printf("Fail to open %s\n", graphFile[k]);
            return;
        }
        else
            printf("Open %s successfully!\n", graphFile[k]);

        fscanf(inFile, "%d %d", &numberOfVertices, &numberOfEdges);
        printf("Number of vertices = %d\n", numberOfVertices);
        printf("Number of edges = %d\n", numberOfEdges);

        graph = createGraph(numberOfVertices, numberOfEdges);

        while(fscanf(inFile, "%d %d %d", &vertexU, &vertexV, &weight) != EOF){
            addEdge(graph, vertexU, vertexV, weight, i);
            i++;
        }

        if(bellmanFord(graph, 1))
            printf("Shortest path of %s = %lld\n", graphFile[k], floydWarshall(graph));
        killGraph(graph);

        fclose(inFile);
    }
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}