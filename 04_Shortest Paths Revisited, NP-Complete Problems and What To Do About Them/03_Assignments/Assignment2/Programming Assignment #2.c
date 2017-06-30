/*
    Travelling Salesman Problem.
    Dynamic programming strategy:
        1. Given vertices set = {1, 2, 3, 4,…,n} and assume starting point is 1.
        (cost(i) = minimum cost for the path from 1 to i. The corrsponding cycle is cost(i) + dist(i, 1))

        2. C(S, i) be the cost of the minimum cost path visiting each vertex in set S exactly once, starting at 1 and ending at i.

        3. 
        If size of S is 2, then S must be {1, i}
            C(S, i) = dist(1, i) 
        Else if size of S is greater than 2.
            C(S, i) = min { C(S-{i}, j) + dis(j, i)}, where j belongs to S, j != i and j != 1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "graph.h"

void swap(int *a, int *b);
void makeEdge(graph_p graph, double **coordinate, int start, int end);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("tsp.txt", "r");
    int numberOfCity, i, j;
    double **coordinate;
    
    if(!inFile){
        printf("Fail to open file.\n");
        return;
    }
    else
        printf("Open file successfully!\n");
    
    fscanf(inFile, "%d", &numberOfCity);
    printf("numberOfCity = %d\n", numberOfCity);
    coordinate = malloc(numberOfCity * sizeof(double*));
    if(!coordinate){
        printf("Malloc coordinate failed.\n");
        return;
    }
    for(i = 0; i < numberOfCity; i++){
        coordinate[i] = malloc(2 * sizeof(double));
        if(!coordinate[i]){
            printf("Malloc coordinate[%d] failed.\n", i);
            return;
        }
    }
    i = 0;
    while(fscanf(inFile, "%lf %lf", &coordinate[i][0], &coordinate[i][1]) != EOF){
        printf("%.4lf %.4lf\n", coordinate[i][0], coordinate[i][1]);
        i++;
    }
    graph_p graph = createGraph(numberOfCity, UNDIRECTED);
    for(i = 0; i < numberOfCity; i++)
        for(j = i + 1; j < numberOfCity; j++)
            makeEdge(graph, coordinate, i, j);
    
    displayGraph(graph);
    
    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void makeEdge(graph_p graph, double **coordinate, int start, int end){
    double x1 = coordinate[start][0], y1 = coordinate[start][1];
    double x2 = coordinate[end][0], y2 = coordinate[end][1];
    double distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    addEdge(graph, start, end, distance);
}