/*
    Greedy Algorithm.
    Decreasing order of the difference (weight - length).
    If equalization in difference (weight - length), using higher weight first.
    
    Weighted completion time = 69119377652.
*/
#include <stdio.h>
#include <time.h>

void swap(int *a, int *b);
int partition(int arr[][3], int left, int right, int pivotIndex);
int medianOfThree(int arr[][3], int left, int right);
void quickSort(int arr[][3], int left, int right);
__int64 weightedCompletionTime(int arr[][3], int length);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("jobs.txt", "r");
    int numberOfJobs, i = 0;
    
    if(!inFile){
    	printf("Fail to open file\n");
        return;
    }
    else
    	printf("Open file successfully!\n");
    
    fscanf(inFile, "%d", &numberOfJobs);
    printf("Number of jobs = %d\n", numberOfJobs);
    int jobArray[numberOfJobs][3];
    while(fscanf(inFile, "%d %d", &jobArray[i][0], &jobArray[i][1]) != EOF){
        jobArray[i][2] = jobArray[i][0] - jobArray[i][1];
        i++;
    }
//    printf("  No. weight length W-L\n");
//    for(i = 0; i < numberOfJobs; i++)
//        printf("%5d    %3d     %2d %3d\n", i, jobArray[i][0], jobArray[i][1], jobArray[i][2]);
    quickSort(jobArray, 0, numberOfJobs - 1);
//    printf("  No. weight length W-L\n");
//    for(i = 0; i < numberOfJobs; i++)
//        printf("%5d    %3d     %2d %3d\n", i, jobArray[i][0], jobArray[i][1], jobArray[i][2]);
    
    fclose(inFile);
    printf("weighted completion time = %lld\n", weightedCompletionTime(jobArray, numberOfJobs));
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

void swap(int *a, int *b){
  	int tmp = *a;
  	*a = *b;
  	*b = tmp;  
}
int partition(int arr[][3], int left, int right, int pivotIndex){
	int pivotValue = arr[pivotIndex][2], pivotWeight = arr[pivotIndex][0];
    int compareIndex = left + 1;
    int j = 0;
    for(j = 0; j < 3; j++)
	   swap(&(arr[pivotIndex][j]), &(arr[left])[j]);
	for(int i = left + 1; i <= right; i++){
		if(arr[i][2] > pivotValue){
            for(j = 0; j < 3; j++)
			     swap(&(arr[i][j]), &(arr[compareIndex][j]));
			compareIndex++;
		}
        if(arr[i][2] == pivotValue && arr[i][0] > pivotWeight){
            for(j = 0; j < 3; j++)
			     swap(&(arr[i][j]), &(arr[compareIndex][j]));
			compareIndex++;
		}
	}
    --compareIndex;
    for(j = 0; j < 3; j++)
	   swap(&(arr[compareIndex][j]), &(arr[left][j]));
	return compareIndex;
}
int medianOfThree(int arr[][3], int left, int right){
	int length = right - left + 1;
	int mid = (length / 2) + left;
	int first = arr[left][2], middle = arr[mid][2], last = arr[right][2];
	if ((middle < first && first < last) || (middle > first && first > last))
    	return left;
	if ((first < middle && middle < last) || (first > middle && middle > last))
		return mid;
	return right;
}
void quickSort(int arr[][3], int left, int right){
	if(right > left){
		int newPivotIndex = partition(arr, left, right,	medianOfThree(arr, left, right)); 
		quickSort(arr, left, newPivotIndex - 1);
		quickSort(arr, newPivotIndex + 1, right);
	}
}
__int64 weightedCompletionTime(int arr[][3], int length){
    int i, time = 0;
    __int64 weightedTime = 0;
    for(i = 0; i < length; i++){
        time += arr[i][1];
        weightedTime += (__int64)time * arr[i][0];
    }
    printf("Time = %d\n", time);
    return weightedTime;
}