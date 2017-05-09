/*
    Median Maintenance Algorithm
	
	Algorithm ( naive ):
		sum=0, input a[n]
		for each input a[i]
			Sort a[0..i]
			sum += a[i/2]
		print sum % 10000
*/
/*	
	The median maintenance is 1213.
	Running time is about 5.9 seconds.
*/
#include <stdio.h>
#include <time.h>

#define SIZE 10000

void swap(int *a, int *b);
void min_heapify(int array[], int start, int end);
void bubbleUp(int array[], int son);
int extractMin(int array[], int end);
int medianMaintenance(int array[], int end);

void main(void){
	clock_t begin = clock();
    FILE *inFile = fopen("Median.txt", "r");
	int array[SIZE] = {0};
	int i = 0;
	int sum = 0;
	
	if(!inFile)
		printf("Fail to open file\n");
	else
		printf("Open file successfully!\n");
	
	while(fscanf(inFile, "%d", &array[i]) != EOF){
		bubbleUp(array, i);
		sum += medianMaintenance(array, i);
		i++;
	}
	sum = sum % 10000;
    printf("Sum = %d\n", sum);
    fclose(inFile);
	clock_t end = clock();
	printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void min_heapify(int array[], int start, int end) {
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) {
		if (son + 1 <= end && array[son] > array[son + 1])
			son++;
		if (array[dad] < array[son])
			return;
		else {
			swap(&array[dad], &array[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void bubbleUp(int array[], int son){
	int dad;
	while(son != 0){
		if(son % 2)
			dad = son / 2;
		else
			dad = son / 2 - 1;
		if(array[son] < array[dad])
			swap(&array[dad], &array[son]);
		else
			return;
		son = dad;
	}
	return;
}

int extractMin(int array[], int end){
	int min = array[0];
	swap(&array[0], &array[end]);
	min_heapify(array, 0, end - 1);
	return min;
}

int medianMaintenance(int array[], int end){
	int length = end, number = length / 2 + 1;
	int i = 0;
	int median;
	for(i = 0; i < number; i++){
		median = extractMin(array, length);
		length--;
	}
	
	for(i = (end - 1) / 2; i >= 0; i--)
		min_heapify(array, i, end);
	
	return median;
}