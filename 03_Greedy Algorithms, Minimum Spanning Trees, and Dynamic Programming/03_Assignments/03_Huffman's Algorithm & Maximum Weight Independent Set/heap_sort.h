#ifndef _HEAPSORT_H_
#define _HEAPSORT_H_

typedef struct huffman_node{
    int key;
    __int64 weight;
    struct huffman_node *left, *right;
}huffman_node_t, *huffman_node_p;

void swap(huffman_node_p a, huffman_node_p b){
    huffman_node_t temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(huffman_node_p huffmanNode, int start, int end) {
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) {
        if (son + 1 <= end && huffmanNode[son].weight < huffmanNode[son + 1].weight)
            son++;
        if (huffmanNode[dad].weight > huffmanNode[son].weight)
            return;
        else {
            swap(&huffmanNode[dad], &huffmanNode[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heap_sort(huffman_node_p huffmanNode, int len) {
    int i;
    for (i = len / 2 - 1; i >= 0; i--)
        max_heapify(huffmanNode, i, len - 1);
    for (i = len - 1; i > 0; i--){
        swap(&huffmanNode[0], &huffmanNode[i]);
        max_heapify(huffmanNode, 0, i - 1);
    }
}

#endif