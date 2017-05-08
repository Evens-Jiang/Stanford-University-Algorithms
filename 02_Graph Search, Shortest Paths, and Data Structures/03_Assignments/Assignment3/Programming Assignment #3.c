/*
    Median Maintenance Algorithm
*/

#include <stdio.h>

void main(void){
    FILE *inFile = fopen("Median.txt", "r");

	if(!inFile)
		printf("Fail to open file\n\n");
	else
		printf("Open file successfully!\n\n");
        
    fclose(inFile);
}