#include <stdio.h>
#include <math.h>

#define SIZE 200

int convertCharToInt(char *c, int digit){
	int number = 0, counter = digit;
	if(counter == 1)
		return *c - 48;
	while(counter){
		number += (*c - 48) * pow(10, --counter);
		c++;
	}
	if(digit % 2)
		number++;
	return number;
}
void main(){
	FILE *inFile = fopen("kargerMinCut.txt", "r");
	int inputArray[SIZE][SIZE] = {0};
	char temp[SIZE];
	int i = 0, j = 0, digit = 1, row = 1;
	if(!inFile)
		printf("Fail to open file\n");
	else
		printf("Open file successfully!\n");
	
	for(i = 0; i < 5; i++){
		if ( fgets (temp , SIZE , inFile) != NULL )
       		while(temp[j] != '\0'){
				if(temp[j] == 9 || temp[j] == 10){
					printf("%3d", convertCharToInt(&temp[j], digit));
					digit = 1;
				}
				else
					printf("%3d", convertCharToInt(&temp[j], digit));
				j++;
			}
		j = 0;
		row++;
		printf("\n");
	}
	fclose(inFile);
}