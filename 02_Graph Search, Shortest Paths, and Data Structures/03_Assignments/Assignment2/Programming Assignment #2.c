/*
Dijkstra's algorithm

*/
#include <stdio.h>
#include <stdlib.h>

void main(){
	FILE *inFile = fopen("dijkstraData.txt", "r");
	int start, end;

	if(!inFile)
		printf("Fail to open file\n\n");
	else
		printf("Open file successfully!\n\n");

	fclose(inFile);
}