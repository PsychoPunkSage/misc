#include <stdio.h>
#include <stdbool.h>

#define N 8

int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool isSafe(int x, int y, int sol[N][N]) {
    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1);
}

bool solveKT(int x, int y, int movei, int sol[N][N]) {
    if (movei == N*N)
        return true;

    for (int k = 0; k < 8; k++) {
        int next_x = x + xMove[k];
        int next_y = y + yMove[k];
        
        if (isSafe(next_x, next_y, sol)) {
            sol[next_x][next_y] = movei;
            if (solveKT(next_x, next_y, movei + 1, sol))
                return true;
            sol[next_x][next_y] = -1;
        }
    }
    return false;
}

int main() {
    int sol[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sol[i][j] = -1;
    
    sol[0][0] = 0;
    if (solveKT(0, 0, 1, sol)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                printf("%2d ", sol[i][j]);
            printf("\n");
        }
    }
    return 0;
}
