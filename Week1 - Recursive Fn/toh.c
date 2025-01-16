#include <stdio.h>

void toh(int n, char src, char aux, char dest)
{
    if (n == 1)
    {
        printf("Move disk 1 from rod %c to rod %c\n", src, dest);
        return;
    }

    toh(n - 1, src, dest, aux);

    printf("Moved <%d> from %c to %c\n", n, src, dest);

    toh(n - 1, aux, dest, src);
}

int tohc(int n, char src, char aux, char dest)
{
    if (n == 1)
    {
        printf("Move disk 1 from %c to %c\n", src, dest);
        return 1;
    }

    int moves = 0;

    moves += tohc(n - 1, src, dest, aux);
    printf("Move disk %d from %c to %c\n", n, src, dest);
    moves++;
    moves += tohc(n - 1, aux, src, dest);

    return moves;
}

int main()
{
    int n = 3; // Number of disks
    toh(n, 'A', 'B', 'C');
    int moves = tohc(n, 'A', 'B', 'C');
    printf("Total number of moves: %d\n", moves);
    return 0;
}