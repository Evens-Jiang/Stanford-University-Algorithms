/*
    Minimum Spanning Tree: Prim's algorithm
    Adjacency list
    Priority queue(heap)
    
    
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

int NUMBER_OF_NODE = 0, TOTAL_COST = 0, NUMBER_OF_VISITED_NODE = 0;

typedef struct vertex_cost{
    int vertex, cost;
}vertexCost, *vertexCost_p;

void swap_VertexQueue(vertexCost *a, vertexCost *b);
void minHeapify(vertexCost vertexQueue[], int end);
int insertHeap(vertexCost vertexQueue[], int end, int vertex, int cost);
int extractMin(vertexCost vertexQueue[], bool visited[], int end);
int updateQueue(graph_p graph, vertexCost vertexQueue[], bool visited[], bool finished[], int vertex, int end);
void prim(graph_p graph, int maxCost);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("edges.txt", "r");
    int numberOfEdges;
    int source, destination, cost, i = 0, maxCost = 0;
    
    if(!inFile){
    	printf("Fail to open file\n");
        return;
    }
    else
    	printf("Open file successfully!\n");
    
    fscanf(inFile, "%d %d", &NUMBER_OF_NODE, &numberOfEdges);
    printf("Number of nodes = %d\n", NUMBER_OF_NODE);
    printf("Number of edges = %d\n", numberOfEdges);
    /* create graph */
    graph_p graph = createGraph(NUMBER_OF_NODE, UNDIRECTED);
    
    /* make adjacency list */
    while(fscanf(inFile, "%d %d %d", &source, &destination, &cost) != EOF){
        addEdge(graph, source, destination, cost);
        if(maxCost < cost)
            maxCost = cost;
    }
    printf("Max cost = %d\n", maxCost);
    prim(graph, maxCost + 1);
    printf("Total cost = %d\n", TOTAL_COST);
    
    displayGraph(graph);
    destroyGraph(graph);
    
    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

void swap_VertexQueue(vertexCost *a, vertexCost *b){
    vertexCost temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(vertexCost vertexQueue[], int end){
	int son = end, dad = son / 2;
	while (son != 1) {
		if (vertexQueue[son].cost < vertexQueue[dad].cost)
			swap_VertexQueue(&vertexQueue[son], &vertexQueue[dad]);
        else
            return;
        son = dad;
        dad = son / 2;
	}
}

int insertHeap(vertexCost vertexQueue[], int end, int vertex, int cost){
    if(end + 1 <= NUMBER_OF_NODE){
        end = end + 1;
        vertexQueue[end].vertex = vertex;
        vertexQueue[end].cost = cost;
        minHeapify(vertexQueue, end);
    }
    return end;
}

int extractMin(vertexCost vertexQueue[], bool finished[], int end){
    for(int i = 1; i <= end; i++){
        printf("(%3d, %3d, %5d)\n", i, vertexQueue[i].vertex, vertexQueue[i].cost);
    }
    swap_VertexQueue(&vertexQueue[1], &vertexQueue[NUMBER_OF_NODE - NUMBER_OF_VISITED_NODE]);
    finished[vertexQueue[NUMBER_OF_NODE - NUMBER_OF_VISITED_NODE].vertex] = TRUE;
    int dad = 1, son = dad * 2;
    while(son < end){
        if(vertexQueue[son + 1].cost < vertexQueue[son].cost && son + 1 <= end)
            son++;
        if(vertexQueue[son].cost < vertexQueue[dad].cost){
            swap_VertexQueue(&vertexQueue[dad], &vertexQueue[son]);
            dad = son;
            son = dad * 2;
        }
        else{
            TOTAL_COST += vertexQueue[NUMBER_OF_NODE - NUMBER_OF_VISITED_NODE].cost;
            return vertexQueue[NUMBER_OF_NODE - NUMBER_OF_VISITED_NODE].vertex;
        }
    }
    TOTAL_COST += vertexQueue[end].cost;
    return vertexQueue[NUMBER_OF_NODE - NUMBER_OF_VISITED_NODE].vertex;
}

int updateQueue(graph_p graph, vertexCost vertexQueue[], bool visited[], bool finished[], int vertex, int end){
    adjlist_node_p nodePtr = (graph->adjListArr[vertex]).head;
    int i = 1;
    while(nodePtr){
        printf("nodePtr->vertex = %d\n", nodePtr->vertex);
        if(finished[nodePtr->vertex]){
            nodePtr = nodePtr->next;
            continue;
        }
        if(visited[nodePtr->vertex]){
            while(vertexQueue[i].vertex != nodePtr->vertex)
                i++;
            if(vertexQueue[i].cost < nodePtr->cost)
                vertexQueue[i].cost = nodePtr->cost;
            minHeapify(vertexQueue, i);
            i = 1;
        }
        else{
            end = insertHeap(vertexQueue, end, nodePtr->vertex, nodePtr->cost);
            visited[nodePtr->vertex] = TRUE;
        }
        nodePtr = nodePtr->next;
    }
    return end;
}

void prim(graph_p graph, int maxCost){
    int vertexV = 1, i, end = 0;
    bool *visited = malloc((NUMBER_OF_NODE  + 1) * sizeof(bool));
    bool *finished = malloc((NUMBER_OF_NODE  + 1) * sizeof(bool));
    vertexCost_p vertexQueue = (vertexCost_p)malloc((NUMBER_OF_NODE  + 1) * sizeof(vertexCost));
    
    for(i = 0; i <= NUMBER_OF_NODE; i++){
        vertexQueue[i].vertex = -1;
        vertexQueue[i].cost = maxCost;
        visited[i] = FALSE;
    }
    vertexQueue[NUMBER_OF_NODE].vertex = vertexV;
    vertexQueue[NUMBER_OF_NODE].cost = 0;
    NUMBER_OF_VISITED_NODE++;
    visited[vertexV] = TRUE;
    finished[vertexV] = TRUE;
    end = updateQueue(graph, vertexQueue, visited, finished, vertexV, end);
    printf("end = %d\n", end);
    vertexV = extractMin(vertexQueue, visited, end);
    NUMBER_OF_VISITED_NODE++;
    printf("vertex V = %d\n", vertexV);
    end--;
    while(end != 0){
        end = updateQueue(graph, vertexQueue, visited, finished, vertexV, end);
        printf("end = %d\n", end);
        vertexV = extractMin(vertexQueue, visited, end);
        NUMBER_OF_VISITED_NODE++;
        printf("vertex V = %d\n", vertexV);
        end--;
    }
    return;
}