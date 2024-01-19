#include <stdio.h>
#include <assert.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort(int* arr, int n) {
    for(int i = 1; i < n; ++i) {
        for (int j = i; j >= 1; --j) {
            if (arr[j] < arr[j-1]) {
                swap(&arr[j], &arr[j-1]);
            }
        }
    }
}

int binarySearch(int* arr, int target, int start, int end) {
    if (start > end) return -1;
    int mid = (start + end) / 2;
    if (arr[mid] == target) return mid;
    else if (arr[mid] < target) return binarySearch(arr, target, mid+1, end);
    else return binarySearch(arr, target, start, mid);
}

void merge(int* arr, int l, int m, int r)
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

void mergeSort(int* arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int isArrEqual(int* a, int* b, int n) {
    for(int i = 0; i< n; ++i) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

void printArr(int* arr, int n) {
    for(int i = 0; i< n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {4,3,5,1,6,9,7};
    int arr2[] = {4, 3, 5, 1, 6, 9, 7};

    insertionSort(arr, 7);
    mergeSort(arr2, 0, 6);
    assert(isArrEqual(arr, arr2, 7));

    printf("Sorted Array: \n");
    printArr(arr,7);
    // Array given to binary search must be sorted
    int find1 = binarySearch(arr, 7, 0, 6);
    assert(find1 == 5);
    printf("Element 7 is at location: %d\n", find1);

    find1 = binarySearch(arr, 10, 0, 6);
    assert(find1 == -1);
    printf("Element 10 does not exist in array\n");

}