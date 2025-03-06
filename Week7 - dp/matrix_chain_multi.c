#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to solve the Matrix Chain Multiplication problem
int matrix_chain_order(int p[], int n) {
    // Create a 2D table for storing results
    int** m = (int**)malloc(n * sizeof(int*));
    if (m == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for (int i = 0; i < n; i++) {
        m[i] = (int*)malloc(n * sizeof(int));
        if (m[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        
        // Initialize the diagonal (single matrix: no multiplication needed)
        m[i][i] = 0;
    }
    
    // l is chain length
    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            
            // Try each possible splitting point
            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                }
            }
        }
    }
    
    // Store the result
    int result = m[1][n - 1];
    
    // Free the memory
    for (int i = 0; i < n; i++) {
        free(m[i]);
    }
    free(m);
    
    return result;
}

// Function to print the optimal parenthesization
void print_optimal_parens(int** s, int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        printf(")");
    }
}

// Function to solve and print the optimal parenthesization
void matrix_chain_with_parens(int p[], int n) {
    // Create m and s tables
    int** m = (int**)malloc(n * sizeof(int*));
    int** s = (int**)malloc(n * sizeof(int*));
    
    if (m == NULL || s == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for (int i = 0; i < n; i++) {
        m[i] = (int*)malloc(n * sizeof(int));
        s[i] = (int*)malloc(n * sizeof(int));
        
        if (m[i] == NULL || s[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        
        // Initialize the diagonal
        m[i][i] = 0;
    }
    
    // l is chain length
    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            
            // Try each possible splitting point
            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
    
    // Print the optimal parenthesization
    printf("Optimal Parenthesization: ");
    print_optimal_parens(s, 1, n - 1);
    printf("\n");
    
    printf("Minimum number of multiplications: %d\n", m[1][n - 1]);
    
    // Free the memory
    for (int i = 0; i < n; i++) {
        free(m[i]);
        free(s[i]);
    }
    free(m);
    free(s);
}

int main() {
    int n;
    
    printf("Enter the number of matrices: ");
    scanf("%d", &n);
    
    // Array p[] of size n+1 such that p[i-1] * p[i] is the dimension of matrix i
    int* p = (int*)malloc((n + 1) * sizeof(int));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter the dimensions:\n");
    for (int i = 0; i <= n; i++) {
        printf("d%d: ", i);
        scanf("%d", &p[i]);
    }
    
    printf("Minimum number of multiplications: %d\n", matrix_chain_order(p, n + 1));
    
    // Uncomment the line below to print the optimal parenthesization
    // matrix_chain_with_parens(p, n + 1);
    
    free(p);
    
    return 0;
}
