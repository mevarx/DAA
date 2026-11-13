#include <stdio.h>
#define MAX 50

int main() {
    int n, i, j, id[MAX];
    float W, w[MAX], p[MAX], r[MAX];
    float remaining, totalProfit = 0, t;
    int ti;

    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter capacity: ");
    scanf("%f", &W);
    for (i = 0; i < n; i++) {
        printf("Item %d: Weight and Profit: ", i + 1);
        scanf("%f %f", &w[i], &p[i]);
        r[i] = p[i] / w[i];
        id[i] = i + 1;
    }

    printf("Ratios: ");
    for (i = 0; i < n; i++)
        printf("I%d=%.2f ", id[i], r[i]);
    printf("\n");

    /* bubble sort by ratio, descending (swap everything together) */
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (r[j] < r[j + 1]) {
                t = r[j]; r[j] = r[j + 1]; r[j + 1] = t;
                t = w[j]; w[j] = w[j + 1]; w[j + 1] = t;
                t = p[j]; p[j] = p[j + 1]; p[j + 1] = t;
                ti = id[j]; id[j] = id[j + 1]; id[j + 1] = ti;
            }
        }
    }

    remaining = W;
    for (i = 0; i < n && remaining > 0; i++) {
        if (w[i] <= remaining) {
            printf("I%d: %.0f kg (100%%)\n", id[i], w[i]);
            remaining -= w[i];
            totalProfit += p[i];
        } else {
            float frac = remaining / w[i];
            printf("I%d: %.0f kg (%.2f%%)\n", id[i], remaining, frac * 100);
            totalProfit += p[i] * frac;
            remaining = 0;
        }
    }

    printf("Total Weight = %.0f kg\n", W - remaining);
    printf("Max Profit = %.2f\n", totalProfit);
    return 0;
}