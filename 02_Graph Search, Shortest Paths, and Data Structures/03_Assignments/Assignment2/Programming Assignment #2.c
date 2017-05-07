/*
	Using min heap to build extract min queue
	Heapify code is from wikipedia: https://zh.wikipedia.org/wiki/%E5%A0%86%E6%8E%92%E5%BA%8F

	Graph adjacency list source code "graph.h" is from Varun Gupta's blog
	http://simplestcodings.blogspot.tw/2013/09/graphs.html?view=sidebar
*/
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
/*
	Vertex: {    7,  37,  59,  82,  99, 115, 133, 165, 188, 197 }
	Answer: { 2599,2610,2947,2052,2367,2399,2029,2442,2505,3068 }
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"

#define SIZE 200
typedef enum {FALSE = 0, TRUE} bool;

typedef struct vertex_distance_queue{
	int vertex, distance;
}vertexDistanceQueue;

int convertCharToInt(char*, int digit);
void makeAdjacencyList(FILE *File, graph_p graph);
void swap_set(vertexDistanceQueue* a, vertexDistanceQueue* b);
void min_heapify(vertexDistanceQueue arr[], int start, int end);
int extract_min(vertexDistanceQueue vertexSet[], int finished);
void updateDistanceInQueue(vertexDistanceQueue vertexSet[], adjlist_p adjList, int finished, int distance, int* pre){
	int length = SIZE - finished;
	int i, j;
	bool vertexFinished = FALSE;
	adjlist_node_p nodePtr = adjList->head;
	// printf("distance = %d\n", distance);
	while(nodePtr != NULL){
		for(i = 1; i <= length; i++){
			if(vertexSet[i].vertex == nodePtr->vertex){
				// printf("vertex = %d\n", vertexSet[i].vertex);
				if((nodePtr->distance + distance) < vertexSet[i].distance){
					// printf("vertexSet[%d].distance = %d\n", i, vertexSet[i].distance);
					// printf("nodePtr->distance = %d\n", nodePtr->distance);
					vertexSet[i].distance = nodePtr->distance + distance;
					pre[vertexSet[i].vertex] = vertexSet[length + 1].vertex;
				}
				nodePtr = nodePtr->next;
				break;
			}
			for(j = SIZE; j > length; j--)
				if(vertexSet[j].vertex == nodePtr->vertex){
					vertexFinished = TRUE;
					nodePtr = nodePtr->next;
					break;
				}
			if(vertexFinished){
				vertexFinished = FALSE;
				break; 
			}
		}
	}
}
int* Dijkstra(graph_p graph, int source){
	int *distance = malloc((SIZE + 1) * sizeof(int));
	int *preVertex = malloc((SIZE + 1) * sizeof(int));
	int i, j;
	int finished = 0, vertexU, vertexV;
	int tempDistance;
	adjlist_p adjListPtr;
	adjlist_node_p nodePtr;
	vertexDistanceQueue vertexSet[SIZE + 1];
	
	for(i = 0; i <= SIZE; i++){
		vertexSet[i].vertex = i;
		vertexSet[i].distance = 1000000;
		distance[i] = 1000000;
		preVertex[i] = -1;
	}
	distance[source] = 0;
	vertexSet[source].distance = 0;
	swap_set(&vertexSet[1], &vertexSet[SIZE]);
	finished++;
	adjListPtr = &(graph->adjListArr[source]);
	nodePtr = adjListPtr->head;
	while(nodePtr != NULL){
		vertexV = nodePtr->vertex;
		tempDistance = nodePtr->distance + distance[source];
		// printf("tempDistance = %d\n", tempDistance);
		if(tempDistance < distance[vertexV]){
			distance[vertexV] = tempDistance;
			preVertex[vertexV] = source;
		}
		nodePtr = nodePtr->next;
	}
	updateDistanceInQueue(vertexSet, &(graph->adjListArr[source]), finished, distance[source], preVertex);


	while(finished != SIZE - 1){
		vertexU = extract_min(vertexSet, finished);
		distance[vertexU] = vertexSet[SIZE - finished].distance;
		finished++;
		// printf("vertexU = %d\n", vertexU);
		// printf("distance[vertexU] = %d\n", distance[vertexU]);
		adjListPtr = &(graph->adjListArr[vertexU]);
		nodePtr = adjListPtr->head;
		while(nodePtr != NULL){
			vertexV = nodePtr->vertex;
			tempDistance = nodePtr->distance + distance[vertexU];
			// printf("tempDistance = %d\n", tempDistance);
			if(tempDistance < distance[vertexV]){
				distance[vertexV] = tempDistance;
				preVertex[vertexV] = vertexU;
			}
			nodePtr = nodePtr->next;
		}
		// printf("Walk all adjacenct node of U\n");

		updateDistanceInQueue(vertexSet, &(graph->adjListArr[vertexU]), finished, distance[vertexU], preVertex);
		// for(j = 1; j <= SIZE; j++){
		// 	printf("%7d ", vertexSet[j].vertex);
		// }
		// printf("\n");
		// for(j = 1; j <= SIZE; j++){
		// 	printf("%7d ", vertexSet[j].distance);
		// }
		// printf("\nUpdate completed\n\n\n");
	}
	return distance;
}
void displayShortPath(int *vertexSet){
	int i;
	int array[] = {7,37,59,82,99,115,133,165,188,197};
	printf("Answer: { ");
	for(i = 0; i < sizeof(array) / sizeof(int) - 1; i++){
		printf("%d,", vertexSet[array[i]]);
	}
	printf("%d }", vertexSet[array[i]]);
	// for(i = 1; i <= SIZE; i++){
	// 	printf("vertex %d = %d\n\n", i, vertexSet[i]);
	// }
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
	// displayGraph(graph);

	displayShortPath(Dijkstra(graph, 1));

	destroyGraph(graph);
	
	fclose(inFile);
}

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
				digit = 0;
				v1Check = FALSE;
			}
			else{
				temp[digit] = c;
				digit++;
			}
		}
		else if(c == 10){
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
				digit = 0;
			}
			else{
				temp[digit] = c;
				digit++;
			}
		}
	}
}

void swap_set(vertexDistanceQueue* a, vertexDistanceQueue* b) {
	vertexDistanceQueue temp = *b;
	*b = *a;
	*a = temp;
}

void min_heapify(vertexDistanceQueue arr[], int start, int end) {
	//建立父節點指標和子節點指標
	int dad = start;
	int son = dad * 2;
	while (son <= end) { //若子節點指標在範圍內才做比較
		if (son + 1 <= end && arr[son].distance > arr[son + 1].distance) //先比較兩個子節點大小，選擇最大的
			son++;
		if (arr[dad].distance < arr[son].distance) //如果父節點大於子節點代表調整完畢，直接跳出函數
			return;
		else { //否則交換父子內容再繼續子節點和孫節點比較
			swap_set(&arr[dad], &arr[son]);
			dad = son;
			son = dad * 2;
		}
	}
}

int extract_min(vertexDistanceQueue vertexSet[], int finished){
	int i, length = SIZE - finished;
	for(i = length / 2; i > 0; i--)
		min_heapify(vertexSet, i, length);
	swap_set(&vertexSet[1], &vertexSet[length]);
	return vertexSet[length].vertex;
}