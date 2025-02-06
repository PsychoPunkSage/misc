/*
Problem: Maximum Subarray Sum with Subarray Elements
Description: Find the contiguous subarray within a one-dimensional array 
that has the largest sum, and print both the sum and the subarray elements.
Time Complexity: O(n log n)
*/

#include <stdio.h>

// Structure to store both sum and subarray bounds
struct Result {
    int sum;
    int start;
    int end;
};

// Function to find maximum of two numbers
int max(int a, int b) { 
    return (a > b) ? a : b; 
}

// Function to find maximum crossing sum and track subarray bounds
struct Result maxCrossingSum(int arr[], int left, int mid, int right) {
    struct Result result = {0, 0, 0};
    int sum = 0;
    int left_sum = -1000000;  // Using a very small number as minimum
    int left_index = mid;
    
    // Find maximum sum for left subarray
    for(int i = mid; i >= left; i--) {
        sum += arr[i];
        if(sum > left_sum) {
            left_sum = sum;
            left_index = i;
        }
    }
    
    sum = 0;
    int right_sum = -1000000;
    int right_index = mid + 1;
    
    // Find maximum sum for right subarray
    for(int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if(sum > right_sum) {
            right_sum = sum;
            right_index = i;
        }
    }
    
    // Combine the results
    result.sum = left_sum + right_sum;
    result.start = left_index;
    result.end = right_index;
    return result;
}

struct Result maxSubArraySum(int arr[], int left, int right) {
    // Base case: single element
    if(left == right) {
        struct Result result = {arr[left], left, left};
        return result;
    }
    
    int mid = (left + right) / 2;
    
    // Get results from left and right subarrays
    struct Result left_result = maxSubArraySum(arr, left, mid);
    struct Result right_result = maxSubArraySum(arr, mid + 1, right);
    struct Result cross_result = maxCrossingSum(arr, left, mid, right);
    
    // Return the maximum of the three possible results
    if(left_result.sum >= right_result.sum && left_result.sum >= cross_result.sum)
        return left_result;
    else if(right_result.sum >= left_result.sum && right_result.sum >= cross_result.sum)
        return right_result;
    else
        return cross_result;
}

int main() {
    int n;
    
    printf("Enter the size of array: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter %d numbers: ", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    struct Result result = maxSubArraySum(arr, 0, n-1);
    
    printf("Maximum contiguous sum is %d\n", result.sum);
    printf("Subarray is: ");
    for(int i = result.start; i <= result.end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    printf("Starting index: %d\n", result.start);
    printf("Ending index: %d\n", result.end);
    
    return 0;
}
