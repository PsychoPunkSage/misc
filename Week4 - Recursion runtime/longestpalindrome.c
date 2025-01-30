// Find longest palindromic subsequence in a string and print it
// Input: String

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to get maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to find length of Longest Palindromic Subsequence
// Also stores the sequence in dp table for later reconstruction
int** findLPSLength(char* str, int n) {
    // Allocate memory for dp table
    int** dp = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        dp[i] = (int*)malloc(n * sizeof(int));
        // Initialize with 0
        memset(dp[i], 0, n * sizeof(int));
        // Single characters are palindromes of length 1
        dp[i][i] = 1;
    }
    
    // Build table for different lengths
    for(int len = 2; len <= n; len++) {
        for(int start = 0; start < n - len + 1; start++) {
            int end = start + len - 1;
            
            // If first and last characters match
            if(str[start] == str[end] && len == 2)
                dp[start][end] = 2;
            else if(str[start] == str[end])
                dp[start][end] = dp[start + 1][end - 1] + 2;
            else
                dp[start][end] = max(dp[start + 1][end], dp[start][end - 1]);
        }
    }
    
    return dp;
}

// Function to print the Longest Palindromic Subsequence
void printLPS(char* str, int** dp, int start, int end, char* result, int* resIndex) {
    if(start > end) 
        return;
        
    // If only one character
    if(start == end) {
        result[(*resIndex)++] = str[start];
        return;
    }
    
    // If first and last characters match
    if(str[start] == str[end]) {
        result[(*resIndex)++] = str[start];
        printLPS(str, dp, start + 1, end - 1, result, resIndex);
        if(start != end - 1) // Don't duplicate middle character
            result[(*resIndex)++] = str[end];
    }
    // If they don't match, find the longer sequence
    else if(dp[start + 1][end] > dp[start][end - 1])
        printLPS(str, dp, start + 1, end, result, resIndex);
    else
        printLPS(str, dp, start, end - 1, result, resIndex);
}

int main() {
    char str[1000];
    printf("Enter the string: ");
    scanf("%s", str);
    
    int n = strlen(str);
    
    // Get the dp table and length
    int** dp = findLPSLength(str, n);
    
    // Allocate memory for result string
    char* result = (char*)malloc((n + 1) * sizeof(char));
    int resIndex = 0;
    
    // Print length
    printf("Length of Longest Palindromic Subsequence is: %d\n", dp[0][n-1]);
    
    // Get and print the sequence
    printf("The Longest Palindromic Subsequence is: ");
    printLPS(str, dp, 0, n-1, result, &resIndex);
    result[resIndex] = '\0';
    printf("%s\n", result);
    
    // Free allocated memory
    for(int i = 0; i < n; i++)
        free(dp[i]);
    free(dp);
    free(result);
    
    return 0;
}

// T(n) = 2T(n-1) + c
// O(2ᶰ)
