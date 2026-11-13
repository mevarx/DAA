#include <stdio.h>
#define MAX 100

void insertionSort(float a[], int n) {
    for (int i = 1; i < n; i++) {
        float key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

int main() {
    int n, i, j, k = 0;
    float arr[MAX], bucket[MAX][MAX];
    int count[MAX] = {0};          /* number of elements in each bucket */

    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
        scanf("%f", &arr[i]);

    printf("Original Array:\n");
    for (i = 0; i < n; i++)
        printf("%.2f ", arr[i]);

    /* 1. distribute into buckets */
    for (i = 0; i < n; i++) {
        int idx = (int)(n * arr[i]);
        bucket[idx][count[idx]] = arr[i];
        count[idx]++;
    }

    /* 2. sort each bucket */
    for (i = 0; i < n; i++)
        insertionSort(bucket[i], count[i]);

    /* 3. combine */
    for (i = 0; i < n; i++)
        for (j = 0; j < count[i]; j++)
            arr[k++] = bucket[i][j];

    printf("\nSorted Array:\n");
    for (i = 0; i < n; i++)
        printf("%.2f ", arr[i]);
    printf("\n");
    return 0;
}