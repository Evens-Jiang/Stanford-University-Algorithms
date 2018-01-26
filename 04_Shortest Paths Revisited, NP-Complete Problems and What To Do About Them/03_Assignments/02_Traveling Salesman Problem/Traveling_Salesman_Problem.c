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
    
    cityset|   |   |   |   |   |   |   |   | citySet[i]
    index  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |         ^
    --------------------------------------------------------------------
           | 0 | 1 | 2 | 1 | 3 | 1 | 2 | 1 | citySet[i].array[j]
    city   |   |   |   | 2 |   | 3 | 3 | 2 |                  ^
    index  |   |   |   |   |   |   |   | 3 | citySet[i].shortestPath[j]
           |   |   |   |   |   |   |   |   |                         ^
    --------------------------------------------------------------------       
    number | 1 | 1 | 1 | 2 | 1 | 2 | 2 | 3 |
    of     |   |   |   |   |   |   |   |   | citySet[i].numberOfSet
    cities |   |   |   |   |   |   |   |   |
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>

typedef struct city_set{
    int numberOfSet, *array;
    float *shortestPath;
}city_set_t, *city_set_p;

void errorExit(char* message);
float calculateDistance(float **coordinate, int start, int end);
int bitcount(unsigned int n);
int *positionOfOne(int n, int numberOfOnes);
float findMin(city_set_p citySet, float **adjMatrix, int i, int j);
float TSP(int numberOfCity, float **adjMatrix);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("tsp_test(12.36).txt", "r");
    int numberOfCity, i, j;
    float **coordinate, **adjMatrix;
    
    if(!inFile)
        errorExit("Fail to open file.");
    else
        printf("Open file successfully!\n");
    
    fscanf(inFile, "%d", &numberOfCity);
    printf("numberOfCity = %d\n", numberOfCity);

    coordinate = malloc(numberOfCity * sizeof(float*));
    if(!coordinate)
        errorExit("Malloc coordinate failed.");
    adjMatrix = malloc(numberOfCity * sizeof(float*));
    if(!adjMatrix)
        errorExit("Malloc adjMatrix failed.");

    for(i = 0; i < numberOfCity; i++){
        coordinate[i] = malloc(2 * sizeof(float));
        adjMatrix[i] = malloc(numberOfCity * sizeof(float));
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
    while(fscanf(inFile, "%f %f", &coordinate[i][0], &coordinate[i][1]) != EOF){
        printf("%.4f %.4f\n", coordinate[i][0], coordinate[i][1]);
        i++;
    }
    for(i = 0; i < numberOfCity; i++){
        adjMatrix[i][i] = 0;
        for(j = i + 1; j < numberOfCity; j++){
            adjMatrix[j][i] = adjMatrix[i][j] = calculateDistance(coordinate, i, j);
        }
    }
    printf(" \\ ");
    for(i = 0; i < numberOfCity; i++)
        printf("    %2d   ", i);
    printf("\n");
    for(i = 0; i < numberOfCity; i++){
        printf("%2d ", i);
        for(j = 0; j < numberOfCity; j++){
            printf("%8.2f ", adjMatrix[i][j]);
        }
        printf("\n");
    }

    printf("min = %f\n", TSP(numberOfCity, adjMatrix));

    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (float)(end - begin) / CLOCKS_PER_SEC);
    return;
}

void errorExit(char* message) {
    printf("[Fatal Error]: %s \nExiting...\n", message);
    exit(1);
}

