/*
Given an N×N chess board, find a path for a knight starting from (0,0) such that:

The knight can only move in a spiral pattern (must visit outer cells before inner cells)
Each move must be a valid knight's move
Each cell must be visited exactly once
If a complete spiral tour isn't possible, find the maximum cells that can be visited following the spiral pattern
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20

// Knight's possible moves
int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

// Global variables
int N;
int board[MAX_N][MAX_N];
int max_moves = 0;
int path[MAX_N * MAX_N][2];

// Function to calculate distance from center
int getDistanceFromCenter(int x, int y) {
    int center = N/2;
    return abs(x - center) + abs(y - center);
}

// Function to check if move is valid
int isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Function to find the next valid move
void findTour(int x, int y, int moveCount) {
    // Mark current cell
    board[x][y] = moveCount;
    path[moveCount][0] = x;
    path[moveCount][1] = y;

    // Update max moves if current path is longer
    if (moveCount + 1 > max_moves) {
        max_moves = moveCount + 1;
    }

    // Array to store possible next moves
    struct {
        int x, y;
        int dist;
    } moves[8];
    int moveNum = 0;

    // Get all possible valid moves
    for (int i = 0; i < 8; i++) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];

        if (isValid(nextX, nextY)) {
            moves[moveNum].x = nextX;
            moves[moveNum].y = nextY;
            moves[moveNum].dist = getDistanceFromCenter(nextX, nextY);
            moveNum++;
        }
    }

    // Sort moves by distance from center (bubble sort)
    for (int i = 0; i < moveNum - 1; i++) {
        for (int j = 0; j < moveNum - i - 1; j++) {
            if (moves[j].dist < moves[j + 1].dist) {
                int tempX = moves[j].x;
                int tempY = moves[j].y;
                int tempDist = moves[j].dist;
                moves[j].x = moves[j + 1].x;
                moves[j].y = moves[j + 1].y;
                moves[j].dist = moves[j + 1].dist;
                moves[j + 1].x = tempX;
                moves[j + 1].y = tempY;
                moves[j + 1].dist = tempDist;
            }
        }
    }

    // Try each move
    for (int i = 0; i < moveNum; i++) {
        findTour(moves[i].x, moves[i].y, moveCount + 1);
    }

    // Backtrack
    board[x][y] = -1;
}

int main() {
    printf("Enter the board size (N): ");
    scanf("%d", &N);

    if (N <= 0 || N > MAX_N) {
        printf("Invalid board size\n");
        return 1;
    }

    // Initialize board
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = -1;
        }
    }

    // Start from (0,0)
    findTour(0, 0, 0);

    // Print results
    printf("\nMaximum cells visited: %d\n", max_moves);
    printf("Path taken:\n");
    for (int i = 0; i < max_moves; i++) {
        printf("(%d,%d) ", path[i][0], path[i][1]);
        if ((i + 1) % 5 == 0) printf("\n");
    }
    printf("\n\nBoard visualization:\n");

    // Initialize visualization board
    int visualBoard[MAX_N][MAX_N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visualBoard[i][j] = -1;
        }
    }

    // Fill in the path
    for (int i = 0; i < max_moves; i++) {
        visualBoard[path[i][0]][path[i][1]] = i;
    }

    // Print the board
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (visualBoard[i][j] == -1)
                printf(" X  ");
            else
                printf("%2d  ", visualBoard[i][j]);
        }
        printf("\n");
    }

    return 0;
}
