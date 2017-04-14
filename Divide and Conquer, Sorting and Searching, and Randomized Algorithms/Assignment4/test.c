#include <stdio.h>
#include <math.h>

#define SIZE 200

int convertCharToInt(char *c, int digit){
	int number = 0, counter = digit;
	if(counter == 1)
		return *c - 48;
	while(counter){
		number += (*c - 48) * pow(10, --counter);
		c++;
	}
	if(digit % 2)
		number++;
	return number;
}
void main(){
	char test[] = "43210";
	printf("%d\n", convertCharToInt(test, 5));
	printf("%d", 5 * pow(10, 0));
}