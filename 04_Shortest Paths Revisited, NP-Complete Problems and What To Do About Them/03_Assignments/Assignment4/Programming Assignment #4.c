/*
    2-SAT Problems with SCC method.
    CPU: Duo E8400
        File        numberOfVertice     Running time(sec)   Unsatisfiable vertex
        2sat1.txt   100000              0.390               none
        2sat2.txt   200000              0.850               u = 9187
        2sat3.txt   400000              1.819               none
        2sat4.txt   600000              2.875               none
        2sat5.txt   800000              3.807               u = 223530
        2sat6.txt   1000000             4.860               u = 273101

    6 instances = 101100
    Total running time = 14.617 (sec)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "scc.h"

int findSat(graph_p dir_graph_transpose, int numberOfVertice, int *vertexToTime);

void main(){
    clock_t beginTime, completeTime, totalBeginTime = clock(), totalCompleteTime;
    FILE *inFile;
    char satFile[6][10] = {"2sat1.txt", "2sat2.txt", "2sat3.txt", "2sat4.txt", "2sat5.txt", "2sat6.txt"};
    int u, v, numberOfVertice, i, j, *vertexToTime, satResult[6] = {0};
    graph_p dir_graph, dir_graph_transpose;
    
    for(i = 0; i < 6; i++){
        beginTime = clock();
        inFile = fopen(satFile[i], "r");
        if(!inFile)
            printf("Fail to open file\n");
        else
            printf("\nOpen %s successfully!\n", satFile[i]);
        fscanf(inFile, "%d", &numberOfVertice);
        printf("numberOfVertice = %d\n", numberOfVertice);
        dir_graph = createGraph(2 * numberOfVertice, DIRECTED);
        dir_graph_transpose = createGraph(2 * numberOfVertice, DIRECTED);
        vertexToTime = malloc(2 * (numberOfVertice + 1) * sizeof(int));
        if(!vertexToTime)
            err_exit("Malloc vertexToTime failed.");
        
        while(fscanf(inFile, "%d %d", &u, &v) != EOF){
            /* u == v */
            if(u == (-1) * v){
                /* Always true */
                continue;
            }
            if(u == v){
                /* There will be a contradiction when u equals to v, not happen in these cases. */
                printf("u equals to v\n");
                printf("(u, v) = (%d, %d)\n", u, v);
                continue;
            }
            /* u != v */
            if(u > 0 && v > 0){
                /* -u -> v */
                addEdge(dir_graph, u + numberOfVertice, v);
                addEdge(dir_graph_transpose, v, u + numberOfVertice);
                /* -v -> u */
                addEdge(dir_graph, v + numberOfVertice, u);
                addEdge(dir_graph_transpose, u, v + numberOfVertice);
            }
            else if(u < 0 && v > 0){
                u *= (-1);
                /* u -> v */
                addEdge(dir_graph, u, v);
                addEdge(dir_graph_transpose, v, u);
                /* -v -> -u */
                addEdge(dir_graph, v + numberOfVertice, u + numberOfVertice);
                addEdge(dir_graph_transpose, u + numberOfVertice, v + numberOfVertice);
            }
            else if(u > 0 && v < 0){
                v *= (-1);
                /* -u -> -v */
                addEdge(dir_graph, u + numberOfVertice, v + numberOfVertice);
                addEdge(dir_graph_transpose, v + numberOfVertice, u + numberOfVertice);
                /* v -> u */
                addEdge(dir_graph, v, u);
                addEdge(dir_graph_transpose, u, v);
            }
            else if(u < 0 && v < 0){
                u *= (-1);
                v *= (-1);
                /* u -> -v */
                addEdge(dir_graph, u, v + numberOfVertice);
                addEdge(dir_graph_transpose, v + numberOfVertice, u);
                /* v -> -u */
                addEdge(dir_graph, v, u + numberOfVertice);
                addEdge(dir_graph_transpose, u + numberOfVertice, v); 
            }
            else{
                /* Exception */
                printf("Out of four conditions.\n");
                exit(1);
            }
        }
        fclose(inFile);
        findSCC(dir_graph, dir_graph_transpose, numberOfVertice);
        /* An transition array for vertex to time. */
        for(j = 1; j <= 2 * numberOfVertice; j++)
            vertexToTime[dir_graph_transpose->adjListArr[j].vertex] = j;

        satResult[i] = findSat(dir_graph_transpose, numberOfVertice, vertexToTime);
        destroyGraph(dir_graph_transpose);
        free(vertexToTime);
        
        completeTime = clock();
        printf("Running time = %.3f (sec)\n\n", (double)(completeTime - beginTime) / CLOCKS_PER_SEC);
    }
    printf("6 instances = ");
    for(i = 0; i < 6; i++)
        printf("%d", satResult[i]);
    printf("\n");
    totalCompleteTime = clock();
    printf("Running time = %.3f (sec)\n\n", (double)(totalCompleteTime - totalBeginTime) / CLOCKS_PER_SEC);
}
/* Check that is there any u and -u in the same component. */
int findSat(graph_p dir_graph_transpose, int numberOfVertice, int *vertexToTime){
    int i, leaderU, leaderNotU, timeIndex;
    for(i = 1; i <= numberOfVertice; i++){
        /* Because adjListArr has been sorted, the index present the end time in 1st dfs. */
        timeIndex = vertexToTime[i];
        if((dir_graph_transpose->adjListArr[timeIndex]).num_members == 0)
            /* num_members == 0 means no such vertex in the clause. */
            continue;
        leaderU = (dir_graph_transpose->adjListArr[timeIndex]).leader;
        if(leaderU == -1)
            /* leaderU == -1 means that u has never been visited. */
            continue;
        leaderNotU = (dir_graph_transpose->adjListArr[vertexToTime[i + numberOfVertice]]).leader;
        if(leaderU == leaderNotU){
            printf("u = %d, leaderU = %d\n", i, leaderU);
            return 0;
        }
    }
    return 1;
}