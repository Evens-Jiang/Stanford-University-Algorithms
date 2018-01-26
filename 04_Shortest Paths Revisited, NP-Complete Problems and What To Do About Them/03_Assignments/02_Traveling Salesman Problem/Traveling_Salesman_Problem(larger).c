/*
    Travelling Salesman Problem.
    Dynamic programming strategy:
        1. Given vertices set = {1, 2, 3, 4,…,n} and assume starting point is 1.
        (cost(i) = minimum cost for the path from 1 to i. The corrsponding cycle is cost(i) + dist(i, 1))

        2. C(S, i) be the cost of the minimum cost path visiting each vertex in set S exactly once, starting at 1 and ending at i.

        3. 
        If size of S is 2, then S must be {1, i}
            C(S, i) = dist(1, i) 
        Else if size of S is greater than 2.
            C(S, i) = min { C(S-{i}, j) + dis(j, i)}, where j belongs to S, j != i and j != 1.
*/
/*
    Example of citySet
    Number of cities = 4
    (citySet[0] indicates the starting city.)
    The array in the citySet stores the city index.
    
    cityset|   |   |   |   |   |   |   |   | citySet[3]
    index  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |         ^
    --------------------------------------------------------------------
           | 0 | 1 | 2 | 1 | 3 | 1 | 2 | 1 | citySet[3].array[1] = 2
    city   |   |   |   | 2 |   | 3 | 3 | 2 |                  ^
    index  |   |   |   |   |   |   |   | 3 | citySet[3].minDistance[1] = A[S, 2] (S = citySet[3])
           |   |   |   |   |   |   |   |   |                        ^
    --------------------------------------------------------------------       
    number | 1 | 1 | 1 | 2 | 1 | 2 | 2 | 3 |
    of     |   |   |   |   |   |   |   |   | citySet[3].sizeOfSet = 2
    cities |   |   |   |   |   |   |   |   |
*/
/*
    The minimum distance = 26442.730309
    Round down the min distace = 26442
    
    1. CPU: i5-6500
        Running time =  69.344 (sec)
	2. CPU: Duo E8400
        Running time = 108.531 (sec)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h> /* DBL_MAX */

typedef struct city_set{
    int sizeOfSet, *array;
    double *minDistance;
}city_set_t, *city_set_p;

void errorExit(char* message);
double calculateDistance(double **coordinate, int start, int end);
int combination(int n, int k);
int bitcount(unsigned int n);
int *positionOfOne(int n, int numberOfOnes);
double findMin(city_set_p citySet, double **adjMatrix, int i, int j);
int *indexFinder(int m, int numberOfCity);
double TSP(int numberOfCity, double **adjMatrix);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("tsp.txt", "r");
    int numberOfCity, i, j;
    double **coordinate, **adjMatrix;
    
    if(!inFile)
        errorExit("Fail to open file.");
    else
        printf("Open file successfully!\n");
    
    fscanf(inFile, "%d", &numberOfCity);
    printf("numberOfCity = %d\n", numberOfCity);

    coordinate = malloc(numberOfCity * sizeof(double*));
    if(!coordinate)
        errorExit("Malloc coordinate failed.");
    adjMatrix = malloc(numberOfCity * sizeof(double*));
    if(!adjMatrix)
        errorExit("Malloc adjMatrix failed.");

    for(i = 0; i < numberOfCity; i++){
        coordinate[i] = malloc(2 * sizeof(double));
        adjMatrix[i] = malloc(numberOfCity * sizeof(double));
        if(!coordinate[i]){
            printf("Malloc coordinate[%d] failed.\n", i);
            return;
        }
        if(!adjMatrix[i]){
            printf("Malloc adjMatrix[%d] failed.\n", i);
            return;
        }
    }
    i = 0;
    while(fscanf(inFile, "%lf %lf", &coordinate[i][0], &coordinate[i][1]) != EOF)
        i++;
    for(i = 0; i < numberOfCity; i++){
        adjMatrix[i][i] = 0;
        for(j = i + 1; j < numberOfCity; j++){
            adjMatrix[j][i] = adjMatrix[i][j] = calculateDistance(coordinate, i, j);
        }
    }
    
