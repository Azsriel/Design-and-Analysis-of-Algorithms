#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max(int a, int b)
{
    return ((a > b) ? a : b);
}

int max3(int a, int b, int c)
{
    return max(max(a, b), c);
}

int maxCrossSum(int *arr, int start, int pivot, int end)
{
    int leftSum = INT_MIN;
    int sum = 0;
    int i = pivot;
    for (i = pivot; i >= 0; --i)
    {
        sum += arr[i];
        if (sum > leftSum)
            leftSum = sum;
    }

    int rightSum = INT_MIN;
    sum = 0;
    for (int i = pivot; i < end; ++i)
    {
        sum += arr[i];
        if (sum > rightSum)
            rightSum = sum;
    }

    return max3(leftSum + rightSum - arr[pivot], leftSum, rightSum);
}

struct MinHeapNode
{
    char data;

    unsigned freq;

    struct MinHeapNode *left, *right;
};

struct MinHeap
{
    unsigned size;

    unsigned capacity;

    struct MinHeapNode **array;
};
struct MinHeapNode *newNode(char data, unsigned freq)
{
    struct MinHeapNode *temp = (struct MinHeapNode *)malloc(
        sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

struct MinHeap *createMinHeap(unsigned capacity)

{

    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));

    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array = (struct MinHeapNode **)malloc(
        minHeap->capacity * sizeof(struct MinHeapNode *));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b)

{

    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx)

{

    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap *minHeap)
{

    return (minHeap->size == 1);
}
struct MinHeapNode *extractMin(struct MinHeap *minHeap)

{

    struct MinHeapNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

void insertMinHeap(struct MinHeap *minHeap, struct MinHeapNode *minHeapNode)

{

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap *minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

int isLeaf(struct MinHeapNode *root)

{

    return !(root->left) && !(root->right);
}

struct MinHeap *createAndBuildMinHeap(char data[], int freq[], int size)

{

    struct MinHeap *minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

struct MinHeapNode *buildHuffmanTree(char data[], int freq[], int size)

{
    struct MinHeapNode *left, *right, *top;
    struct MinHeap *minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap))
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}
void printCodes(struct MinHeapNode *root, int arr[], int top)

{
    if (root->left)
    {

        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right)
    {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root))
    {

        printf("%c: ", root->data);
        printArr(arr, top);
    }
}

void printArr(int *arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort(int *arr, int n)
{
    for (int i = 1; i < n; ++i)
    {
        for (int j = i; j >= 1; --j)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(&arr[j], &arr[j - 1]);
            }
        }
    }
}

int binarySearch(int *arr, int target, int start, int end)
{
    if (start > end)
        return -1;
    int mid = (start + end) / 2;
    if (arr[mid] == target)
        return mid;
    else if (arr[mid] < target)
        return binarySearch(arr, target, mid + 1, end);
    else
        return binarySearch(arr, target, start, mid);
}

void merge(int *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}


int isArrEqual(int *a, int *b, int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

void swap2(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort2(int *p, int *w, float *pw, int n)
{
    for (int i = 1; i < n; ++i)
    {
        for (int j = i; j >= 1; --j)
        {
            if (pw[j] > pw[j - 1])
            {
                swap2(&pw[j], &pw[j - 1]);
                swap(&p[j], &p[j - 1]);
                swap(&w[j], &w[j - 1]);
            }
        }
    }
}

/*----------------------------------------------------*/
void mergeSort(int *arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

float fractionalKnapsack(int profits[], int weights[], int n, int maxCapacity)
{
    float pw[n];
    for (int i = 0; i < n; ++i)
    {
        pw[i] = (float)profits[i] / weights[i];
    }

    insertionSort2(profits, weights, pw, n);

    int currentCapacity = 0;
    float currentprofit = 0;
    for (int i = 0; i < n; ++i)
    {
        int currentAmount = (currentCapacity + weights[i] <= maxCapacity) ? weights[i] : maxCapacity - currentCapacity;
        currentprofit += profits[i] * (float)currentAmount / weights[i];
        currentCapacity += currentAmount;
    }
    return currentprofit;
}

void HuffmanCodes(char data[], int freq[], int size)

{
    struct MinHeapNode *root = buildHuffmanTree(data, freq, size);

    int arr[100], top = 0;

    printCodes(root, arr, top);
}

int maxSubArray(int *arr, int start, int end)
{
    // Break condition
    if (start == end)
        return arr[start];
    if (start > end)
        return INT_MIN;

    int pivot = (start + end) / 2;
    int leftSum = maxSubArray(arr, 0, pivot);
    int rightSum = maxSubArray(arr, pivot + 1, end);
    int crossSum = maxCrossSum(arr, start, pivot, end);
    return max3(leftSum, rightSum, crossSum);
}

// TODO Karatsuba's Multiplication Algorithm
// TODO Assembly Line Scheduling
// TODO Matrix chain Multiplication optimization

int main()
{

}