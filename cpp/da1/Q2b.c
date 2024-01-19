#include <stdio.h>
#include <stdlib.h>

#define SPECIAL '#'

struct minHeapNode {
    char data;
    unsigned int frequency;
    struct minHeapNode *left, *right;
};

struct minHeap {
    unsigned int size;
    unsigned int capacity;
    struct minHeapNode** array;
};

struct minHeapNode* newNode(char data, unsigned int frequency) {
    struct minHeapNode* node = (struct minHeapNode*) malloc(sizeof(struct minHeapNode));

    node->left = node->right = NULL;
    node->data = data;
    node->frequency = frequency;

    return node;
}

struct minHeap* createMinHeap(unsigned capacity) {
    struct minHeap *minHeap = (struct minHeap *)malloc(sizeof(struct minHeap));

    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct minHeapNode**) malloc(minHeap->capacity * sizeof(struct minHeapNode));

    return minHeap;
}

void swapMinHeapNode(struct minHeapNode** a, struct minHeapNode** b) {
    struct minHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct minHeap* minHeap, int i) {
    int smallest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != i) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[i]);
        minHeapify(minHeap, smallest);
    }
}

int isSize1(struct minHeap* minHeap) {
    return (minHeap->size == 1);
}

struct minHeapNode* extractNode(struct minHeap* minHeap) {
    struct minHeapNode* value = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    minHeap->size--;
    return value;
} 

void insertNode(struct minHeap* minHeap, struct minHeapNode* node) {
    minHeap->size++;
    int i = minHeap->size-1;
    while(i && node->frequency < minHeap->array[(i-1)/2]->frequency) {
        minHeap->array[i] = minHeap->array[(i-1)/2];
        i=(i-1)/2;
    }
    minHeap->array[i] = node;
}

void buildMinHeap(struct minHeap* heap) {
    int n = heap->size-1;
    for(int i = (n-1)/2; i>=0; --i)
        minHeapify(heap, i);
}

int isLeaf(struct minHeapNode* node) {
    return !(node->left) && !(node->right);
}

struct minHeap* createBuildMinHeap(char* data, int* freq, int size) {
    struct minHeap* heap = createMinHeap(size);

    for(int i = 0; i<size; ++i) {
        heap->array[i] = newNode(data[i], freq[i]);
    }
    heap->size = size;
    buildMinHeap(heap);

    return heap;
}

struct minHeapNode* buildHuffmanTree(char* data, int* freq, int size) {
    struct minHeapNode *left, *right, *top;

    struct minHeap* heap = createBuildMinHeap(data, freq, size);

    while(!isSize1(heap)) {
        left = extractNode(heap);
        right = extractNode(heap);

        top = newNode(SPECIAL, left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        insertNode(heap, top);
    }

    return extractNode(heap);
}

void printArr(int *arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printCodes(struct minHeapNode* root, int* arr, int top) {
    if(root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top+1);
    }
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root)) {
        printf("%c: ", root->data);
        printArr(arr, top);
    }
}

void HuffmanCodes(char* data, int* freq, int size) {
    struct minHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[100];
    int top = 0;
    printCodes(root, arr, top);
}

int main() {
    // printf("Test Case 1: \n");
    // char data1[] = {'a','b','c','d'};
    // int freq1[] = {4,3,2,6};
    // int size = sizeof(data1) / sizeof(data1[0]);
    // HuffmanCodes(data1,freq1,size);

    // printf("Test case 2: \n");
    // char data2[] = {'a', 'b', 'c', 'd', 'e'};
    // int freq2[] = {50, 25, 15, 40, 75};
    // size = sizeof(data2) / sizeof(data2[0]);
    // HuffmanCodes(data2, freq2, size);

    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};

    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCodes(arr, freq, size);
}
