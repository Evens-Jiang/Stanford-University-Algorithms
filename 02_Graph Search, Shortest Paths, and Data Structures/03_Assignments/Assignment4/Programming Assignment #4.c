/*
    2 Sum Algorithm.

    The answer is 427.
    By using brutal force method:
    1. CPU: i5-6500
    Running time = 1467.959 (sec).

    2. CPU: Duo E8400
    Running time = 4597.308 (sec)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000
#define PRIME 9973 

/* Hash Table chaining */
typedef struct hash_table{
    __int64 value;
    struct hash_table *next;
}hash_table, *hash_table_p;

void addKey(int value, hash_table_p hashTablePtr);
int hash_function(__int64 value);
int hash_findMatch(__int64 value, hash_table_p hashTablePtr);
int hash_table_chaining(FILE *inFile);

/* Brutal Force */    
void swap_long(__int64 *a, __int64 *b);
int partition(__int64 arr[], int left, int right, int pivotIndex);
int medianOfThree(__int64 arr[], int left, int right);
void quickSort(__int64 arr[], int left, int right);
int findMatch(__int64 arr[], __int64 value, int firstPositiveIndex);
int brutal_force(FILE *inFile);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("2sum.txt", "r");
    if(!inFile)
    	printf("Fail to open file\n");
    else
    	printf("Open file successfully!\n");
    
//    int counter = brutal_force(inFile);
    int counter = hash_table_chaining(inFile);
    printf("Counter = %d\n", counter);
    fclose(inFile);
    
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

/* Hash Table chaining */
void addKey(int value, hash_table_p hashTablePtr){
    if(hashTablePtr->value == 0){
        hashTablePtr->value = value;
        return;
    }
    hash_table_p tempPtr = hashTablePtr, newKey = (hash_table_p)malloc(sizeof(hash_table));
    newKey->value = value;
    newKey->next = NULL;
    while(tempPtr->next != NULL)
        tempPtr = tempPtr->next;
    tempPtr->next = newKey;
    return;
}
int hash_function(__int64 value){
    int result = value % PRIME;
    if(result >= 0)
        return result;
    else
        return result + PRIME;
}
int hash_findMatch(__int64 value, hash_table_p hashTablePtr){
    hash_table_p tempPtr = hashTablePtr;
    while(tempPtr != NULL){
        if(tempPtr->value == value)
            return 1;
        else
            tempPtr = tempPtr->next;
    }
    return 0;
}
int hash_table_chaining(FILE *inFile){
    hash_table_p hashTable = (hash_table_p)malloc(PRIME * sizeof(hash_table));
    __int64 array[SIZE] = {0}, match;
    int i = 0, counter = 0, temp = 0, target = -10000, index;
    
    for(i = 0; i < PRIME; i++){
        hashTable[i].next = NULL;
        hashTable[i].value = 0;
    }
    i = 0;
    while(fscanf(inFile, "%lld", &array[i]) != EOF){
        index = hash_function(array[i]);
        addKey(array[i], &hashTable[index]);
        i++;
    }
    printf("Hash table completed\n");
    for(target = -9874; target <= 10000; target++){
        for(i = 0; i < SIZE; i++){
            match = target - array[i];
            index = hash_function(match);
            if(hash_findMatch(match, &hashTable[index])){
                temp = counter;
                counter++;
                printf("match = %lld\n", match);
                printf("index = %d\n", index);
                printf("counter = %d\n\n", counter);
                printf("%d match\n\n", target);
                break;
            }
        }
        if(temp == counter)
            printf("%d no match\n\n", target);
    }
    return counter;
}


/* Brutal force */
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
int brutal_force(FILE *inFile){
    __int64 array[SIZE] = {0}, value;
    int i = 0, counter = 0, target = -10000, temp;
    int firstPositiveIndex = 0;
    
    while(fscanf(inFile, "%lld", &array[i]) != EOF)
        i++;
    quickSort(array, 0, SIZE - 1);
    for(i = 0; i < SIZE; i++){
        if(array[i] + array[i + 1] > array[i]){
            firstPositiveIndex = ++i;
            break;
        }
    }
    for(target = -10000; target <= 10000; target++){
        for(i = 0; i < SIZE; i++){
            value = target - array[i];
		  	temp = counter;
            counter += findMatch(array, value, firstPositiveIndex);
		  	if(counter > temp){
			  printf("array[%6d] = %lld\n       target = %d\n\n", i, array[i], target);
			  break;
			}
        }
    }
    return counter;
}