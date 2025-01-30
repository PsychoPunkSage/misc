#include <stdio.h>
#include <string.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void permute(char *str, int left, int right) {
    if (left == right)
        printf("%s\n", str);
    else {
        for (int i = left; i <= right; i++) {
            swap(&str[left], &str[i]);
            permute(str, left + 1, right);
            swap(&str[left], &str[i]); // backtrack
        }
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    printf("All permutations are:\n");
    permute(str, 0, strlen(str) - 1);
    return 0;
}

// Time Complexity Recursion: T(n) = n × T(n-1) + c
// Solves to: O(n!)
