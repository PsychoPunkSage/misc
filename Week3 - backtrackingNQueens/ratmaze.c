#include <stdio.h>
#include <stdbool.h>

#define N 4

bool isSafe(int maze[N][N], int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1);
}

bool solveMaze(int maze[N][N], int x, int y, int sol[N][N]) {
    if (x == N-1 && y == N-1) {
        sol[x][y] = 1;
        return true;
    }
    
    if (isSafe(maze, x, y)) {
        sol[x][y] = 1;
        
        if (solveMaze(maze, x+1, y, sol))
            return true;
        if (solveMaze(maze, x, y+1, sol))
            return true;
            
        sol[x][y] = 0;
        return false;
    }
    return false;
}

int main() {
    int maze[N][N] = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };
    int sol[N][N] = {0};
    
    if (solveMaze(maze, 0, 0, sol)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                printf("%d ", sol[i][j]);
            printf("\n");
        }
    }
    return 0;
}
