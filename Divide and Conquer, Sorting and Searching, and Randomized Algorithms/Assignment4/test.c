#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 200
int COUNTER = 200;

struct Adjacency {
	int point = 0;
	int adjList[SIZE + 1] = {0};
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
void MakeadjacencyList(struct Adjacency list[SIZE + 1], FILE *file){
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
						list[row].point = convertCharToInt(&temp[j - digit + 1], digit);
						digit = 1;
					}
					else if(temp[j] == 9 && colCounter == 0){
						list[row].adjList[col] = row;
						col++;
					}
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
	j = 0;
	for(i = 1; i <= SIZE; i++){
		printf("list[%d].point\n", list[i].point);
		while(list[i].adjList[j] != 0){
			printf("%3d ", list[i].adjList[j]);
			j++;
		}
		printf("\n\n");
		j = 0;
	}
}
void MakeAdjacencyMatrix(int array[][2 * SIZE], FILE *file){
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
	// j = 0;
	// for(i = 1; i <= row; i++){
	// 	printf("%3d ", i);
	// 	while(j != 200){
	// 		printf("%3d ", array[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n\n");
	// 	j = 0;
	// }
}
void randomSelection(int array[][2 * SIZE], int pick[2]){
	srand(time(NULL));
	int randomRow = rand() % COUNTER + 1, randomCol;
	int length = 1;
	while(array[randomRow][length] != 0){
		length++;
	}
	length--;
	randomCol = rand() % length + 1;
	pick[0] = randomRow;
	pick[1] = randomCol;
}
void contraction(int array[][2 * SIZE], int edge[2]){
	int rowSize = COUNTER, row1 = edge[0], col1 = edge[1], row2 = 1, col2 = 1;
	int i = 1, j = 1;
	int tempArray[2 * SIZE] = {0};
	int v1, v2;
//	printf("row1 = %d\n", row1);
//	printf("col1 = %d\n", col1);
	printf("v1 = %d, v2 = %d\n", array[row1][0], array[row1][col1]);
	
	//find the match row2
	while(array[row2][0] != array[row1][col1] && row2 <= COUNTER)
		row2++;
	//find the match col2
	while(array[row2][col2] != array[row1][0] && array[row2][col2] != 0)
		col2++;
//	printf("row2 = %d\n", row2);
//	printf("col2 = %d\n", col2);
	printf("v2 = %d, v1 = %d\n\n", array[row2][0], array[row2][col2]);
	
	//switch the smaller point
	if(row1 > row2){
		swap(&row1, &row2);
		swap(&col1, &col2);
	}
	v1 = array[row1][0];
	v2 = array[row2][0];
	
//	printf("array[%d] = {", array[row1][0]);
//	while(array[row1][i] != 0){
//		printf("%3d ", array[row1][i]);
//		i++;
//	}
//	printf("}\n\n");
//	i = 1;
//	
//	printf("array[%d] = {", array[row2][0]);
//	while(array[row2][i] != 0){
//		printf("%3d ", array[row2][i]);
//		i++;
//	}
//	printf("}\n\n");
//	i = 1;
	
	//contraction
	tempArray[0] = array[row1][0];
	while(array[row1][i] != 0){
		if(array[row1][i] != array[row1][col1] && array[row1][i] != array[row1][0] && array[row1][i] != -1){
			tempArray[j] = array[row1][i];
			j++;
		}
		i++;
	}
	i = 1;
	while(array[row2][i] != 0){
		if(array[row2][i] != array[row2][col2] && array[row2][i] != array[row2][0] && array[row1][i] != -1){
			tempArray[j] = array[row2][i];
			j++;
		}
		i++;
	}
	
//	i = 1;
//	printf("tempArray = {%d ", tempArray[0]);
//	while(tempArray[i] != 0){
//		printf("%3d ", tempArray[i]);
//		i++;
//	}
//	printf("}\n\n");
	
	//clear row1 and row2
	for(i = 0; i < 2 * SIZE; i++){
		array[row1][i] = 0;
		array[row2][i] = 0;
	}

	//duplicate temp to row1
	i = 0;
	while(tempArray[i] != 0){
		if(i > 2 * SIZE){
			printf("row1\n");
			printf("i > 2 * SIZE\n\n");
			return;
		}
		array[row1][i] = tempArray[i];
		i++;
	}
	
//	i = 1;
//	printf("array[%d] = {%d ", row1, array[row1][0]);
//	while(array[row1][i] != 0){
//		printf("%3d ", array[row1][i]);
//		i++;
//	}
//	printf("}\n\n");
	
	//move last row to row2
	i = 0;
	while(array[COUNTER][i] != 0){
		array[row2][i] = array[COUNTER][i];
		i++;
	}
	
	//clear the point in other row
	j = 1;
	for(i = 1; i <= COUNTER; i++){
		while(array[i][j] != 0){
			if(array[i][j] == v2)
				array[i][j] = v1;
			j++;
		}
		j = 1;
	}
	COUNTER--;
	printf("COUNTER = %d\n\n", COUNTER);
}

int findMinCut(int array[][2 * SIZE]){
	int pickedEdge[2];
	int counter = 1;
	int last = 2;
	while(COUNTER > last){
		randomSelection(array, pickedEdge);
		contraction(array, pickedEdge);
	}
	printf("array[%d] = { ", last);
	while(array[last][counter] != 0){
		printf("%3d ", array[last][counter]);
		counter++;
	}
	printf("}\n\n");
	return counter;
}

void main(){
	FILE *inFile = fopen("kargerMinCut.txt", "r");
	struct Adjacency list[SIZE + 1];
	int i = 0, j = 0;
	int minCut;
	
	for(i = 0; i <= SIZE; i++){
		list[i].point = i;
		for(j = 0; j <= SIZE; j++){
			list[i].adjList[j] = 0;
		}
	}
	
	if(!inFile)
		printf("Fail to open file\n");
	else
		printf("Open file successfully!\n");
	MakeadjacencyList(inputArray, inFile);
//	minCut = findMinCut(inputArray);
//	printf("minCut = %d", minCut);
	fclose(inFile);
}