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
#include <stdio.h>
#include <time.h>
#include "graph.h"

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("cluster1.txt", "r");
    int numberOfNodes;

    if(!inFile){
    	printf("Fail to open file\n");
        return;
    }
    else
    	printf("Open file successfully!\n");
    
    fscanf(inFile, "%d", &numberOfNodes);
    printf("Number of nodes = %d\n", numberOfNodes);


    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}