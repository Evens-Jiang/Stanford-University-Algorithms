/*
    Traveling Salesman Problem - nearest neighbor heuristic
    Distance = 1203406.501271
    1. CPU: i5-6500
        Running time =  (sec)
	2. CPU: Duo E8400
        Running time = 477.987 (sec)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>

typedef struct city{
    int number;
    double distance;
}city_t, *city_p;

void errorExit(char* message);
void swap(city_p a, city_p b);
void max_heapify(city_p citySet, int start, int end);
void heap_sort(city_p citySet, int len);
double calculateDistance(double **coordinate, int start, int end);
city_p findClosetCity(int numberOfCity, int cityNow, int cityCounter, int *cityCheck, double **coordinate);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("nn.txt", "r");
    int numberOfCity, i, j;
    int cityNow = 1, cityCounter = 0, *cityCheck;
    double **coordinate, distance = 0.0;
    city_p cityTemp;
    
    if(!inFile)
        errorExit("Fail to open file.");
    else
        printf("Open file successfully!\n");
    
    fscanf(inFile, "%d", &numberOfCity);
    printf("numberOfCity = %d\n", numberOfCity);
    
    /* Malloc coordinate, cityCheck */
    coordinate = malloc((numberOfCity + 1) * sizeof(double*));
    if(!coordinate)
        errorExit("Malloc coordinate failed.");
    cityCheck = malloc((numberOfCity + 1) * sizeof(int*));
    if(!cityCheck)
        errorExit("Malloc cityCheck failed.");
    cityCheck[0] = -1;
    
    for(i = 1; i <= numberOfCity; i++){
        cityCheck[i] = 0;
        coordinate[i] = malloc(2 * sizeof(double));
        if(!coordinate[i]){
            printf("Malloc coordinate[%d] failed.\n", i);
            return;
        }
    }
    fscanf(inFile, "%d", &i);
    while(fscanf(inFile, "%lf %lf", &coordinate[i][0], &coordinate[i][1]) != EOF){
//        printf("%5d %5.4lf %5.4lf\n", i, coordinate[i][0], coordinate[i][1]);
        if(fscanf(inFile, "%d", &i) == EOF)
            break;
    }
    cityCheck[1] = ++cityCounter;
    for(i = 2; i <= numberOfCity; i++){
        cityTemp = findClosetCity(numberOfCity, cityNow, cityCounter, cityCheck, coordinate);
        cityCounter++;
        cityNow = cityTemp->number;
        distance += cityTemp->distance;
        free(cityTemp);
//        printf("cityNow = %d, cityCounter = %d, Distance = %lf\n", cityNow, cityCounter, distance);
    }
    /* Return to city 1 */
    distance += calculateDistance(coordinate, cityNow, 1);
    printf("Distance = %lf\n", distance);
    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

void errorExit(char* message){
    printf("[Fatal Error]: %s \nExiting...\n", message);
    exit(1);
}

void swap(city_p a, city_p b) {
	city_t temp = *b;
	*b = *a;
	*a = temp;
}

void max_heapify(city_p citySet, int start, int end) {
	//建立父節點指標和子節點指標
	int dad = start;
	int son = dad * 2;
	while (son <= end) {
		if (son + 1 <= end && citySet[son].distance < citySet[son + 1].distance)
			son++;
		if (citySet[dad].distance > citySet[son].distance)
			return;
		else {
			swap(&citySet[dad], &citySet[son]);
			dad = son;
			son = dad * 2;
		}
	}
}

void heap_sort(city_p citySet, int len) {
	int i;
	/* 初始化，i從最後一個父節點開始調整 */
	for (i = len / 2; i > 0; i--)
		max_heapify(citySet, i, len);
	/* 先將第一個元素和已排好元素前一位做交換，再從新調整，直到排序完畢 */
	for (i = len; i > 0; i--) {
		swap(&citySet[1], &citySet[i]);
        /* 最大的放最後面 */
		max_heapify(citySet, 1, i - 1);
	}
}

double calculateDistance(double **coordinate, int start, int end){
    if(start == end)
        return 0.0;
    double x1 = coordinate[start][0], y1 = coordinate[start][1];
    double x2 = coordinate[end][0], y2 = coordinate[end][1];
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

city_p findClosetCity(int numberOfCity, int cityNow, int cityCounter, int *cityCheck, double **coordinate){
    city_p citySet = malloc((numberOfCity + 1) * sizeof(city_t)), cityReturn = malloc(sizeof(city_t));
    int i, tempPtr = 2, tempCity, finalPtr;
    double distance, tempDistance;
    if(!citySet)
       errorExit("Malloc citySet failed.");

    /* Calculate the distance */
    for(i = 1; i <= numberOfCity; i++){
        citySet[i].number = i;
        citySet[i].distance = calculateDistance(coordinate, cityNow, i);
    }
    /* Sort the distance */
    heap_sort(citySet, numberOfCity);
    /* Find the nearest and unreached city */
    while(cityCheck[citySet[tempPtr].number] > 0)
        tempPtr++;
    /* Check if the same distance to different city */
    tempCity = citySet[tempPtr].number;
    tempDistance = citySet[tempPtr].distance;
    finalPtr = tempPtr;
    while(tempDistance == citySet[tempPtr + 1].distance){
        if(tempCity > citySet[tempPtr + 1].number && cityCheck[citySet[tempPtr + 1].number] == 0){
            tempCity = citySet[tempPtr + 1].number;
            finalPtr = tempPtr + 1;
        }
        tempPtr++;
    }
    cityCheck[citySet[finalPtr].number] = ++cityCounter;
    cityReturn->number = citySet[finalPtr].number;
    cityReturn->distance = citySet[finalPtr].distance;
    free(citySet);
    return cityReturn;
}