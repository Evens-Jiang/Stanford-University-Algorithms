#include <stdio.h>
long long mergeSortRecursive(int arr[], int result[], int start, int end) {
	if(start >= end)
		return 0;
	int start1 = start, end1 = ((end - start) >> 1 ) + start;
	int start2 = end1 + 1, end2 = end;
	int k = start, i = 0;
	long long inversionCounter = 0;
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
			for(i = 0; i < end1 - start1 + 1; i++)
				inversionCounter += 1;
		}
		k++;
//		result[k] = arr[start1] < arr[start2] ? arr[start1] : arr[start2];
	}
	while(start1 <= end1){
		result[k] = arr[start1];
		k++; 
		start1++;
	}
	while(start2 <= end2){
		result[k] = arr[start2];
		k++; 
		start2++;
	}
	for(k = start; k <= end; k++)
		arr[k] = result[k];
	return inversionCounter;
}
long long mergeSort(int arr[], const int length) {
	int result[length];
	return mergeSortRecursive(arr, result, 0, length - 1);
}
int main() {
	FILE *pFile, *wFile;
	int inputArray[100000];
	pFile = fopen("inputIntegers.txt", "r");
	wFile = fopen("sortResult.txt", "w");
	if(!pFile)
		printf("Fail to open file\n");
	else
		printf("Open file successfully!\n");
	for(int i = 0; i < 100000; i++)
		fscanf(pFile, "%d", &inputArray[i]);
	printf("Inversion count = %lld\n", mergeSort(inputArray, sizeof(inputArray) / sizeof(int)));
	for(int i = 0; i < 100000; i++)
		fprintf(wFile, "%d\n", inputArray[i]);
	fclose (pFile);
	fclose (wFile);
   	return 0;
}