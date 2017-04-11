#include <stdio.h>
void main(){
	FILE *inFile = fopen("kargerMinCut.txt", "r");
	int size = 200;
	int inputArray[size][size - 1];
	int i = 0, j = 0, check = 0;
	if(!inFile)
		printf("Fail to open file\n");
	else
		printf("Open file successfully!\n");
//	for(i = 0; i < 5; i++){
		for(j = 0; j < 100; j++){
			fscanf(inFile, "%d", &inputArray[i][j]);
			printf("%3d ", inputArray[i][j]);
		}
		printf("\n");
//	}
	fclose(inFile);
}