#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 58726
int INIT = 0;

struct Adjacency {
	int vertex;
	int size;
	int *adjList = malloc(INIT * sizeof(int));
};

void swap(int *a, int *b){
  	int tmp = *a;
  	*a = *b;
  	*b = tmp;  
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

void main(){
	FILE *inFile = fopen("SCC.txt", "r");
	int Adjacency array[SIZE];
	int temp[100] = {0};
	int vertex1, vertex2;
	int i = 1, j = 1, k = 1;

	for (i = 0; i <= SIZE; ++i){
		array[i].vertex = i;
		array[i].size = 0;
	}

	if(!inFile)
		printf("Fail to open file\n");
	else
		printf("Open file successfully!\n");
	i = 1;
	while(fscanf(inFile, "%d %d", &vertex1, &temp[j]) != EOF){
		if(vertex1 == array[i].vertex){
			j++;
		}
		else{
			array[i].size = j;
			for(k = 1; k <= j; k++){
				array[i].adjList[k] = temp[k];
				temp[k] = 0;
			}
			j = 1;
			i++;
			j++;
		}
	}
	array[i].size = j;
	for(k = 1; k <= j; k++){
		array[i].adjList[k] = temp[k];
		temp[k] = 0;
	}
	j = 1;

	for(i = 1; i <= SIZE; i++){
		printf("vertex = %d\n", array[i].vertex);
		while(array[i].adjList[j]){
			printf("%6d ", array[i].adjList[j]);
		}
		printf("\n\n");
	}

	fclose(inFile);
}