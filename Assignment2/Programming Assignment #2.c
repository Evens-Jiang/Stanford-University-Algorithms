#include <stdio.h>

int mergeSortRecursive(int arr[], int result[], int start, int end) {
	if(start >= end)
		return 0;
	int start1 = start, end1 = ((end - start) >> 1 )+ start;
	int start2 = end1 + 1, end2 = end;
	int k = start;
	long long int inversionCounter = 0;
	inversionCounter += mergeSortRecursive(arr, result, start1, end1);
	inversionCounter += mergeSortRecursive(arr, result, start2, end2);
	while(start1 <= end1 && start2 <= end2){
		if(arr[start1] < arr[start2]) {
			result[k] = arr[start1];
			start1++;
		}
		else{
			result[k] = arr[start2];
			start2++;
			inversionCounter++;
		}
		k++;
//		result[k] = arr[start1] < arr[start2] ? arr[start1] : arr[start2];
	}
	while(start1 <= end1){
		result[k] = arr[start1];
		k++; start1++;
	}
	while(start2 <= end2){
		result[k] = arr[start2];
		k++; start2++;
	}
	for(k = start; k <= end; k++)
		arr[k] = result[k];
	return inversionCounter;
}

int mergeSort(int arr[], const int length) {
	int result[length];
	return mergeSortRecursive(arr, result, 0, length - 1);
}

int main() {
	FILE *pFile;
	int inputArray[100000];//, outputArray[100000];
	pFile = fopen("123.txt", "r");
	if(!pFile)
		printf("Fail to open file\n");
	else
		printf("Open file successfully!\n");
	fread(inputArray, 400000, 4, pFile);
	printf("Inversion count = %d\n", mergeSort(inputArray, sizeof(inputArray) / sizeof(int)));
	fclose (pFile);
   	return 0;
}