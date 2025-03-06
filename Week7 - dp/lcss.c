#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to find maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to find the length of the Longest Common Subsequence of two strings
int lcs_length(char* X, char* Y, int m, int n) {
    // Create a dynamic programming table
    int** L = (int**)malloc((m + 1) * sizeof(int*));
    if (L == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for (int i = 0; i <= m; i++) {
        L[i] = (int*)malloc((n + 1) * sizeof(int));
        if (L[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    
    // Build L[m+1][n+1] in bottom-up fashion
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
    
    // Store the result
    int result = L[m][n];
    
    // Free the memory
    for (int i = 0; i <= m; i++) {
        free(L[i]);
    }
    free(L);
    
    return result;
}

// Function to print the Longest Common Subsequence
void print_lcs(char* X, char* Y, int m, int n) {
    // Create a dynamic programming table
    int** L = (int**)malloc((m + 1) * sizeof(int*));
    if (L == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for (int i = 0; i <= m; i++) {
        L[i] = (int*)malloc((n + 1) * sizeof(int));
        if (L[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    
    // Build L[m+1][n+1] in bottom-up fashion
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
    
    // Create a character array to store the LCS
    int index = L[m][n];
    char* lcs = (char*)malloc((index + 1) * sizeof(char));
    if (lcs == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    // Set the terminating character
    lcs[index] = '\0';
    
    // Start from the right-bottom corner and get the LCS
    int i = m, j = n;
    while (i > 0 && j > 0) {
        // If current characters in X and Y are same, then
        // they are part of LCS
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1]; // Add to result
            i--;
            j--;
            index--;
        }
        // If not same, then find the larger of two and
        // move in the direction of larger value
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }
    
    // Print the LCS
    printf("Longest Common Subsequence: %s\n", lcs);
    
    // Free the memory
    free(lcs);
    for (int i = 0; i <= m; i++) {
        free(L[i]);
    }
    free(L);
}

int main() {
    char X[100], Y[100];
    
    printf("Enter the first string: ");
    scanf("%s", X);
    
    printf("Enter the second string: ");
    scanf("%s", Y);
    
    int m = strlen(X);
    int n = strlen(Y);
    
    printf("Length of Longest Common Subsequence: %d\n", lcs_length(X, Y, m, n));
    
    print_lcs(X, Y, m, n);
    
    return 0;
}