float calculateDistance(float **coordinate, int start, int end){
    float x1 = coordinate[start][0], y1 = coordinate[start][1];
    float x2 = coordinate[end][0], y2 = coordinate[end][1];
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int combination(int n, int k){
    int i, top = n, down = k;
    for(i = n - 1; i > (n - k); i--)
        top *= i;
    for(i = k - 1; i > 0; i--)
        down *= i;
    return top / down;
}

/* Counting number of 1 bits */
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
    int i, *position, bit, temp = 0;
    position = malloc(numberOfOnes * sizeof(int));
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

float findMin(city_set_p citySet, float **adjMatrix, int i, int j){
    int l;
    int tailCity = citySet[i].array[j], newCitySetIndex = i - (int)pow(2, tailCity - 1);
    int newTailCity, lengthOfNewArray = citySet[newCitySetIndex].numberOfSet;
    float min = DBL_MAX, shortestPath;
    // printf("i = %d, j = %d\n", i, j);
    // printf("newCitySetIndex = %d\n", newCitySetIndex);
    // printf("tailCity = %d\n\n", tailCity);

    for(l = 0; l < lengthOfNewArray; l++){
        newTailCity = citySet[newCitySetIndex].array[l];
        // printf("newTailCity = %d\n", newTailCity);
        shortestPath = citySet[newCitySetIndex].shortestPath[l] + adjMatrix[newTailCity][tailCity];
        // printf("shortestPath = %f\n", shortestPath);
        if(shortestPath < min)
            min = shortestPath;
        // printf("min = %f\n\n", min);
    }
    return min;
}

float TSP(int numberOfCity, float **adjMatrix){
    int m, i, j, numberOfOnes, citySetIndex = (int) pow(2, numberOfCity - 1);
    int *array;
    float min = DBL_MAX, tempSP;
    city_set_p citySet = malloc(citySetIndex * sizeof(city_set_t));

    for(i = 0; i < citySetIndex; i++){
        if(i == 0)
            numberOfOnes = 1;
        else
            numberOfOnes = counting1Bits(i);

        citySet[i].numberOfSet = numberOfOnes;
        citySet[i].array = malloc(numberOfOnes * sizeof(int));
        citySet[i].shortestPath = malloc(numberOfOnes * sizeof(float));
        if(!citySet[i].array){
            printf("Malloc citySet[%d].array failed.\n", i);
            errorExit(" ");
        }
        if(!citySet[i].shortestPath){
            printf("Malloc citySet[%d].shortestPath failed.\n", i);
            errorExit(" ");
        }
        /* Initialize citySet */
        if(i == 0){
            citySet[i].array[0] = 0;
            citySet[i].shortestPath[0] = 0.0;
        }
        else{
            array = positionOfOne(i, numberOfOnes);
            if(numberOfOnes == 1){
                citySet[i].array[0] = array[0];
                citySet[i].shortestPath[0] = adjMatrix[0][array[0]];
            }
            else{
                for(j = 0; j < numberOfOnes; j++){
                    citySet[i].array[j] = array[j];
                    citySet[i].shortestPath[j] = -1.0;
                }
            }
            free(array);
        }
    }
    
    // for(i = 1; i < citySetIndex; i++){
    //     printf("i = %d ", i);
    //     printf("length = %d\n", citySet[i].numberOfSet);
    //     for (j = 0; j < citySet[i].numberOfSet; ++j){
    //         printf("%d ", citySet[i].array[j]);
    //     }
    //     printf("\n");
    // }

    for(m = 2; m < numberOfCity; m++){
        for(i = 1; i < citySetIndex; i++){
            if(citySet[i].numberOfSet == m){
                for(j = 0; j < m; j++)
                    citySet[i].shortestPath[j] = findMin(citySet, adjMatrix, i, j);
            }
        }
    }
    // printf("citySetIndex = %d\n", citySetIndex);
    for(i = 0; i < numberOfCity - 1; i++){
        // printf("citySet[citySetIndex - 1].shortestPath[%d] = %f\n", i, citySet[citySetIndex - 1].shortestPath[i]);
        // printf("adjMatrix[citySet[citySetIndex - 1].array[%d]][0] = %f\n\n", i, adjMatrix[citySet[citySetIndex - 1].array[i]][0]);
        tempSP = citySet[citySetIndex - 1].shortestPath[i] + adjMatrix[citySet[citySetIndex - 1].array[i]][0];
        if(min > tempSP)
            min = tempSP;
    }
    return min;
}