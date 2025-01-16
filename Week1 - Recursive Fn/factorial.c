#include <stdio.h>

int factorial(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }

    return n * factorial(n - 1);
}

int main()
{
    printf("Enter the number:");
    int num;
    scanf("%d", &num);

    if (num < 0)
    {
        printf("Wrong Input");
    }
    else
    {
        int ans = factorial(num);
        printf("Factorial of %d is: %d\n", num, ans);
    }

    return 0;
}