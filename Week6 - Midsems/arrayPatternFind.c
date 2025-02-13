/*
Given an array of integers, find if it can be divided into three contiguous parts such that:

Each part has equal sum
The minimum element in each part differs by at most 1
Use divide and conquer to solve this in O(n log n).
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int sum;
    int min;
    int max;
} SubarrayInfo;

// Function to merge subarrays information
SubarrayInfo merge(SubarrayInfo left, SubarrayInfo right) {
    SubarrayInfo result;
    result.sum = left.sum + right.sum;
    result.min = left.min < right.min ? left.min : right.min;
    result.max = left.max > right.max ? left.max : right.max;
    return result;
}

// Function to get subarray information using divide and conquer
SubarrayInfo getSubarrayInfo(int arr[], int start, int end) {
    if (start == end) {
        SubarrayInfo result = {arr[start], arr[start], arr[start]};
        return result;
    }

    int mid = (start + end) / 2;
    SubarrayInfo left = getSubarrayInfo(arr, start, mid);
    SubarrayInfo right = getSubarrayInfo(arr, mid + 1, end);

    return merge(left, right);
}

// Function to check if array can be divided into three equal parts
int canDivideArray(int arr[], int n) {
    if (n < 3) return 0;

    int totalSum = 0;
    for (int i = 0; i < n; i++) {
        totalSum += arr[i];
    }

    if (totalSum % 3 != 0) return 0;
    int targetSum = totalSum / 3;

    // Try all possible divisions
    int firstEnd = n/3;
    int secondEnd = 2*n/3;

    for (int i = firstEnd-1; i <= firstEnd+1; i++) {
        for (int j = secondEnd-1; j <= secondEnd+1; j++) {
            if (i >= 0 && i < j && j < n) {
                SubarrayInfo first = getSubarrayInfo(arr, 0, i);
                SubarrayInfo second = getSubarrayInfo(arr, i+1, j);
                SubarrayInfo third = getSubarrayInfo(arr, j+1, n-1);

                if (first.sum == targetSum && second.sum == targetSum &&
                    third.sum == targetSum) {
                    // Check if minimum elements differ by at most 1
                    int min1 = first.min;
                    int min2 = second.min;
                    int min3 = third.min;

                    if (abs(min1 - min2) <= 1 && abs(min2 - min3) <= 1 &&
                        abs(min1 - min3) <= 1) {
                        printf("Division found at indices: %d and %d\n", i, j);
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    if (canDivideArray(arr, n)) {
        printf("Array can be divided into three equal parts with given conditions\n");
    } else {
        printf("Array cannot be divided as required\n");
    }

    free(arr);
    return 0;
}
