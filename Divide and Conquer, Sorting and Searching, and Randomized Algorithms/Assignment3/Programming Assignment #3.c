#include <stdio.h>
void swap(int *a, int *b){
  	int tmp = *a;
  	*a = *b;
  	*b = tmp;                                                                                             
}

int partition(int array[], int left, int right, int pivotIndex, int *counter){
	int pivotValue = array[pivotIndex], compareIndex = left;
	*counter += (right - left);
	swap(&array[pivotIndex], &array[right]);
	for(int i = left; i < right; i++)
		if(array[i] < pivotValue){
			swap(&array[compareIndex], &array[i]);
			compareIndex++;
		}
	swap(&array[compareIndex], &array[right]);
	return compareIndex;
}

void quickSort(int array[], int left, int right, int *counter){
	if(right > left){
		int newPivotIndex = partition(array, left, right, left, counter);
		quickSort(array, left, newPivotIndex - 1, counter);
		quickSort(array, newPivotIndex + 1, right, counter);
	}
}

void main(void){
	FILE *inFile, *wFile;
	int size = 10000;
	int inputArray[size];
	int i = 0, counter = 0;
	int *counterPtr;
	counterPtr = &counter;
	inFile = fopen("QuickSort.txt", "r");
	wFile = fopen("sorted.txt", "w");
	if(!inFile)
		printf("Fail to open file\n");
	else
		printf("Open file successfully!\n");
	for(i = 0; i < size; i++)
		fscanf(inFile, "%d", &inputArray[i]);
	quickSort(inputArray, 0, size - 1, counterPtr);
	for(i = 0; i < size - 1; i++)
		fprintf(wFile, "%d\n", inputArray[i]);
	fprintf(wFile, "%d", inputArray[size - 1]);
	printf("Comparison counts = %d\n", counter);
	fclose (inFile);
	fclose (wFile);
}