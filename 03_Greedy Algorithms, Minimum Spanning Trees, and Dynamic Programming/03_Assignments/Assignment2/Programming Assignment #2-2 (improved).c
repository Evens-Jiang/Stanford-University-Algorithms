/*
	Number Of Clusters = 6118.
	CPU: i5-6500
	Running time = 126.578 (sec)
*/
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "union_find.h"

typedef struct hamming_vertexvertex{
	int leader, reached;
}hamming_vertex_t, *hamming_vertex_p;

int calculator(int *hammingDistance, int numberOfBitsPerLable);
int hammingDistanceFill(hamming_vertex_p hammingVertex, int *hammingDistance, int vertex, int numberOfBitsPerLable, int numberOfClusters, vertex_p vertices);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("clustering_big.txt", "r");
    int numberOfNodes, numberOfClusters, numberOfBitsPerLable, distance, i = 0;
    hamming_vertex_p hammingVertex;
    int *hammingDistance, vertex = 1;
    
    if(!inFile){
    	printf("Fail to open file\n");
        return;
    }
    else
    	printf("Open file successfully!\n");
    
    fscanf(inFile, "%d %d", &numberOfNodes, &numberOfBitsPerLable);
    printf("Number of nodes = %d\nNumber of bits per lable = %d\n\n", numberOfNodes, numberOfBitsPerLable);
    distance = (int)pow(2, numberOfBitsPerLable);
    printf("distance = %d\n", distance);
   	if((hammingDistance = malloc(numberOfBitsPerLable * sizeof(int))) == NULL)
   		printf("Malloc hammingDistance failed.\n");;
    if((hammingVertex = malloc(distance * sizeof(hamming_vertex_t))) == NULL){
    	printf("Malloc hammingVertex failed.\n");
    	return;
    }

    for(i = 0; i < distance; i++){
    	hammingVertex[i].leader = 0;
    	hammingVertex[i].reached = 0;
    }

    vertex_p vertices = malloc((numberOfNodes + 1) * sizeof(vertex_t));
    for(i = 0; i <= numberOfNodes; i++)
        MakeSet(&vertices[i]);

    numberOfClusters = numberOfNodes;
    printf("numberOfClusters = %d\n", numberOfClusters);
    printf("Start hammingDistanceFill\n");
    i = 0;
    while(fscanf(inFile, "%d", &hammingDistance[i]) != EOF){
    	i++;
    	if(i == numberOfBitsPerLable){
    		// printf("vertex = %d\n", vertex);
    		numberOfClusters = hammingDistanceFill(hammingVertex, hammingDistance, vertex, numberOfBitsPerLable, numberOfClusters, vertices);
    		i = 0;
    		vertex++;
    	}
    }

    printf("Number Of Clusters = %d\n", numberOfClusters);
    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

int calculator(int *hammingDistance, int numberOfBitsPerLable){
	int i, result = 0;
	for(i = 0; i <numberOfBitsPerLable; i++){
		result += pow(2, i) * hammingDistance[i];
	}
	return result;
}

int hammingDistanceFill(hamming_vertex_p hammingVertex, int *hammingDistance, int vertex, int numberOfBitsPerLable, int numberOfClusters, vertex_p vertices){
	int result, temp, i = 0, j = 0, k = 0;
	int *hammingDistanceTemp = malloc(numberOfBitsPerLable * sizeof(int));

	result = calculator(hammingDistance, numberOfBitsPerLable);

	/* Update distance = 0 in hammingVertex */
	if(hammingVertex[result].leader == 0){
		// printf("distance = 0\n");
		// printf("result = %d\n", result);
		hammingVertex[result].leader = vertex;
		hammingVertex[result].reached = 1;
	}
	else{
		// printf("distance = 0\n");
		// printf("result = %d\n", result);
		temp = numberOfClusters;
		hammingVertex[result].reached = 1;
		numberOfClusters = Union(&vertices[hammingVertex[result].leader], &vertices[vertex], numberOfClusters);
		// if(numberOfClusters != temp){
		// 	printf("distance = 0\n");
		// 	printf("result = %d\n", result);
		// 	printf("numberOfClusters = %d\n", numberOfClusters);
		// }
		// else
		// 	printf("numberOfClusters = temp\n");
	}
	/* Update distance = 1 in hammingVertex */
	for(i = 0; i < numberOfBitsPerLable; i++){
		for(j = 0; j < numberOfBitsPerLable; j++){
			if(j == i){
				if(hammingDistance[j])
					hammingDistanceTemp[j] = 0;
				else
					hammingDistanceTemp[j] = 1;
			}
			else
				hammingDistanceTemp[j] = hammingDistance[j];
		}
		result = calculator(hammingDistanceTemp, numberOfBitsPerLable);
		if(hammingVertex[result].leader == 0){
			// printf("distance = 1\n");
			// printf("result = %d\n", result);
			hammingVertex[result].leader = vertex;
		}
		else{
			if(hammingVertex[result].reached){
				// printf("distance = 1\n");
				// printf("result = %d\n", result);
				temp = numberOfClusters;
				numberOfClusters = Union(&vertices[hammingVertex[result].leader], &vertices[vertex], numberOfClusters);
				// if(numberOfClusters != temp){
				// 	printf("distance = 1\n");
				// 	printf("result = %d\n", result);
				// 	printf("numberOfClusters = %d\n", numberOfClusters);
				// }
				// else
				// 	printf("numberOfClusters = temp\n");
			}
		}
	}
	/* Update distance = 2 in hammingVertex */
	for(i = 0; i < numberOfBitsPerLable; i++){
		for(j = 0; j < i; j++)
			hammingDistanceTemp[j] = hammingDistance[j];
		if(hammingDistance[i])
			hammingDistanceTemp[i] = 0;
		else
			hammingDistanceTemp[i] = 1;
		for(k = i + 1; k < numberOfBitsPerLable; k++){
			for(j = i + 1; j < numberOfBitsPerLable; j++){
				if(j == k){
					if(hammingDistance[j])
						hammingDistanceTemp[j] = 0;
					else
						hammingDistanceTemp[j] = 1;
				}
				else
					hammingDistanceTemp[j] = hammingDistance[j];
			}
			result = calculator(hammingDistanceTemp, numberOfBitsPerLable);
			if(hammingVertex[result].leader == 0){
				// printf("distance = 2\n");
				// printf("result = %d\n", result);
				hammingVertex[result].leader = vertex;
			}
			else{
				if(hammingVertex[result].reached){
					// printf("distance = 2\n");
					// printf("result = %d\n", result);
					temp = numberOfClusters;
					numberOfClusters = Union(&vertices[hammingVertex[result].leader], &vertices[vertex], numberOfClusters);
					// if(numberOfClusters != temp){
					// 	printf("distance = 2\n");
					// 	printf("result = %d\n", result);
					// 	printf("numberOfClusters = %d\n", numberOfClusters);
					// }
					// else
					// 	printf("numberOfClusters = temp\n");
				}
			}
		}
	}
	// printf("\n");
	return numberOfClusters;
}