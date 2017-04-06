#include <stdio.h>
void swap(int *a, int *b){
  	int tmp = *a;
  	*a = *b;
  	*b = tmp;                                                                                             
}

int partition(int array[], int left, int right, int pivotIndex){
	int pivotValue = array[pivotIndex], storeIndex = left;
	swap(&array[pivotIndex], &array[right]);
	
	for(int i = left; i < right; i++)
		if(array[i] <= pivotValue){
			swap(&array[storeIndex], &array[i]);
			storeIndex++;
		}
	swap(&array[storeIndex], &array[right]);
	return storeIndex;
}

void quickSort(int array[], int left, int right){
	if(right > left){
		int newPivotIndex = partition(array, left, right, left);
		quickSort(array, left, newPivotIndex - 1);
		quickSort(array, newPivotIndex + 1, right);
	}
}

void main(void){
	FILE *inFile, *wFile;
	int size = 10000;
	int inputArray[size];
	int i = 0;
	inFile = fopen("QuickSort.txt", "r");
	wFile = fopen("sorted.txt", "w");
	if(!inFile)
		printf("Fail to open file\n");
	else
		printf("Open file successfully!\n");
	for(i = 0; i < size; i++)
		fscanf(inFile, "%d", &inputArray[i]);
	quickSort(inputArray, 0, size - 1);
	for(i = 0; i < size - 1; i++)
		fprintf(wFile, "%d\n", inputArray[i]);
	fprintf(wFile, "%d", inputArray[size - 1]);
	fclose (inFile);
	fclose (wFile);
}