#include <stdio.h>
#include <math.h>

#define SIZE 200

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
void adjacencyList(int array[][SIZE + 1], FILE *file){
	char temp[3 * SIZE];
	int i = 0, j = 0, digit = 1;
	int row = 0, col = 0, colCounter = 0;
	int rowCheck = 1;
	
	for(i = 0; i < SIZE; i++){
		if (fgets (temp , SIZE , file) != NULL)
       		while(temp[j] != '\0'){
				if(rowCheck){
					if(temp[j + 1] == 9){
						row = convertCharToInt(&temp[j - digit + 1], digit);
						digit = 1;
						rowCheck = 0;
					}
					else if(temp[j] == 9){}
					else
						digit++;
				}
				else{
					if(temp[j + 1] == 9){
						array[row][col] = convertCharToInt(&temp[j - digit + 1], digit);
						digit = 1;
					}
					else if(temp[j] == 9 && colCounter == 0){}
					else if(temp[j] == 9)
						col++;
					else if(temp[j] == 10)
						col = 0;
					else
						digit++;
					colCounter++;
				}
				j++;
			}
		colCounter = 0;
		j = 0;
		rowCheck = 1;
	}
//	j = 0;
//	for(i = 1; i <= SIZE; i++){
//		printf("%3d\n", i);
//		while(array[i][j] != 0){
//			printf("%3d ", array[i][j]);
//			j++;
//		}
//		printf("\n\n");
//		j = 0;
//	}
}
void adjacencyMatrix(int array[][SIZE + 1], FILE *file){
	char temp[3 * SIZE];
	int i = 0, j = 0, digit = 1;
	int row = 0, col = 0;
	int rowCheck = 1;
	for(i = 0; i < SIZE; i++){
		if ( fgets (temp , SIZE , file) != NULL )
       		while(temp[j] != '\0'){
				if(rowCheck){
					if(temp[j + 1] == 9){
						row = convertCharToInt(&temp[j - digit + 1], digit);
						digit = 1;
						rowCheck = 0;
					}
					else if(temp[j] == 9){}
					else
						digit++;
				}
				else{
					if(temp[j + 1] == 9){
						col = convertCharToInt(&temp[j - digit + 1], digit);
						array[row][col] = 1;
						digit = 1;
					}
					else if(temp[j] == 9 || temp[j] == 10){}
					else
						digit++;
				}
				j++;
			}
		j = 0;
		rowCheck = 1;
	}
//	j = 0;
//	for(i = 1; i <= row; i++){
//		printf("%3d ", i);
//		while(j != 200){
//			printf("%3d ", array[i][j]);
//			j++;
//		}
//		printf("\n\n");
//		j = 0;
//	}
}
void main(){
	FILE *inFile = fopen("kargerMinCut.txt", "r");
	int inputArray[SIZE + 1][SIZE + 1] = {0};
	int i = 0, j = 0;
	if(!inFile)
		printf("Fail to open file\n");
	else
		printf("Open file successfully!\n");
	adjacencyList(inputArray, inFile);
//	adjacencyMatrix(inputArray, inFile);
	
	fclose(inFile);
}