#include <stdio.h>
#include <string.h>

void swap(char *x, char *y)
{
    char temp = *x;
    *x = *y;
    *y = temp;
}

int shouldSwap(char *str, int start, int curr) {
    for (int i = start; i < curr; i++)
        if (str[i] == str[curr])
            return 0;
    return 1;
}

int permute(char *str, int l, int r)
{
    int count = 0;
    if (l == r)
    {
        count++;
        printf("%s\n", str);
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
          if (shouldSwap(str,l,i)){
            swap((str + l), (str + i));
            permute(str, l + 1, r);
            swap((str + l), (str + i));
          }
        }
    }
}

int main()
{
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    int c = permute(str, 0, strlen(str) - 1);
    printf("combinations: %d\n", c);
    return 0;
}
