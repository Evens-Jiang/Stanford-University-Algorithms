/*
    2 Sum Algorithm.
    The answer is 427.
    By using brutal force method, the running time = 1467.959 (sec).
*/
#include <stdio.h>
#include <time.h>

#define SIZE 1000000

void swap_long(__int64 *a, __int64 *b){
  	__int64 tmp = *a;
  	*a = *b;
  	*b = tmp;  
}

int partition(__int64 arr[], int left, int right, int pivotIndex){
	__int64 pivotValue = arr[pivotIndex];
    int compareIndex = left + 1;
	swap_long(&(arr[pivotIndex]), &(arr[left]));
	for(int i = left + 1; i <= right; i++){
		if(arr[i] < pivotValue){
			swap_long(&(arr[i]), &(arr[compareIndex]));
			compareIndex++;
		}
	}
	swap_long(&(arr[--compareIndex]), &(arr[left]));
	return compareIndex;
}

int medianOfThree(__int64 arr[], int left, int right){
	int length = right - left + 1;
	int mid = (length % 2) == 0 ? length / 2 + left : (length / 2) + left;
	__int64 first = arr[left], middle = arr[mid], last = arr[right];
	if ((middle < first && first < last) || (middle > first && first > last))
    	return left;
	if ((first < middle && middle < last) || (first > middle && middle > last))
		return mid;
	return right;
}

void quickSort(__int64 arr[], int left, int right){
	if(right > left){
		int newPivotIndex = partition(arr, left, right,	medianOfThree(arr, left, right));
		quickSort(arr, left, newPivotIndex - 1);
		quickSort(arr, newPivotIndex + 1, right);
	}
}

int findMatch(__int64 arr[], __int64 value, int firstPositiveIndex){
    int counter = 0, i = 0, start, end, mid;
    if(value > 0){
        start = firstPositiveIndex;
        end = SIZE - 1;
        mid = (end - start) / 2 + start;
        while(start <= end){
            if(arr[mid] == value)
                return 1;
            else if(arr[mid] < value){
                start = mid + 1;
                mid = (end - start) / 2 + start;
            }
            else if(arr[mid] > value){
                end = mid - 1;
                mid = (end - start) / 2 + start;
            }
        }
        return 0;
    }
    else{
        start = 0;
        end = firstPositiveIndex;
        mid = (end - start) / 2 + start;
        while(start <= end){
            if(arr[mid] == value)
                return 1;
            else if(arr[mid] < value){
                start = mid + 1;
                mid = (end - start) / 2 + start;
            }
            else if(arr[mid] > value){
                end = mid - 1;
                mid = (end - start) / 2 + start;
            }
        }
        return 0;
    }
}

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("2sum.txt", "r");
    __int64 array[SIZE] = {0}, value;
    int i = 0, counter = 0, target = -10000, temp;
    int firstPositiveIndex = 0;
    if(!inFile)
    	printf("Fail to open file\n");
    else
    	printf("Open file successfully!\n");
    
    while(fscanf(inFile, "%lld", &array[i]) != EOF){
        i++;
    }
    quickSort(array, 0, SIZE - 1);
    for(i = 0; i < SIZE; i++){
        if(array[i] + array[i + 1] > array[i])
            firstPositiveIndex = ++i;
            break;
    }
    for(target = -10000; target <= 10000; target++){
        for(i = 0; i < SIZE; i++){
            value = target - array[i];
            temp = counter;
            counter += findMatch(array, value, firstPositiveIndex);
            if(counter > temp){
                printf("array[%6d] = %lld\n", i, array[i]);
                printf("value         = %lld\n", value);
                printf("target        = %d\n\n", target);
                break;
            }
        }
    }

    printf("counter = %d\n", counter);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    fclose(inFile);
}