#include <stdio.h>
#include <stdlib.h>

// Function to find the nth Fibonacci number using dynamic programming
long long fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    
    long long* fib = (long long*)malloc((n + 1) * sizeof(long long));
    if (fib == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    fib[0] = 0;
    fib[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    
    long long result = fib[n];
    free(fib);
    
    return result;
}

int main() {
    int n;
    
    printf("Enter the value of n to find the nth Fibonacci number: ");
    scanf("%d", &n);
    
    if (n < 0) {
        printf("Please enter a non-negative integer\n");
        return 1;
    }
    
    printf("The %dth Fibonacci number is: %lld\n", n, fibonacci(n));
    
    return 0;
}
