/*
DFS‐Loop(graph G)
	Global variable t = 0
	[# of nodes processed so far]
	Global variable s = NULL 
	[current source vertex]
	Assume nodes labeled 1 to n
	For i = n down to 1
		if i not yet explored
			s = i
			DFS(G,i)
----------------------------------------
DFS(graph G, node i)
	mark i as explored
	set leader(i) = node s
	for each arc(i,j) in G:
		if j not yet explored
			DFS(G,j)
	t++
	set f(i) = t

*/
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// #define SIZE 875714 
#define SIZE 8
int S = -1;
int TIME = 1;
int COUNTER = 0;
typedef struct scclist_node{
	int vertex;
	struct scclist_node *next;
}scclist_node_t, *scclist_node_p;

typedef struct scclist{
	int num_members;	//number of members in the list
	scclist_node_t *head;
}scclist_t, *scclist_p;

typedef struct scc{
	int num_sccs;
	scclist_p sccListArr;
}scc_t, *scc_p;

void dfs(graph_p graph, int node){
	int i, vertex;
	adjlist_node_p adjListNodePtr = graph->adjListArr[node].head;

	graph->adjListArr[node].explored = TRUE;
	graph->adjListArr[node].leader = S;
	// graph->adjListArr[node].startTime = TIME;
	// TIME++;
	for(i = 0; i < graph->adjListArr[node].num_members; i++){
		vertex = adjListNodePtr->vertex;
		if(!graph->adjListArr[vertex].explored)
			dfs(graph, vertex);
		adjListNodePtr = adjListNodePtr->next;
	}
	graph->adjListArr[node].endTime = TIME;
	TIME++;
}

void dfs_loop(graph_p graph){
	S = -1;
	TIME = 1;
	int i;
	for(i = SIZE; i > 0; i--){
		if(!graph->adjListArr[i].explored){
			S = i;
			dfs(graph, i);
		}
	}
}

void transTime(graph_p g, graph_p g_trans){
	int i, j;
	adjlist_node_p nodePtr;
	for(i = 1; i <= SIZE; i++){
		g_trans->adjListArr[i].endTime = g->adjListArr[i].endTime;
		nodePtr = g_trans->adjListArr[i].head;
		while(nodePtr){
			nodePtr->vertex = g->adjListArr[nodePtr->vertex].endTime;
			nodePtr = nodePtr->next;
		}
	}
}

void swap(adjlist_p a, adjlist_p b){
  	adjlist_t tmp = *a;
  	*a = *b;
  	*b = tmp;  
}

int partition(adjlist_p adjListArr, int left, int right, int pivotIndex){
	int pivotValue = adjListArr[pivotIndex].endTime, compareIndex = left + 1;
	swap(&(adjListArr[pivotIndex]), &(adjListArr[left]));
	for(int i = left + 1; i <= right; i++){
		if(adjListArr[i].endTime < pivotValue){
			swap(&(adjListArr[i]), &(adjListArr[compareIndex]));
			compareIndex++;
		}
	}
	swap(&(adjListArr[--compareIndex]), &(adjListArr[left]));
	return compareIndex;
}

int medianOfThree(adjlist_p adjListArr, int left, int right){
	int length = right - left + 1;
	int mid = (length % 2) == 0 ? ((length / 2) - 1) + left : (length / 2) + left;
	int first = adjListArr[left].endTime,\
		middle = adjListArr[mid].endTime,\
		last = adjListArr[right].endTime;
	if ((middle < first && first < last) || (middle > first && first > last))
    	return left;
	if ((first < middle && middle < last) || (first > middle && middle > last))
		return mid;
	return right;
}

void quickSort(adjlist_p adjListArr, int left, int right){
	if(right > left){
		COUNTER++;
		// printf("COUNTER = %d\n\n", COUNTER);
		int newPivotIndex = \
			partition(adjListArr, left, right,\
				medianOfThree(adjListArr, left, right));
		quickSort(adjListArr, left, newPivotIndex - 1);
		quickSort(adjListArr, newPivotIndex + 1, right);
	}
}

void main(){
	FILE *inFile = fopen("test3.txt", "r");
	int start, end;

	if(!inFile)
		printf("Fail to open file\n");
	else
		printf("Open file successfully!\n");

	graph_p dir_graph = createGraph(SIZE, DIRECTED);
	graph_p dir_graph_transpose = createGraph(SIZE, DIRECTED);
	printf("Created successfully\n\n");

	while(fscanf(inFile, "%d %d", &start, &end) != EOF){
		addEdge(dir_graph, start, end);
		addEdge(dir_graph_transpose, end, start);
	}

	dfs_loop(dir_graph);
	transTime(dir_graph, dir_graph_transpose);
	printf("Time transition completed.\n\n");
	
	quickSort(dir_graph_transpose->adjListArr, 1, SIZE);
	printf("Quicksort completed.\n");
	
	dfs_loop(dir_graph_transpose);
	
	printf("\nDIRECTED GRAPH");
    displayGraph(dir_graph);
    destroyGraph(dir_graph);
    printf("\nDIRECTED GRAPH_Transpose");
    displayGraph(dir_graph_transpose);
    destroyGraph(dir_graph_transpose);
	fclose(inFile);
}