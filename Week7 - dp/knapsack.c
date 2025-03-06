#include <stdio.h>
#include <stdlib.h>

// Function to find maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve the 0/1 Knapsack problem using dynamic programming
int knapsack(int W, int wt[], int val[], int n) {
    // Create a dynamic programming table
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    if (dp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((W + 1) * sizeof(int));
        if (dp[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    
    // Build table dp[][] in bottom-up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    
    // Store the result
    int result = dp[n][W];
    
    // Free the memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

int main() {
    int n, W;
    
    printf("Enter the number of items: ");
    scanf("%d", &n);
    
    int* val = (int*)malloc(n * sizeof(int));
    int* wt = (int*)malloc(n * sizeof(int));
    
    if (val == NULL || wt == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter the values of the %d items:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val[i]);
    }
    
    printf("Enter the weights of the %d items:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &wt[i]);
    }
    
    printf("Enter the maximum weight capacity: ");
    scanf("%d", &W);
    
    printf("The maximum value that can be obtained is: %d\n", knapsack(W, wt, val, n));
    
    free(val);
    free(wt);
    
    return 0;
}
