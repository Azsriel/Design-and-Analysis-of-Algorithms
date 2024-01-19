#include <stdio.h>
#include <assert.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void swap2(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort(int *p, int* w, float* pw, int n)
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

float fractionalKnapsack(int profits[], int weights[], int n, int maxCapacity) {
    float pw[n];
    for(int i = 0; i<n; ++i) {
        pw[i] = (float)profits[i] / weights[i];
    }

    insertionSort(profits, weights, pw, n);

    int currentCapacity = 0;
    float currentprofit = 0;
    for(int i = 0; i<n; ++i) {
        int currentAmount = (currentCapacity + weights[i] <= maxCapacity) ? weights[i] : maxCapacity - currentCapacity;
        currentprofit += profits[i] * (float)currentAmount / weights[i];
        currentCapacity += currentAmount;
    }
    return currentprofit;
}

int main() {
    int p[] = {3,6,1,4};
    int w[] = {6,1,5,3};
    int n = 4;
    int c = 10;

    float ans = fractionalKnapsack(p, w, n, c);
    assert(ans == 13.0);
    printf("First Test case passed\n");

    int p1[] = {5,10,15,7,8,9,4};
    int w1[] = {1,3,5,4,1,3,2};
    int n1 = 7;
    int c1 = 15;

    // Test case is wrong in the question paper. Correct answer is 51, not 47.25
    ans = fractionalKnapsack(p1, w1, n1, c1);
    assert(ans == 51.0);
    printf("Second Test case passed\n");

    int p2[] = {10,5,15,7,6,18,3};
    int w2[] = {2,3,5,7,1,4,1};
    int n2 = 7;
    int c2 = 15;

    // Test case is wrong in the question paper. Correct answer is 55.3, not 54.6
    ans = fractionalKnapsack(p2, w2, n2, c2);
    // The int conversions are because float comparisons are weird in c. Checked using debugger that values are correct
    assert((int)ans == (int)55.3333321);
    printf("Third Test case passed\n");
}