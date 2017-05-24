/*
    Greedy Algorithm.
    Decreasing order of the ratio (weight/length).
    It does not matter the equalization in difference (weight/length).
    Weighted completion time = 67311454237.
*/
#include <stdio.h>
#include <time.h>

typedef struct weight_length{
    int weight, length;
    float difference;
}weight_length;

void swap(weight_length *a, weight_length *b);
int partition(weight_length wl[], int left, int right, int pivotIndex);
int medianOfThree(weight_length wl[], int left, int right);
void quickSort(weight_length wl[], int left, int right);
__int64 weightedCompletionTime(weight_length wl[], int length);

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
    weight_length wl[numberOfJobs];
    
    while(fscanf(inFile, "%d %d", &(wl[i].weight), &(wl[i].length)) != EOF){
        wl[i].difference = (float)wl[i].weight / wl[i].length;
        i++;
    }
//    printf("  No. weight length W-L\n");
//    for(i = 0; i < numberOfJobs; i++)
//        printf("%5d    %3d     %2d %f\n", i, wl[i].weight, wl[i].length, wl[i].difference);
    quickSort(wl, 0, numberOfJobs - 1);
//    printf("  No. weight length W-L\n");
//    for(i = 0; i < numberOfJobs; i++)
//        printf("%5d    %3d     %2d %f\n", i, wl[i].weight, wl[i].length, wl[i].difference);
    
    fclose(inFile);
    printf("weighted completion time = %lld\n", weightedCompletionTime(wl, numberOfJobs));
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

void swap(weight_length *a, weight_length *b){
  	weight_length tmp = *a;
  	*a = *b;
  	*b = tmp;  
}
int partition(weight_length wl[], int left, int right, int pivotIndex){
	float pivotValue = wl[pivotIndex].difference;
    int pivotWeight = wl[pivotIndex].weight;
    int compareIndex = left + 1;
    
    swap(&(wl[pivotIndex]), &(wl[left]));
	for(int i = left + 1; i <= right; i++){
		if(wl[i].difference > pivotValue){
            swap(&(wl[i]), &(wl[compareIndex]));
			compareIndex++;
		}
	}
    swap(&(wl[--compareIndex]), &(wl[left]));
	return compareIndex;
}
int medianOfThree(weight_length wl[], int left, int right){
	int length = right - left + 1;
	int mid = (length / 2) + left;
	float first = wl[left].difference, middle = wl[mid].difference, last = wl[right].difference;
	if ((middle < first && first < last) || (middle > first && first > last))
    	return left;
	if ((first < middle && middle < last) || (first > middle && middle > last))
		return mid;
	return right;
}
void quickSort(weight_length wl[], int left, int right){
	if(right > left){
		int newPivotIndex = partition(wl, left, right,	medianOfThree(wl, left, right)); 
		quickSort(wl, left, newPivotIndex - 1);
		quickSort(wl, newPivotIndex + 1, right);
	}
}
__int64 weightedCompletionTime(weight_length wl[], int length){
    int i, time = 0;
    __int64 weightedTime = 0;
    for(i = 0; i < length; i++){
        time += wl[i].length;
        weightedTime += (__int64)time * wl[i].weight;
    }
    printf("Time = %d\n", time);
    return weightedTime;
}