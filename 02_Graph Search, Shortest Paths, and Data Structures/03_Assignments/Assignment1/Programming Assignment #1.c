#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

struct Adjacency {
	int point;
	int adjList[SIZE + 1];
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
	
	if(!inFile)
		printf("Fail to open file\n");
	else
		printf("Open file successfully!\n");
	
	fclose(inFile);
}