#include <stdio.h>

int fib(int n)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }

    return fib(n - 2) + fib(n - 1);
}

int main()
{
    int nth;

    printf("Enter the position of the Fibonacci number: ");
    scanf("%d", &nth);

    if (nth <= 0)
    {
        printf("Invalid number");
    }
    else
    {
        int ans = fib(nth);
        printf("Ans (%d) = %d", nth, ans);
    }

    return 0;
}