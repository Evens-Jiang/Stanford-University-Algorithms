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
    must include: <stdio.h>, <stdlib.h>, <time.h>, "graph.h"
*/
#ifndef _SCC_H_
#define _SCC_H_

int dfs(graph_p graph, int node, int time, int sourceVertex){
	int i, vertex;
	adjlist_node_p adjListNodePtr = graph->adjListArr[node].head;

	graph->adjListArr[node].leader = sourceVertex;
	for(i = 0; i < graph->adjListArr[node].num_members; i++){
		vertex = adjListNodePtr->vertex;
		if(graph->adjListArr[vertex].leader == -1)
			time = dfs(graph, vertex, time, sourceVertex);
		adjListNodePtr = adjListNodePtr->next;
	}
    graph->adjListArr[node].endTime_1st = time;
	time++;
    return time;
}

void dfs_loop(graph_p graph, int numberOfVertice){
	int i, time = 1, sourceVertex = 1;
	for(i = numberOfVertice; i > 0; i--){
		if(graph->adjListArr[i].leader == -1){
			sourceVertex = i;
			time = dfs(graph, i, time, sourceVertex);
		}
	}
}

int dfs_2nd(graph_p graph, int node, int time, int sourceVertex){
    /* sourceVertex equals to the 1st end time(the sorted index in adjListArr), not vertex number. */
	int i, endTime_1st;
	adjlist_node_p adjListNodePtr = graph->adjListArr[node].head;
    
    /* The adjListArr has been sorted, so we need to access adjListArr[sourceVertex].vertex. */
	graph->adjListArr[node].leader = graph->adjListArr[sourceVertex].vertex;
	for(i = 0; i < graph->adjListArr[node].num_members; i++){
		endTime_1st = adjListNodePtr->endTime;
        if(endTime_1st == -1){
            /* endTime_1st == -1 shows that the vertex has never been visited or no such vertex. */
            /* So we can skip it. */
            adjListNodePtr = adjListNodePtr->next;
            continue;
        }
		if(graph->adjListArr[endTime_1st].leader == -1)
			time = dfs_2nd(graph, endTime_1st, time, sourceVertex);
		adjListNodePtr = adjListNodePtr->next;
	}
    graph->adjListArr[node].endTime_2nd = time;
	time++;
    return time;
}

void dfs_2nd_loop(graph_p graph, int numberOfVertice){
	int i, time = 1, sourceVertex = 1;
	for(i = numberOfVertice; i > 0; i--){
        if(graph->adjListArr[i].endTime_1st == -1)
            continue;
		if(graph->adjListArr[i].leader == -1){
			sourceVertex = i;
			time = dfs_2nd(graph, i, time, sourceVertex);
		}
	}
}

void transTime(graph_p g, graph_p g_trans, int numberOfVertice){
	int i;
	adjlist_node_p nodePtr;
	for(i = 1; i <= numberOfVertice; i++){
		g_trans->adjListArr[i].endTime_1st = g->adjListArr[i].endTime_1st;
		nodePtr = g_trans->adjListArr[i].head;
		while(nodePtr){
			nodePtr->endTime = g->adjListArr[nodePtr->vertex].endTime_1st;
			nodePtr = nodePtr->next;
		}
	}
}

void swap_Graph(adjlist_p a, adjlist_p b){
  	adjlist_t tmp = *a;
  	*a = *b;
  	*b = tmp;  
}

int partition_Graph(adjlist_p adjListArr, int left, int right, int pivotIndex){
	int pivotValue = adjListArr[pivotIndex].endTime_1st, compareIndex = left + 1;
	swap_Graph(&(adjListArr[pivotIndex]), &(adjListArr[left]));
	for(int i = left + 1; i <= right; i++){
		if(adjListArr[i].endTime_1st < pivotValue){
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
	int first = adjListArr[left].endTime_1st,\
		middle = adjListArr[mid].endTime_1st,\
		last = adjListArr[right].endTime_1st;
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

void findSCC(graph_p dir_graph, graph_p dir_graph_transpose, int numberOfVertice){
    /* A vertex has true nad false presentation (not X and X), so numberOfVertice must double. */
    numberOfVertice *= 2;
	dfs_loop(dir_graph, numberOfVertice);

	transTime(dir_graph, dir_graph_transpose, numberOfVertice);
	
	quickSort_Graph(dir_graph_transpose->adjListArr, 1, numberOfVertice);
    
	dfs_2nd_loop(dir_graph_transpose, numberOfVertice);

    destroyGraph(dir_graph);
}

#endif