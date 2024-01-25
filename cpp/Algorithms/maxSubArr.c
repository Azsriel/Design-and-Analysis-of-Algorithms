#include <stdio.h>
#include <limits.h>

int max(int a, int b) {
    return ((a > b) ? a : b);
}

int max3(int a, int b, int c) {
    return max(max(a,b),c);
}

int maxCrossSum(int* arr, int start, int pivot, int end) {
    int leftSum = INT_MIN;
    int sum = 0;
    int i = pivot;
    for (i = pivot; i>= 0; --i) {
        sum += arr[i];
        if(sum > leftSum)
            leftSum = sum;
    }

    int rightSum = INT_MIN;
    sum = 0;
    for(int i = pivot; i< end; ++i) {
        sum += arr[i];
        if(sum > rightSum)
            rightSum = sum;
    }

    return max3(leftSum + rightSum - arr[pivot], leftSum, rightSum);

}

int maxSubArray(int* arr, int start, int end) {
    // Break condition
    if (start == end) return arr[start];
    if (start > end) return INT_MIN;

    int pivot = (start + end) / 2;
    int leftSum = maxSubArray(arr, 0, pivot);
    int rightSum = maxSubArray(arr,pivot+1, end);
    int crossSum = maxCrossSum(arr, start, pivot, end);
    return max3(leftSum, rightSum, crossSum);
}

int main() {
    int arr[] = {1,-3, 2, -5, 7, 6, -1, -4, 11, -23};
    printf("%d\n", maxSubArray(arr, 0, 10));
}