//    printf(" \\ ");
//    for(i = 0; i < numberOfCity; i++)
//        printf("    %2d   ", i);
//    printf("\n");
//    for(i = 0; i < numberOfCity; i++){
//        printf("%2d ", i);
//        for(j = 0; j < numberOfCity; j++){
//            printf("%8.2f ", adjMatrix[i][j]);
//        }
//        printf("\n");
//    }
    printf("Minimum distance = %lf\n\n", TSP(numberOfCity, adjMatrix));

    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

void errorExit(char* message) {
    printf("[Fatal Error]: %s \nExiting...\n", message);
    exit(1);
}

double calculateDistance(double **coordinate, int start, int end){
    double x1 = coordinate[start][0], y1 = coordinate[start][1];
    double x2 = coordinate[end][0], y2 = coordinate[end][1];
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int combination(int n, int k){
    int i = 0;
    if(k == n)
        return 1;
    if(k > n / 2)
        k = n - k;
    __int64 top = n, down = k;
    for(i = n - 1; i > (n - k); i--)
        top *= i;
    for(i = k - 1; i > 0; i--)
        down *= i;
    return top / down;
}

/* Counting number of '1' bits */
/* Algorithm is from https://goo.gl/ptGcbf */
int bitcount(unsigned int n){
   int count = 0 ;
   while (n){
      count++ ;
      n &= (n - 1) ; //關鍵演算之處
   }
   return count ;
}
int counting1Bits(int decimal){
    int count = 0;
    count = bitcount(decimal);
    // printf("%d contains %d '1's\n\n", decimal, count);
    return count;
}

int *positionOfOne(int n, int numberOfOnes){
    int i, bit, temp = 0, *position = malloc(numberOfOnes * sizeof(int));
    // printf("numberOfOnes = %d\n", numberOfOnes);
    if(!position)
        errorExit("Malloc position failed.");
    for(i = 0; i < numberOfOnes; i++)
        position[i] = 0;
    i = 0;
    while(n != 0){
        bit = n % 2;
        i++;
        // printf("bit = %d\n", bit);
        if(bit){
            // printf("position = %d\n", i);
            position[temp] = i;
            temp++;
        }
        n = n / 2;
    }
    return position;
}

double findMin(city_set_p citySet, double **adjMatrix, int i, int j){
    int l;
    int tailCity = citySet[i].array[j], newCitySetIndex = i - (int)pow(2, tailCity - 1);
    int newTailCity, lengthOfNewArray = citySet[newCitySetIndex].sizeOfSet;
    double min = DBL_MAX, minDistance;
//     printf("i = %d, j = %d\n", i, j);
//     printf("newCitySetIndex = %d\n", newCitySetIndex);
//     printf("tailCity = %d\n\n", tailCity);

    for(l = 0; l < lengthOfNewArray; l++){
        newTailCity = citySet[newCitySetIndex].array[l];
//         printf("newTailCity = %d\n", newTailCity);
        minDistance = citySet[newCitySetIndex].minDistance[l] + adjMatrix[newTailCity][tailCity];
//         printf("minDistance = %lf\n", minDistance);
        if(minDistance < min)
            min = minDistance;
//         printf("min = %lf\n\n", min);
    }
    return min;
}
/* Find the index of citySet */
int *indexFinder(int m, int numberOfCity){
    int *array, j, tempBitIndex = 0;
    int bitCounter = combination(numberOfCity - 1, m);
    int citySetIndexAll = (int) pow(2, numberOfCity - 1);
    array = malloc(bitCounter * sizeof(int));
    if(!array){
        printf("Malloc no. %d array failed\n", m);
        exit(1);
    }
    for(j = 1; j < citySetIndexAll; j++)
        if(counting1Bits(j) == m)
            array[tempBitIndex++] = j;
    return array;
}

double TSP(int numberOfCity, double **adjMatrix){
    int m, i, j, citySetIndexAll = (int) pow(2, numberOfCity - 1);
    int tempBitCounter, tempCitySetIndex;
    int *array, *citySetIndexArray;
    double min = DBL_MAX, tempSP;
    city_set_p citySet = malloc(citySetIndexAll * sizeof(city_set_t));

    /* citySet index represent the number of the city in the set */
    /* Find the citySetIndex that contains only one city */
    citySetIndexArray = indexFinder(1, numberOfCity);
    /* tempBitCounter is the size of citySetIndexArray */
    tempBitCounter = combination(numberOfCity - 1, 1);
    for(i = 0; i < tempBitCounter; i++){
        tempCitySetIndex = citySetIndexArray[i];
        citySet[tempCitySetIndex].sizeOfSet = 1;
        citySet[tempCitySetIndex].array = malloc(sizeof(int));
        citySet[tempCitySetIndex].minDistance = malloc(sizeof(double));
        if(!citySet[tempCitySetIndex].array){
            printf("Malloc citySet[%d].array failed.\n", tempCitySetIndex);
            errorExit(" ");
        }
        if(!citySet[tempCitySetIndex].minDistance){
            printf("Malloc citySet[%d].minDistance failed.\n", tempCitySetIndex);
            errorExit(" ");
        }
        /* Find the '1' position which represent the index of city */
        array = positionOfOne(tempCitySetIndex, 1);
        citySet[tempCitySetIndex].array[0] = array[0];
        citySet[tempCitySetIndex].minDistance[0] = adjMatrix[0][array[0]];
        free(array);
    }
    free(citySetIndexArray);
    for(m = 2; m < numberOfCity; m++){
        /* tempBitCounter is the size of citySetIndexArray */
        tempBitCounter = combination(numberOfCity - 1, m);
        /* Find the citySetIndex that contains only one city */
        citySetIndexArray = indexFinder(m, numberOfCity);
        for(i = 0; i < tempBitCounter; i++){
            tempCitySetIndex = citySetIndexArray[i];
            citySet[tempCitySetIndex].sizeOfSet = m;
            citySet[tempCitySetIndex].array = malloc(m * sizeof(int));
            if(!citySet[tempCitySetIndex].array){
                printf("Malloc citySet[%d].array failed.\n", tempCitySetIndex);
                exit(1);
            }
            /* Find the '1' position which represent the index of city */
            array = positionOfOne(tempCitySetIndex, m);
            for(j = 0; j < m; j++)
                citySet[tempCitySetIndex].array[j] = array[j];
            free(array);
            citySet[tempCitySetIndex].minDistance = malloc(m * sizeof(double));
            if(!citySet[tempCitySetIndex].minDistance){
                printf("Malloc citySet[%d].minDistance failed.\n", tempCitySetIndex);
                exit(1);
            }
            /* Calculate the minimum distance */
            for(j = 0; j < m; j++){
                citySet[tempCitySetIndex].minDistance[j] = findMin(citySet, adjMatrix, tempCitySetIndex, j);
            }
        }
        /* Free the citySet array and minDistance */
        tempBitCounter = combination(numberOfCity - 1, m - 1);
        free(citySetIndexArray);
        citySetIndexArray = indexFinder(m - 1, numberOfCity);
        for(i = 0; i < tempBitCounter; i++){
            tempCitySetIndex = citySetIndexArray[i];
            free(citySet[tempCitySetIndex].array);
            free(citySet[tempCitySetIndex].minDistance);
        }
        free(citySetIndexArray);
    }
    /* The last calculation back to starting city */
    for(i = 0; i < numberOfCity - 1; i++){
        tempSP = citySet[citySetIndexAll - 1].minDistance[i] + adjMatrix[citySet[citySetIndexAll - 1].array[i]][0];
        if(min > tempSP)
            min = tempSP;
    }
    return min;
}