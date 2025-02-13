/*
Consider a game board of size N×N where each cell contains a number representing points. A player starts from any cell in the first row and can move only in the following ways:

One step diagonally down-right (i+1, j+1)
One step diagonally down-left (i+1, j-1)
Two steps directly down (i+2, j)

The player needs to reach the last row collecting maximum points. However, if a cell has negative points, it must be avoided (cannot be included in the path).
Write a C program that:

Takes N as input (N ≤ 20)
Takes N×N matrix as input
Finds the path with maximum points that reaches the last row
Prints both the maximum points possible and the path taken
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 20

// Structure to store path information
typedef struct {
    int row;
    int col;
} Position;

// Global variables
int N;
int board[MAX_N][MAX_N];
Position path[MAX_N];  // To store the final path
Position curr_path[MAX_N];  // To store current path during recursion
int max_points = INT_MIN;
int path_length = 0;

// Function to check if position is valid
int isValid(int row, int col) {
    return (row >= 0 && row < N && col >= 0 && col < N && board[row][col] >= 0);
}

// Recursive function to find maximum points path
void findMaxPath(int row, int col, int points, int len) {
    // Base case: reached last row
    if (row == N-1) {
        if (points > max_points) {
            max_points = points;
            path_length = len;
            // Store the path
            for (int i = 0; i < len; i++) {
                path[i] = curr_path[i];
            }
        }
        return;
    }
    
    // Store current position in path
    curr_path[len].row = row;
    curr_path[len].col = col;
    
    // Try diagonal down-right
    if (isValid(row+1, col+1)) {
        findMaxPath(row+1, col+1, points + board[row+1][col+1], len+1);
    }
    
    // Try diagonal down-left
    if (isValid(row+1, col-1)) {
        findMaxPath(row+1, col-1, points + board[row+1][col-1], len+1);
    }
    
    // Try two steps down
    if (isValid(row+2, col)) {
        findMaxPath(row+2, col, points + board[row+2][col], len+1);
    }
}

int main() {
    // Input board size
    printf("Enter board size (N): ");
    scanf("%d", &N);
    
    // Input board values
    printf("Enter board values (N x N matrix):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &board[i][j]);
        }
    }
    
    // Try starting from each position in first row
    for (int j = 0; j < N; j++) {
        if (board[0][j] >= 0) {
            findMaxPath(0, j, board[0][j], 0);
        }
    }
    
    // Print results
    if (max_points == INT_MIN) {
        printf("No valid path exists!\n");
    } else {
        printf("\nMaximum points possible: %d\n", max_points);
        printf("Path taken:\n");
        for (int i = 0; i < path_length; i++) {
            printf("(%d,%d) ", path[i].row, path[i].col);
        }
        printf("\n");
    }
    
    return 0;
}
