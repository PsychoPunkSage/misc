#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to solve the coin change problem (minimum number of coins)
int min_coins(int coins[], int n, int amount) {
    // Create the dynamic programming table
    int* dp = (int*)malloc((amount + 1) * sizeof(int));
    if (dp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    // Base case (If amount = 0)
    dp[0] = 0;
    
    // Initialize all dp values as infinite
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX;
    }
    
    // Fill dp[] for all amounts from 1 to amount
    for (int i = 1; i <= amount; i++) {
        // Go through all coins smaller than i
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i) {
                int sub_res = dp[i - coins[j]];
                if (sub_res != INT_MAX && sub_res + 1 < dp[i]) {
                    dp[i] = sub_res + 1;
                }
            }
        }
    }
    
    // Store the result
    int result = dp[amount];
    
    // Free the memory
    free(dp);
    
    // If no solution exists
    if (result == INT_MAX) {
        return -1;
    }
    
    return result;
}

// Function to count the total number of ways to make change
int count_ways(int coins[], int n, int amount) {
    // Create the dynamic programming table
    int* dp = (int*)malloc((amount + 1) * sizeof(int));
    if (dp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    // Base case (If amount = 0)
    dp[0] = 1;
    
    // Initialize all other dp values as 0
    for (int i = 1; i <= amount; i++) {
        dp[i] = 0;
    }
    
    // Fill dp[] for all amounts from 1 to amount
    for (int i = 0; i < n; i++) {
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    
    // Store the result
    int result = dp[amount];
    
    // Free the memory
    free(dp);
    
    return result;
}

int main() {
    int n, amount, choice;
    
    printf("Coin Change Problem\n");
    printf("1. Find minimum number of coins required\n");
    printf("2. Count total number of ways to make change\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    
    printf("Enter the number of coins: ");
    scanf("%d", &n);
    
    int* coins = (int*)malloc(n * sizeof(int));
    if (coins == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter the values of the %d coins:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }
    
    printf("Enter the amount: ");
    scanf("%d", &amount);
    
    if (choice == 1) {
        int result = min_coins(coins, n, amount);
        if (result == -1)
            printf("It's not possible to make change for %d\n", amount);
        else
            printf("Minimum number of coins required: %d\n", result);
    } else if (choice == 2) {
        printf("Total number of ways to make change: %d\n", count_ways(coins, n, amount));
    } else {
        printf("Invalid choice\n");
    }
    
    free(coins);
    
    return 0;
}
