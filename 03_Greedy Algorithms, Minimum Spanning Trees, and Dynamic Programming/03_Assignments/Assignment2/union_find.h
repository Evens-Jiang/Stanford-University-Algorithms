#ifndef _UNIONFIND_H_
#define _UNIONFIND_H_

typedef struct edge{
    int vertex1, vertex2, cost;
}edge_t, *edge_p;

typedef struct vertex{
    struct vertex *parent;
    int rank;
}vertex_t, *vertex_p;

void MakeSet(vertex_p vertex){
    vertex->parent = vertex;
    vertex->rank = 0;
}
vertex_p Find(vertex_p vertex){
    if(vertex->parent != vertex)
        vertex->parent = Find(vertex->parent);
    return vertex->parent;
}
int Union(vertex_p vertex1, vertex_p vertex2, int numberOfCluster){
    vertex_p vertexRoot1 = Find(vertex1), vertexRoot2 = Find(vertex2);
    
    if(vertexRoot1 == vertexRoot2)
        return numberOfCluster;
    
    if(vertexRoot1->rank < vertexRoot2->rank)
        vertexRoot1->parent = vertexRoot2;
    else if(vertexRoot1->rank > vertexRoot2->rank)
        vertexRoot2->parent = vertexRoot1;
    else{
        vertexRoot2->parent = vertexRoot1;
        vertexRoot1->rank++;
    }
    numberOfCluster--;
    return numberOfCluster;
}
#endif