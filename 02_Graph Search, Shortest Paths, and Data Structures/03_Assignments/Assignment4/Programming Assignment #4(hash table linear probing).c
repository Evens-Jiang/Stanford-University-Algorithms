/*
    Hash Table with linear probing
    too slow.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TOTAL_NUMBER 1000000
#define POWER 27

int hashFunction(__int64 key);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("2sum.txt", "r");
    __int64 *hashTable, value, tempValue;
    int probingCounter = 0, probingMax = 0, resultCounter = 0;
    int index, maxIndex = (int) pow(2, POWER), i, j, counter = 0;
    int pConstant1, pConstant2;
    
    if(!inFile)
    	printf("Fail to open file\n");
    else
    	printf("Open file successfully!\n");
    
    hashTable = malloc(maxIndex * sizeof(__int64));
    if(!hashTable){
        printf("Malloc hashTable failed.\n");
        exit(1);
    }
    for(i = 0; i < maxIndex; i++)
        hashTable[i] = 0;
    /* insert keys to hash table */
    while(fscanf(inFile, "%lld", &value) != EOF){
        counter++;
        index = hashFunction(value);
        /* linear probing */
        while(hashTable[index]){
            probingCounter++;
            index = (index + 10079) % maxIndex;
        }
        if(probingCounter > probingMax)
            probingMax = probingCounter;
        probingCounter = 0;
        hashTable[index] = value;
        if(counter % 100000 == 0)
            printf("value = %lld, index = %d, probingMax = %d\n\n", value, index, probingMax);
    }
    printf("probingMax = %d\n", probingMax);
    fseek(inFile, 0, SEEK_SET);
    /* find the temp value to the key */
    for(i = -10000; i <= 10000; i++){
        while(fscanf(inFile, "%d", &value) != EOF){
            tempValue = i - value;
            index = hashFunction(tempValue);
            for(j = 0; j < probingMax; j++){
                if(tempValue == hashTable[index]){
                    printf("temp value match!\n");
                    printf("value = %lld, tempValue = %lld, target = %d\n\n", value, tempValue, i);
                    resultCounter++;
                    fseek(inFile, 0, SEEK_END);
                    break;
                }
                index = (index + 10079) % maxIndex;
            }
        }
        fseek(inFile, 0, SEEK_SET);
    }
    printf("resultCounter = %d\n", resultCounter);

    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

int hashFunction(__int64 key){
    if(key < 0)
        key *= (-1);
    int m = (int) pow(2, POWER), result;
    double A = 0.59375, keyMultiA, fraction;
    
    keyMultiA = (double) key * A;
    fraction = keyMultiA - (__int64) keyMultiA;
    result = (int)((double) m * fraction);
//    printf("key = %lld, keyMultiA = %lf, fraction = %lf, result = %d\n", key, keyMultiA, fraction, result);
    return result;
}