#ifndef _HEAPSORT_H_
#define _HEAPSORT_H_

void swap(int *a, *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleUp(int *heap, int end){
    int son = end, dad = (son / 2) % 2 ?  (son / 2) - 1 : (son / 2);
    while(son > 0){
        if(son < dad){
            swap(&heap[son], &heap[dad]);
            son = dad;
            dad = (son / 2) % 2 ?  (son / 2) - 1 : (son / 2);
        }
        else
            break;
    }
    return;
}

void bubbleDown(int *heap, int end){
    int dad = 0, son = 1;
    while(son <= end){
        if(son + 1 < son && son + 1 <= end)
            son = son + 1;
        if(dad < son){
            swap(&heap[son], &heap[dad]);
            dad = son;
            son = dad * 2 + 1;
        }
        else
            break;
    }
    return;
}

int insertHeap(int *heap, int end, int key){
    end++;
    heap[end] = key;
    bubbleUp(heap, end);
    return end;
}

int deleteHeap(int *heap, int end){
    swap(&heap[0], &heap[end]);
    end--;
    bubbleDown(heap, end);
    return end;
}

int extractMin(int *heap, int end, int *minKey){
    *minKey = heap[0];
    return deleteHeap(heap, end);
}

#endif