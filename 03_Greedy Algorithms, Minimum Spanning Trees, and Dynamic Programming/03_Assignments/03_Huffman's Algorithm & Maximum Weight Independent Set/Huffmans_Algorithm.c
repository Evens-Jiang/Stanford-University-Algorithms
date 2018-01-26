/*
    Huffman's Algorithm
    (Given frequencies Pi as input)
    If |∑| = 2 return

           Node
        0 /   \ 1
         A     B

    Let a, b belong to ∑ have the smallest frequencies.
    Let ∑' = ∑ with a, b replaced by new symbol ab.
    Define Pab = Pa + Pb.
    Recursively compute T' (for the alphabet ∑')
    Extend T' (with leaves ←→ ∑') to a tree T with leaves ←→ ∑ by splitting leaf ab into two leaves a & b.

    Return T
*/
/*
    Max = 19, min = 9.
    runnig time = 0.090 (sec)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap_sort.h"

int findMax(huffman_node_p huffmanNode);
int findMin(huffman_node_p huffmanNode);

void main(void){
    clock_t begin = clock();
    FILE *inFile = fopen("huffman.txt", "r");
    int numberOfSymbols, i = 0;
    __int64 totalWeight = 0;
    huffman_node_p huffmanNode;
    
    if(!inFile){
    	printf("Fail to open file\n");
        return;
    }
    else
    	printf("Open file successfully!\n");
    
    fscanf(inFile, "%d", &numberOfSymbols);
    printf("Number of symbols = %d\n", numberOfSymbols);
    
    if((huffmanNode = malloc((numberOfSymbols) * sizeof(huffman_node_t))) == NULL)
        printf("Malloc weight failed.\n");
    
    while(fscanf(inFile, "%lld", &huffmanNode[i].weight) != EOF){
        totalWeight += huffmanNode[i].weight;
        huffmanNode[i].key = i;
        huffmanNode[i].left = NULL;
        huffmanNode[i].right = NULL;
        i++;
    }

    printf("totalWeight = %lld\n", totalWeight);
    heap_sort(huffmanNode, numberOfSymbols);

    /* i represents the count of merges. */
    i = numberOfSymbols - 1;
    while(i != 0){
        huffman_node_p newNode1 = malloc(sizeof(huffman_node_t)),  newNode2 = malloc(sizeof(huffman_node_t));
        *newNode1 = huffmanNode[0];
        *newNode2 = huffmanNode[1];
        huffmanNode[0].weight = huffmanNode[0].weight + huffmanNode[1].weight;
        huffmanNode[0].key = 0;
        huffmanNode[0].left = newNode1;
        huffmanNode[0].right = newNode2;
        swap(&huffmanNode[i], &huffmanNode[1]);
        /* we need to pass the length of array to heap_sort, not the number. */
        heap_sort(huffmanNode, i);
        i--;
    }
    /* Check the weight of the last node. */
    printf("i = 0 weight = %lld\n", huffmanNode[0].weight);

    printf("Max = %d\n", findMax(&huffmanNode[0]));
    printf("Min = %d\n", findMin(&huffmanNode[0]));

    fclose(inFile);
    clock_t end = clock();
    printf("Running time = %.3f (sec)\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

int findMax(huffman_node_p huffmanNode){
    if(huffmanNode->left == NULL && huffmanNode->right == NULL)
        return 0;
    int left = findMax(huffmanNode->left), right = findMax(huffmanNode->right);
    if(left > right)
        return 1 + left;
    else
        return 1 + right;
}

int findMin(huffman_node_p huffmanNode){
    if(huffmanNode->left == NULL && huffmanNode->right == NULL)
        return 0;
    int left = findMin(huffmanNode->left), right = findMin(huffmanNode->right);
    if(left < right)
        return 1 + left;
    else
        return 1 + right;
}