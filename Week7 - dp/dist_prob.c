#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to find minimum of three numbers
int min(int x, int y, int z) {
    int min_val = x;
    if (y < min_val) min_val = y;
    if (z < min_val) min_val = z;
    return min_val;
}

// Function to calculate the Edit Distance between two strings
int edit_distance(char* str1, char* str2) {
    int m = strlen(str1);
    int n = strlen(str2);
    
    // Create a 2D dynamic programming table
    int** dp = (int**)malloc((m + 1) * sizeof(int*));
    if (dp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    
    // Fill dp[][] in bottom-up manner
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // If first string is empty, insert all characters of second string
            if (i == 0)
                dp[i][j] = j;
            
            // If second string is empty, remove all characters of first string
            else if (j == 0)
                dp[i][j] = i;
            
            // If last characters of two strings are same, nothing more to do
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            
            // If last characters are different, consider all possibilities
            else
                dp[i][j] = 1 + min(dp[i][j - 1],      // Insert
                                   dp[i - 1][j],      // Remove
                                   dp[i - 1][j - 1]); // Replace
        }
    }
    
    // Store the result
    int result = dp[m][n];
    
    // Free the memory
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

// Function to print the operations to convert str1 to str2
void print_edit_operations(char* str1, char* str2) {
    int m = strlen(str1);
    int n = strlen(str2);
    
    // Create a 2D dynamic programming table
    int** dp = (int**)malloc((m + 1) * sizeof(int*));
    if (dp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    
    // Fill dp[][] in bottom-up manner
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // If first string is empty, insert all characters of second string
            if (i == 0)
                dp[i][j] = j;
            
            // If second string is empty, remove all characters of first string
            else if (j == 0)
                dp[i][j] = i;
            
            // If last characters of two strings are same, nothing more to do
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            
            // If last characters are different, consider all possibilities
            else
                dp[i][j] = 1 + min(dp[i][j - 1],      // Insert
                                   dp[i - 1][j],      // Remove
                                   dp[i - 1][j - 1]); // Replace
        }
    }
    
    // Print the operations
    printf("Edit operations to convert \"%s\" to \"%s\":\n", str1, str2);
    
    int i = m, j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && str1[i - 1] == str2[j - 1]) {
            // Characters are same, no operation needed
            i--;
            j--;
        } else if (j > 0 && (i == 0 || dp[i][j] == dp[i][j - 1] + 1)) {
            // Insert operation
            printf("Insert '%c' at position %d\n", str2[j - 1], i);
            j--;
        } else if (i > 0 && (j == 0 || dp[i][j] == dp[i - 1][j] + 1)) {
            // Remove operation
            printf("Remove '%c' at position %d\n", str1[i - 1], i - 1);
            i--;
        } else {
            // Replace operation
            printf("Replace '%c' with '%c' at position %d\n", str1[i - 1], str2[j - 1], i - 1);
            i--;
            j--;
        }
    }
    
    // Free the memory
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
}

int main() {
    char str1[100], str2[100];
    int choice;
    
    printf("Enter the first string: ");
    scanf("%s", str1);
    
    printf("Enter the second string: ");
    scanf("%s", str2);
    
    printf("1. Calculate Edit Distance\n");
    printf("2. Print Edit Operations\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Edit Distance: %d\n", edit_distance(str1, str2));
    } else if (choice == 2) {
        print_edit_operations(str1, str2);
    } else {
        printf("Invalid choice\n");
    }
    
    return 0;
}
