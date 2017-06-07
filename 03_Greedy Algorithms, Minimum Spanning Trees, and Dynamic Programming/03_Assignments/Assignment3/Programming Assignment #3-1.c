/*
    Huffman Coding Algorithm.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("huffman.txt", "r");
    int numberOfSymbols, *weight, i = 0;
    
    if(!inFile){
    	printf("Fail to open file\n");
        return;
    }
    else
    	printf("Open file successfully!\n");
    
    fscanf(inFile, "%d", &numberOfSymbols);
    printf("Number of symbols = %d\n", numberOfSymbols);
    
    if((weight = malloc((numberOfSymbols + 1) * sizeof(int))) == NULL)
        printf("Malloc weight failed.\n");
    
    while(fscanf(inFile, "%d", &weight[i]) != EOF)
        i++;
    printf("Completed reading weights.\n");
    for(i = 1; i < 10; i++)
        printf("%d\n", weight[i]);
    
    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}