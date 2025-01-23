#include <stdio.h>
#include <stdbool.h>

#define N 4 // Size of chess board

bool isSafe(int board[N][N], int row, int col)
{
    int i, j;

    // Check row on left side
    for (j = 0; j < col; j++)
        if (board[row][j])
            return false;

    // Check upper diagonal
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal
    for (i = row, j = col; i < N && j >= 0; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

bool solveNQueens(int board[N][N], int col)
{
    if (col >= N)
        return true;

    for (int row = 0; row < N; row++)
    {
        if (isSafe(board, row, col))
        {
            board[row][col] = 1;

            if (solveNQueens(board, col + 1))
                return true;

            board[row][col] = 0; // Backtrack
        }
    }
    return false;
}

int main()
{
    int board[N][N] = {0};

    if (!solveNQueens(board, 0))
    {
        printf("Solution doesn't exist");
        return 0;
    }

    // Print solution
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }
    return 0;
}