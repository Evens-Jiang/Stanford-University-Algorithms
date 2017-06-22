/*
    Floyd-Warshall Algorithm.
    all-pairs shortest path.
    
    let dist be a |V| × |V| array of minimum distances initialized to ∞ (infinity)
    for each vertex v
        dist[v][v] ← 0
    for each edge (u,v)
        dist[u][v] ← w(u,v)  // the weight of the edge (u,v)
    for k from 1 to |V|
        for i from 1 to |V|
            for j from 1 to |V|
                if dist[i][j] > dist[i][k] + dist[k][j] 
                    dist[i][j] ← dist[i][k] + dist[k][j]
                end if
*/
#ifndef _FLOYDWARSHALL_H_
#define _FLOYDWARSHALL_H_

__int64 floydWarshall(graph_p graph){
    int i, j, k;
    int numberOfVertices = graph->numberOfVertices, numberOfEdges = graph->numberOfEdges;
    int start, end, weight;
    __int64 **distance, shortestPath = INFINITY;

    if((distance = malloc((numberOfVertices + 1) * sizeof(__int64*))) == NULL)
        errorExit("Malloc *distance failed.");
    for(i = 0; i <= numberOfVertices; i++){
        if((distance[i] = malloc((numberOfVertices + 1) * sizeof(__int64))) == NULL)
            errorExit("Malloc distance failed.");
        for(j = 0; j <= numberOfVertices; j++){
            if(i == j)
                distance[i][j] = 0;
            else
                distance[i][j] = INFINITY;
        }
    }
    for(i = 0; i < numberOfEdges; i++){
        start = graph->edges[i].start;
        end = graph->edges[i].end;
        distance[start][end] = graph->edges[i].weight;
    }
    for(k = 1; k <= numberOfVertices; k++)
        for(i = 1; i <= numberOfVertices; i++)
            for(j = 1; j <= numberOfVertices; j++)
                if(distance[i][j] > distance[i][k] + distance[k][j])
                    distance[i][j] = distance[i][k] + distance[k][j];
    for(i = 1; i <= numberOfVertices; i++)
        for(j = 1; j <= numberOfVertices; j++)
            if(shortestPath > distance[i][j])
                shortestPath = distance[i][j];
    return shortestPath;
}

#endif