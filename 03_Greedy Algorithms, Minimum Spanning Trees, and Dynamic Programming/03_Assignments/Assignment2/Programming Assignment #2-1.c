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

#define CLUSTER 4

void swap_edges(edge_t *a, edge_t *b);
int partition(edge_p edges, int left, int right, int pivotIndex);
int medianOfThree(edge_p edges, int left, int right);
void quickSort(edge_p edges, int left, int right);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("clustering1.txt", "r");
    int numberOfNodes, numberOfEdges, numberOfClusters, i = 0;
    int vertex1, vertex2, cost;
    
    if(!inFile){
    	printf("Fail to open file\n");
        return;
    }
    else
    	printf("Open file successfully!\n");
    
    fscanf(inFile, "%d", &numberOfNodes);
    printf("Number of nodes = %d\n", numberOfNodes);
    
    numberOfEdges = numberOfNodes * (numberOfNodes - 1) / 2;
    edge_p edges = malloc(numberOfEdges * sizeof(edge_t));
    while(fscanf(inFile, "%d %d %d", &vertex1, &vertex2, &cost) != EOF){
        edges[i].vertex1 = vertex1;
        edges[i].vertex2 = vertex2;
        edges[i].cost = cost;
        i++;
    }
    
    quickSort(edges, 0, numberOfEdges - 1);

    vertex_p vertices = malloc((numberOfNodes + 1) * sizeof(vertex_t));
    for(i = 0; i <= numberOfNodes; i++)
        MakeSet(&vertices[i]);
    
    numberOfClusters = numberOfNodes;
    i = 0;
    while(numberOfClusters >= CLUSTER && i < numberOfEdges){
//        printf("edge cost = %d\n", edges[i].cost);
//        printf("vertex1 = %d vertex2 = %d\n", edges[i].vertex1, edges[i].vertex2);
        numberOfClusters = Union(&vertices[edges[i].vertex1], &vertices[edges[i].vertex2], numberOfClusters);
//        printf("vertices[%3d] = %p rank = %d\n", edges[i].vertex1, &vertices[edges[i].vertex1], vertices[edges[i].vertex1].rank);
//        printf("vertices[%3d].parent = %p rank = %d\n", edges[i].vertex1, Find(&vertices[edges[i].vertex1]), (Find(&vertices[edges[i].vertex1]))->rank);
//        printf("vertices[%3d] = %p rank = %d\n", edges[i].vertex2, &vertices[edges[i].vertex2], vertices[edges[i].vertex2].rank);
//        printf("vertices[%3d].parent = %p rank = %d\n", edges[i].vertex2, Find(&vertices[edges[i].vertex2]), (Find(&vertices[edges[i].vertex2]))->rank);
//        printf("cluster = %d i = %d\n\n", numberOfClusters, i);
        i++;
    }
    printf("Maximum spacing = %d\n", edges[i].cost);
    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

void swap_edges(edge_t *a, edge_t *b){
  	edge_t tmp = *a;
  	*a = *b;
  	*b = tmp;  
}
int partition(edge_p edges, int left, int right, int pivotIndex){
	int pivotValue = edges[pivotIndex].cost;
    int compareIndex = left + 1;
    
    swap_edges(&(edges[pivotIndex]), &(edges[left]));
	for(int i = left + 1; i <= right; i++){
		if(edges[i].cost < pivotValue){
            swap_edges(&(edges[i]), &(edges[compareIndex]));
			compareIndex++;
		}
	}
    swap_edges(&(edges[--compareIndex]), &(edges[left]));
	return compareIndex;
}
int medianOfThree(edge_p edges, int left, int right){
	int length = right - left + 1;
	int mid = (length / 2) + left;
	int first = edges[left].cost, middle = edges[mid].cost, last = edges[right].cost;
	if ((middle < first && first < last) || (middle > first && first > last))
    	return left;
	if ((first < middle && middle < last) || (first > middle && middle > last))
		return mid;
	return right;
}
void quickSort(edge_p edges, int left, int right){
	if(right > left){
		int newPivotIndex = partition(edges, left, right, medianOfThree(edges, left, right)); 
		quickSort(edges, left, newPivotIndex - 1);
		quickSort(edges, newPivotIndex + 1, right);
	}
}