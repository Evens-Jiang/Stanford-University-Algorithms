/*
	Dijkstra's algorithm
	function Dijkstra(Graph, source):
		create vertex set Q
		for each vertex v in Graph:             // Initialization
			dist[v] ← INFINITY                  // Unknown distance from source to v
			prev[v] ← UNDEFINED                 // Previous node in optimal path from source
			add v to Q                          // All nodes initially in Q (unvisited nodes)
		dist[source] ← 0                        // Distance from source to source
		while Q is not empty:
			u ← vertex in Q with min dist[u]    // Node with the least distance will be selected first
			remove u from Q 
			for each neighbor v of u:           // where v is still in Q.
				alt ← dist[u] + length(u, v)
				if alt < dist[v]:               // A shorter path to v has been found
					dist[v] ← alt 
					prev[v] ← u 
		return dist[], prev[]
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"

#define SIZE 200
typedef enum {FALSE = 0, TRUE} bool;

int convertCharToInt(char *c, int digit){
	int number = 0, counter = digit, power = 0;
	if(counter == 1)
		return *c - 48;
	while(counter--){
		if(counter % 2 || counter == 0)
			power = (int) (pow(10, counter));
		else
			power = (int) (pow(10, counter)) + 1;
		number += (*c - 48) * power;
		c++;
	}
	return number;
}

void makeAdjacencyList(FILE *File, graph_p graph){
	int v1, v2, digit = 0, distance;
	char c;
	char temp[7];
	bool v1Check = TRUE;
	
	while(!feof(File)){
		c = fgetc(File);
		if(v1Check){
			if(c == 9){
				v1 = convertCharToInt(temp, digit);
//				printf("v1 = %d\n", v1);
				digit = 0;
				v1Check = FALSE;
			}
			else{
				temp[digit] = c;
				digit++;
			}
		}
		else if(c == 10){
//			printf("\n");
			v1Check = TRUE;
		}
		else{
			if(c == 9){
				distance = convertCharToInt(temp, digit);
				digit = 0;
				addEdge(graph, v1, v2, distance);
			}
			else if(c == 44){
				v2 = convertCharToInt(temp, digit);
//				printf("%4d ", v2);
				digit = 0;
			}
			else{
				temp[digit] = c;
				digit++;
			}
		}
	}
}

void Dijkstra(graph_p graph, int source){
	int vertexSet[SIZE + 1], distance[SIZE + 1], preVertex[SIZE + 1];
}

void main(){
	FILE *inFile = fopen("dijkstraData.txt", "r");
	
	if(!inFile)
		printf("Fail to open file\n\n");
	else
		printf("Open file successfully!\n\n");
	
	graph_p graph = createGraph(SIZE, DIRECTED);
	printf("Graph created.\n\n");

	makeAdjacencyList(inFile, graph);
	displayGraph(graph);
	destroyGraph(graph);
	
	fclose(inFile);
}