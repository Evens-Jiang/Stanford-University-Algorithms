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
	CPU: i5-6500
	executing 100 times.
	Average running time is about 3.902 seconds. (Using min heap.)
	Average running time is about 7.252 seconds. (Naive method, using heap sort sorting the array every time.)
*/
#include <stdio.h>
#include <time.h>

#define SIZE 10000

void swap(int *a, int *b);
void min_heapify(int array[], int start, int end);
// void heap_sort(int arr[], int len);
void bubbleUp(int array[], int son);
void bubbleDown(int array[], int end);
int extractMin(int array[], int end);
int medianMaintenance(int array[], int end);

double median(void){
	clock_t begin = clock();
	FILE *inFile = fopen("Median.txt", "r");
	int array[SIZE] = {0};
	int i = 0;
	int sum = 0;
	
	// if(!inFile)
	// 	printf("Fail to open file\n");
	// else
	// 	printf("Open file successfully!\n");
	
	while(fscanf(inFile, "%d", &array[i]) != EOF){
			/*Median maintenance*/
		bubbleUp(array, i);
		sum += medianMaintenance(array, i);
			/*Naive method*/
		// heap_sort(array, i + 1);
		// sum += array[i - i / 2];
		i++;
	}
	sum = sum % 10000;
	// printf("Sum = %d\n", sum);
	fclose(inFile);
	clock_t end = clock();
	// printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
	return (double)(end - begin) / CLOCKS_PER_SEC;
}


void main(void){
	int i;
	double sum = 0;
	for(i = 0; i < 100; i++)
		sum += median();
	sum /= 100;
	printf("Average Running Time = %.3f\n", sum);
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

/*void heap_sort(int arr[], int len) {
	int i;
	for (i = len / 2 - 1; i >= 0; i--)
		min_heapify(arr, i, len - 1);
	for (i = len - 1; i > 0; i--) {
		swap(&arr[0], &arr[i]);
		min_heapify(arr, 0, i - 1);
	}
}*/

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

void bubbleDown(int array[], int end){
	int dad = 0, son = dad * 2 + 1;
	while(son <= end){
		if(son + 1 <= end && array[son + 1] < array[son])
			son = son + 1;
		if(array[dad] > array[son])
			swap(&array[dad], &array[son]);
		else
			return;
		dad = son;
		son = son * 2 + 1;
	}
	return;
}

int extractMin(int array[], int end){
	int min = array[0];
	swap(&array[0], &array[end]);
//	min_heapify(array, 0, end - 1);
	bubbleDown(array, end - 1);
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