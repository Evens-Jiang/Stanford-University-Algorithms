/*
	Graph adjacency list source code "graph.h" is from Varun Gupta's blog
	http://simplestcodings.blogspot.tw/2013/09/graphs.html?view=sidebar
*/
/*
	Kosaraju's algorithm.
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
/*
	Because of the huge data, we need to increase the stack size for DFS recursion.
	gcc -Wl,--stack,16777216 "Programming Assignment #1.c" -o "Programming Assignment #1.exe"

	for test examples
	http://rupen.s3-website-us-east-1.amazonaws.com/

	The top 5 largest SCC number = { 434821,968,459,313,211 }
*/
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define SIZE 875714 

int S = -1;
int TIME = 1;
int COUNTER = 0;
int SCC[SIZE + 1] = {0};

void dfs(graph_p graph, int node){
	int i, vertex;
	adjlist_node_p adjListNodePtr = graph->adjListArr[node].head;

	graph->adjListArr[node].leader = S;
	for(i = 0; i < graph->adjListArr[node].num_members; i++){
		vertex = adjListNodePtr->vertex;
		if(graph->adjListArr[vertex].leader == -1)
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
		if(graph->adjListArr[i].leader == -1){
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

void swap_SCC(int *a, int *b){
  	int tmp = *a;
  	*a = *b;
  	*b = tmp;  
}

int partition_SCC(int arr[], int left, int right, int pivotIndex){
	int pivotValue = arr[pivotIndex], compareIndex = left + 1;
	swap_SCC(&(arr[pivotIndex]), &(arr[left]));
	for(int i = left + 1; i <= right; i++){
		if(arr[i] < pivotValue){
			swap_SCC(&(arr[i]), &(arr[compareIndex]));
			compareIndex++;
		}
	}
	swap_SCC(&(arr[--compareIndex]), &(arr[left]));
	return compareIndex;
}

int medianOfThree_SCC(int arr[], int left, int right){
	int length = right - left + 1;
	int mid = (length % 2) == 0 ? ((length / 2) - 1) + left : (length / 2) + left;
	int first = arr[left],\
		middle = arr[mid],\
		last = arr[right];
	if ((middle < first && first < last) || (middle > first && first > last))
    	return left;
	if ((first < middle && middle < last) || (first > middle && middle > last))
		return mid;
	return right;
}

void quickSort_SCC(int arr[], int left, int right){
	if(right > left){
		int newPivotIndex = \
			partition_SCC(arr, left, right,\
				medianOfThree_SCC(arr, left, right));
		quickSort_SCC(arr, left, newPivotIndex - 1);
		quickSort_SCC(arr, newPivotIndex + 1, right);
	}
}

void countSCC(adjlist_p adjListArr){
	int i;
	int final[5] = {0};
	int temp;
	for(i = 1; i <= SIZE; i++){
		if(adjListArr[i].leader != -1)
			SCC[adjListArr[i].leader]++;
	}
	for(i = 1; i <= SIZE; i++){
		temp = SCC[i];
		if(temp > final[0])
			swap_SCC(&temp, &final[0]);
		if(temp > final[1])
			swap_SCC(&temp, &final[1]);
		if(temp > final[2])
			swap_SCC(&temp, &final[2]);
		if(temp > final[3])
			swap_SCC(&temp, &final[3]);
		if(temp > final[4])
			swap_SCC(&temp, &final[4]);
	}

	printf("\nThe top 5 largest SCC number = { ");
	for(i = 0; i < 4; i++){
		printf("%d,", final[i]);
	}
	printf("%d }\n", final[i]);
}

void swap_Graph(adjlist_p a, adjlist_p b){
  	adjlist_t tmp = *a;
  	*a = *b;
  	*b = tmp;  
}

/*
typedef struct _Range {
	int start, end;
} Range;
Range new_Range(int s, int e) {
	Range r;
	r.start = s;
	r.end = e;
	return r;
}
void quickSort(adjlist_p adjListArr, const int len) {
	if (len <= 0)
		return; //避免len等於負值時宣告堆疊陣列當機
	//r[]模擬堆疊,p為數量,r[p++]為push,r[--p]為pop且取得元素
	Range r[len];
	int p = 0;
	r[p++] = new_Range(1, len);
	// printf("p = %d\n\n", p);
	while (p) {
		Range range = r[--p];
		// printf("p--\np = %d\n\n", p);
		if (range.start >= range.end)
			continue;
		int mid = adjListArr[range.end].endTime;
		int left = range.start, right = range.end - 1;
		while (left < right) {
			while (adjListArr[left].endTime < mid && left < right)
				left++;
			while (adjListArr[right].endTime >= mid && left < right)
				right--;
			swap_Graph(&adjListArr[left], &adjListArr[right]);
		}
		if (adjListArr[left].endTime >= adjListArr[range.end].endTime)
			swap_Graph(&adjListArr[left], &adjListArr[range.end]);
		else
			left++;
		r[p++] = new_Range(range.start, left - 1);
		// printf("p++\np = %d\n\n", p);
		r[p++] = new_Range(left + 1, range.end);
		// printf("p++\np = %d\n\n", p);
	}
}
*/

int partition_Graph(adjlist_p adjListArr, int left, int right, int pivotIndex){
	int pivotValue = adjListArr[pivotIndex].endTime, compareIndex = left + 1;
	swap_Graph(&(adjListArr[pivotIndex]), &(adjListArr[left]));
	for(int i = left + 1; i <= right; i++){
		if(adjListArr[i].endTime < pivotValue){
			swap_Graph(&(adjListArr[i]), &(adjListArr[compareIndex]));
			compareIndex++;
		}
	}
	swap_Graph(&(adjListArr[--compareIndex]), &(adjListArr[left]));
	return compareIndex;
}

int medianOfThree_Graph(adjlist_p adjListArr, int left, int right){
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

void quickSort_Graph(adjlist_p adjListArr, int left, int right){
	if(right > left){
		int newPivotIndex = \
			partition_Graph(adjListArr, left, right,\
				medianOfThree_Graph(adjListArr, left, right));
		quickSort_Graph(adjListArr, left, newPivotIndex - 1);
		quickSort_Graph(adjListArr, newPivotIndex + 1, right);
	}
}

void main(){
	FILE *inFile = fopen("SCC.txt", "r");
	int start, end;

	if(!inFile)
		printf("Fail to open file\n\n");
	else
		printf("Open file successfully!\n\n");

	graph_p dir_graph = createGraph(SIZE, DIRECTED);
	graph_p dir_graph_transpose = createGraph(SIZE, DIRECTED);
	printf("Created successfully\n\n");

	while(fscanf(inFile, "%d %d", &start, &end) != EOF){
		addEdge(dir_graph, start, end);
		addEdge(dir_graph_transpose, end, start);
	}
	printf("Add edge completed\n\n");

	dfs_loop(dir_graph);
	printf("Graph dfs completed.\n\n");

	transTime(dir_graph, dir_graph_transpose);
	printf("Time transition completed.\n\n");
	
	quickSort_Graph(dir_graph_transpose->adjListArr, 1, SIZE);
	printf("Quicksort completed.\n\n");
	
	dfs_loop(dir_graph_transpose);
	printf("Graph transpose dfs completed\n\n");

    destroyGraph(dir_graph);
    // printf("\nDIRECTED GRAPH_Transpose");
    // displayGraph(dir_graph_transpose);
    // destroyGraph(dir_graph_transpose);

    countSCC(dir_graph_transpose->adjListArr);

	fclose(inFile);
}