/*
    Bellman Ford algorithm.
    Detecting negative cycle.
    (https://www.dyclassroom.com/graph/detecting-negative-cycle-using-bellman-ford-algorithm)
    
    Step 1: We start by filling the distance array d[ ] with INFINITY and since vertex 0 is the source vertex so we will set d[0] = 0.

    Step 2: Next we will fill the predecessor array p[ ] with 0.

    Step 3: We will relax all the edges of the graph by loop N-1 times.

    Step 4: We will perform the Nth loop to check if the graph has any negative cycle.
    
    About Relaxing Edge:
        Consider an edge u --> v where u is the start and v is the end vertex respectively. Relaxing an edge relax(u,v) means to find shorter path to reach v when considering edge u --> v.

    relax(u,v):
        if v.d > u.d + w(u,v) then
            v.d = u.d + w(u,v)
            v.p = u
*/
#ifndef _BELLMANFORD_H_
#define _BELLMANFORD_H_

#define INFINITY 99999

//struct for the edges of the graph
typedef struct Edge {
	int start;	//start vertex of the edge
	int end;	//end vertex of the edge
	int weight;	//weight of the edge (u,v)
}edge_t, *edge_p;

//Graph - it consists of edges
typedef struct Graph {
	int numberOfVertices	//total number of vertices in the graph
	int numberOfEdges;	//total number of edges in the graph
	edge_t *edges;	//array of edges
}graph_t, *graph_p;

void errorExit(char* message) {
    printf("[Fatal Error]: %s \nExiting...\n", message);
    exit(1);
}

void addEdge(graph_p graph, int start, int end, int weight, int numberOfEdge){
    if(graph->numberOfEdges < numberOfEdge)
        errorExit("Edge number overflowed.");
    graph->edges[numberOfEdge].start = start;
    graph->edges[numberOfEdge].end = end;
    graph->edges[numberOfEdge].weight = weight;
    return;
}

graph_p createGraph(int numberOfVertices, int numberOfEdges){
    graph_p newGraph = malloc(sizeof(graph_t));
    if(!newGraph)
        errorExit("Malloc graph failed.");
    newGraph->numberOfVertices = numberOfVertices;
    newGraph->numberOfEdges = numberOfEdges;
    newGraph->edges = malloc(numberOfEdges * sizeof(edge_t));
    return newGraph;
}

bellmanFord(graph_p graph, int source){
    int numberOfVertices = graph->numberOfVertices, numberOfEdges = graph->numberOfEdges;
    int *distance, *predecessor;
    int i;
    
    if(distance = malloc((numberOfVertices + 1) * sizeof(int)) == NULL)
        errorExit("Malloc distance array failed.");
    if(predecessor = malloc((numberOfVertices + 1) * sizeof(int)) == NULL)
        errorExit("Malloc predecessor array failed.");
    /* Step1 & 2 */
    for(i = 0; i <= numberOfVertices; i++){
        distance[i] = INFINITY;
        predecessor[i] = 0;
    }
    distance[source] = 0;
    
    /* Step3 */
    for(i = 0; i < numberOfVertices; i++)
        
    
}

#endif