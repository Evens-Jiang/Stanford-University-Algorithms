#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 200
int COUNTER = 200;

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
void makeAdjacencyList(struct Adjacency list[SIZE + 1], FILE *file){
	char temp[10 * SIZE];
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
						col = convertCharToInt(&temp[j - digit + 1], digit);
						list[row].adjList[col]++;
						digit = 1;
					}
					else if(temp[j] == 9 && colCounter == 0)
						list[row].point = row;
					else if(temp[j] == 9 || temp[j] == 10)
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
//	for(i = 1; i <= SIZE; i++){
//		printf("list[%d].point = %d\n", i, list[i].point);
//		for(j = 1; j <= SIZE; j++)
//			printf("list[%d].adjList[%d] = %3d\n", i, j, list[i].adjList[j]);
//		printf("\n\n");
//	}
}
void makeAdjacencyMatrix(int array[][2 * SIZE], FILE *file){
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
void randomSelection(struct Adjacency list[SIZE + 1], int pick[2]){
	srand(time(NULL));
	int randomRow = rand() % COUNTER + 1, randomCol;
	int length = 0, temp[SIZE] = {0};
	int i;
	for(i = 1; i <= SIZE; i++){
		if(list[randomRow].adjList[i] > 0){
			temp[length] = i;
			length++;
		}
	}
	randomCol = rand() % length;
	pick[0] = randomRow;
	pick[1] = temp[randomCol];
//	printf("randomRow = %d\n", randomRow);
//	printf("randomCol = %d\n", randomCol);
//	printf("length = %d\n", length);
//	i = 0;
//	while(temp[i] != 0){
//		printf("%3d ", temp[i]);
//		i++;
//	}
//	printf("\n\n");
//	printf("point = %d\n", list[randomRow].point);
//	printf("v2 = %d\n", temp[randomCol]);
}
void contraction(struct Adjacency list[SIZE + 1], int edge[2]){
	int rowSize = COUNTER;
	int row1 = edge[0], row2 = 1;
	int v1 = list[row1].point, v2 = edge[1];
	int i = 1, j = 1;

//	printf("v1 = %d, v2 = %d\n", v1, v2);
	
	//find the row2
	while(list[row2].point != v2 && row2 <= COUNTER)
		row2++;
	
	//switch the smaller point
	if(row1 > row2){
		swap(&row1, &row2);
		v1 = list[row1].point, v2 = list[row2].point;
//		printf("v1 = %d, v2 = %d\n", v1, v2);
	}
	
	//contraction
	list[row1].adjList[v2] = -1;
	list[row2].adjList[v1] = -1;
	for(i = 1; i <= SIZE; i++){
		if(list[row2].adjList[i] > 0)
			list[row1].adjList[i] += list[row2].adjList[i];
	}
	for(i = 1; i <= SIZE; i++){
		if(i == v1)
			continue;
		if(list[i].adjList[v2] > 0){
			list[i].adjList[v1] += list[i].adjList[v2];
		}
		list[i].adjList[v2] = -1;
	}
//	printf("point = %d\n", list[row1].point);
//	printf("adjList = {\n");
//	for(i = 1; i <= 10; i++){
//		printf("%3d ", i);
//	}
//	printf("\n");
//	for(i = 1; i <= SIZE; i++){
//		if(i % 10 == 1)
//			printf("%d ", i / 10);
//		printf("%3d ", list[row1].adjList[i]);
//		if(i % 10 == 0)
//			printf("\n");
//	}
//	printf("}");
	
	//move last row to row2
	list[row2].point = list[COUNTER].point;
	for(i = 1; i <= SIZE; i++)
		list[row2].adjList[i] = list[COUNTER].adjList[i];
	COUNTER--;
}

int findMinCut(struct Adjacency list[SIZE + 1]){
	int pickedEdge[2];
	int counter1 = 0, counter2 = 0,i = 1;
	int last = 2;
	while(COUNTER > last){
		randomSelection(list, pickedEdge);
		contraction(list, pickedEdge);
	}
	for(i = 1; i <= SIZE; i++){
		if(list[last].adjList[i] > 0)
			counter1 += list[last].adjList[i];
	}
	for(i = 1; i <= SIZE; i++){
		if(list[1].adjList[i] > 0)
			counter2 += list[1].adjList[i];
	}
//	printf("counter2 = %d\n", counter2);
	return counter1;
}

void main(){
	FILE *inFile = fopen("kargerMinCut.txt", "r");
	struct Adjacency list[SIZE + 1];
	int i = 0, j = 0, count = 0, k = 0;
	int minCut = 1000, t = 0, fail = 0;
	
	for(i = 0; i <= SIZE; i++){
		list[i].point = 0;
		for(j = 0; j <= SIZE; j++){
			if(j == i)
				list[i].adjList[j] = -1;
			else
				list[i].adjList[j] = 0;
		}
	}
	
	if(!inFile)
		printf("Fail to open file\n");
	else
		printf("Open file successfully!\n");
	makeAdjacencyList(list, inFile);
	minCut = findMinCut(list);
	printf("minCut = %d\n", minCut);
//	for(k = 0; k <= 500; k++){
//		t = findMinCut(list);	
//		if(t < minCut){
//			minCut = t;
//			printf("minCut = %d\n", minCut);
//			count++;
//		}
//		else{
//			fail++;
//		}
//		printf("t = %d\n", t);
//		COUNTER = 200;
//		for(i = 0; i <= SIZE; i++){
//			list[i].point = 0;
//			for(j = 0; j <= SIZE; j++){
//				if(j == i)
//					list[i].adjList[j] = -1;
//				else
//					list[i].adjList[j] = 0;
//			}
//		}
//		inFile = fopen("kargerMinCut.txt", "r");
//		makeAdjacencyList(list, inFile);
//	}
//	printf("fail = %d\n", fail);
//	printf("counter = %d", count);
	fclose(inFile);
}