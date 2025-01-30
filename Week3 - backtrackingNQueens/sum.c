#include <stdio.h>
#include <stdbool.h>

/*
Name: <Your name>
Roll: <Your roll>
Assignment: 3
*/

static int xMove[] = {2, 1, -1, -2, -2, -1, 1, 2};
static int yMove[] = {1, 2, 2, 1, -1, -2, -2, -1};
static int maxCells = 1;
static int bestBoard[10][10];

bool isValid(int x, int y, int n, int board[n][n])
{
    return (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == -1);
}

void copyBoard(int n, int src[n][n], int dest[n][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dest[i][j] = src[i][j];
}

void printBoard(int n, int board[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == -1)
                printf("x ");
            else
                printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

void tourUtil(int x, int y, int moveCount, int n, int board[n][n], bool *found)
{
    if (moveCount > maxCells)
    {
        maxCells = moveCount;
        copyBoard(n, board, bestBoard);
    }

    if (moveCount == n * n)
    {
        *found = true;
        copyBoard(n, board, bestBoard);
        return;
    }

    for (int k = 0; k < 8; k++)
    {
        int nextX = x + xMove[k];
        int nextY = y + yMove[k];

        if (isValid(nextX, nextY, n, board))
        {
            board[nextX][nextY] = moveCount;
            tourUtil(nextX, nextY, moveCount + 1, n, board, found);
            if (*found)
                return;
            board[nextX][nextY] = -1;
        }
    }
}

int main()
{
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    int board[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            board[i][j] = -1;
            bestBoard[i][j] = -1;
        }

    board[0][0] = 0;
    bestBoard[0][0] = 0;
    bool found = false;

    tourUtil(0, 0, 1, n, board, &found);

    if (found)
        printf("A knight's tour exists:\n");
    else
        printf("A knight's tour does not exist, a longest tour is:\n");

    printBoard(n, bestBoard);

    return 0;
}