// Find longest common subsequence of two strings and print the sequence
// Input: Two strings

#include <stdio.h>
#include <string.h>

#define MAX 1000

void printLCS(char b[MAX][MAX], char X[], int i, int j) {
    if (i == 0 || j == 0)
        return;
    if (b[i][j] == 'D') {
        printLCS(b, X, i-1, j-1);
        printf("%c", X[i-1]);
    }
    else if (b[i][j] == 'U')
        printLCS(b, X, i-1, j);
    else
        printLCS(b, X, i, j-1);
}

void LCS(char X[], char Y[]) {
    int m = strlen(X);
    int n = strlen(Y);
    int L[MAX][MAX];
    char b[MAX][MAX];
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i-1] == Y[j-1]) {
                L[i][j] = L[i-1][j-1] + 1;
                b[i][j] = 'D';  // diagonal
            }
            else if (L[i-1][j] >= L[i][j-1]) {
                L[i][j] = L[i-1][j];
                b[i][j] = 'U';  // up
            }
            else {
                L[i][j] = L[i][j-1];
                b[i][j] = 'L';  // left
            }
        }
    }
    
    printf("Length of LCS is %d\n", L[m][n]);
    printf("LCS is: ");
    printLCS(b, X, m, n);
    printf("\n");
}

int main() {
    char X[MAX], Y[MAX];
    printf("Enter first string: ");
    scanf("%s", X);
    printf("Enter second string: ");
    scanf("%s", Y);
    
    LCS(X, Y);
    return 0;
}

// Time Complexity Recursion for printing: T(n,m) = T(n-1,m-1) + c
// Overall complexity: O(mn)
