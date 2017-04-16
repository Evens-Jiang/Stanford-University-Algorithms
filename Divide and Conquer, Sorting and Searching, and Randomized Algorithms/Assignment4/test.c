#include <stdio.h>
#include <math.h>

#define SIZE 200

int convertCharToInt(char *c, int digit){
	int number = 0, counter = digit, power = 0;
	if(counter == 1)
		return *c - 48;
	while(counter--){
		if(counter % 2 || counter == 0)
			power = (int) (pow(10, counter));
		else
			power = (int) (pow(10, counter)) + 1;
		number += (*c - 48) * power;
		c++;
	}
	return number;
}
void main(){
	char test[] = "56789";
	printf("%d\n", convertCharToInt(test, 1));
	printf("%d\n", convertCharToInt(test, 2));
	printf("%d\n", convertCharToInt(test, 3));
	printf("%d\n", convertCharToInt(test, 4));
	printf("%d\n", convertCharToInt(test, 5));
}