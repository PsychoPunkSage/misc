#include <stdio.h>
#include <stdbool.h>

bool isSubsetSum(int arr[], int n, int sum, int* subset, int subsetSize) {
    if (sum == 0) {
        printf("Subset found: ");
        for(int i = 0; i < subsetSize; i++)
            printf("%d ", subset[i]);
        printf("\n");
        return true;
    }
    if (n == 0)
        return false;
        
    subset[subsetSize] = arr[n-1];
    return isSubsetSum(arr, n-1, sum - arr[n-1], subset, subsetSize + 1) || 
           isSubsetSum(arr, n-1, sum, subset, subsetSize);
}

int main() {
    int n, sum;
    printf("Enter size of array: ");
    scanf("%d", &n);
    
    int arr[n], subset[n];
    printf("Enter array elements: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
        
    printf("Enter target sum: ");
    scanf("%d", &sum);
    
    if (!isSubsetSum(arr, n, sum, subset, 0))
        printf("No subset with given sum exists\n");
    
    return 0;
}

// Time Complexity Recursion: T(n) = 2×T(n-1) + c
// Solves to: O(2^n)
