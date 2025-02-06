/*
Problem: Karatsuba Multiplication
Description: Multiply two large numbers using Karatsuba's divide and conquer algorithm.
This is faster than the traditional multiplication for very large numbers.
Time Complexity: O(n^log₂3) ≈ O(n^1.585)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to make the length of strings equal by adding zeros at start
void makeEqualLength(char* str1, char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if (len1 < len2) {
        for (int i = len1; i < len2; i++)
            str1[i] = '0';
        str1[len2] = '\0';
    } else if (len2 < len1) {
        for (int i = len2; i < len1; i++)
            str2[i] = '0';
        str2[len1] = '\0';
    }
}

// Add two bit strings
char* addBitStrings(char* first, char* second) {
    int length = strlen(first);
    char* result = (char*)malloc((length + 1) * sizeof(char));
    char carry = '0';
    
    for (int i = length - 1; i >= 0; i--) {
        if (first[i] == '1' && second[i] == '1') {
            result[i] = (carry == '0') ? '0' : '1';
            carry = '1';
        }
        else if (first[i] == '0' && second[i] == '0') {
            result[i] = carry;
            carry = '0';
        }
        else {
            result[i] = (carry == '0') ? '1' : '0';
        }
    }
    result[length] = '\0';
    return result;
}

// Multiply two bit strings using Karatsuba algorithm
char* multiply(char* X, char* Y) {
    int n = strlen(X);
    
    // Base cases
    if (n == 0) return "0";
    if (n == 1) {
        char* result = (char*)malloc(2 * sizeof(char));
        result[0] = ((X[0] - '0') * (Y[0] - '0')) + '0';
        result[1] = '\0';
        return result;
    }
    
    int mid = n/2;
    char* Xl = (char*)malloc((mid + 1) * sizeof(char));
    char* Xr = (char*)malloc((n - mid + 1) * sizeof(char));
    char* Yl = (char*)malloc((mid + 1) * sizeof(char));
    char* Yr = (char*)malloc((n - mid + 1) * sizeof(char));
    
    // Split the strings
    strncpy(Xl, X, mid);
    Xl[mid] = '\0';
    strcpy(Xr, X + mid);
    strncpy(Yl, Y, mid);
    Yl[mid] = '\0';
    strcpy(Yr, Y + mid);
    
    // Recursive steps
    char* P1 = multiply(Xl, Yl);
    char* P2 = multiply(Xr, Yr);
    
    char* sum1 = addBitStrings(Xl, Xr);
    char* sum2 = addBitStrings(Yl, Yr);
    char* P3 = multiply(sum1, sum2);
    
    // Combine results
    char* temp1 = addBitStrings(P1, P2);
    char* temp2 = addBitStrings(P3, temp1);
    
    // Free memory
    free(Xl); free(Xr); free(Yl); free(Yr);
    free(sum1); free(sum2); free(P1); free(P2); free(P3); free(temp1);
    
    return temp2;
}

int main() {
    char num1[1000], num2[1000];
    
    printf("Enter first binary number: ");
    scanf("%s", num1);
    printf("Enter second binary number: ");
    scanf("%s", num2);
    
    makeEqualLength(num1, num2);
    char* result = multiply(num1, num2);
    
    printf("Product: %s\n", result);
    free(result);
    
    return 0;
}
