// Calculate minimum operations to convert string1 to string2
// Operations: Insert, Delete, Replace
// Input: Two strings

#include <stdio.h>
#include <string.h>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

int editDistUtil(char *str1, char *str2, int m, int n, char *operation) {
    if (m == 0) {
        for(int i = 0; i < n; i++) operation[i] = 'I'; // Insert
        return n;
    }
    if (n == 0) {
        for(int i = 0; i < m; i++) operation[i] = 'D'; // Delete
        return m;
    }

    if (str1[m-1] == str2[n-1]) {
        operation[m+n-1] = 'M'; // Match
        return editDistUtil(str1, str2, m-1, n-1, operation);
    }

    int insert = editDistUtil(str1, str2, m, n-1, operation) + 1;
    int del = editDistUtil(str1, str2, m-1, n, operation) + 1;
    int replace = editDistUtil(str1, str2, m-1, n-1, operation) + 1;

    int min = MIN3(insert, del, replace);
    operation[m+n-1] = min == insert ? 'I' : (min == del ? 'D' : 'R');
    return min;
}

int main() {
    char str1[100], str2[100], operation[200];
    printf("Enter first string: ");
    scanf("%s", str1);
    printf("Enter second string: ");
    scanf("%s", str2);
    
    int dist = editDistUtil(str1, str2, strlen(str1), strlen(str2), operation);
    printf("Edit Distance: %d\n", dist);
    printf("Operations: %s\n", operation);
    return 0;
}

// T(m,n) = T(m-1,n) + T(m,n-1) + T(m-1,n-1) + c
// O(3^(m+n))
