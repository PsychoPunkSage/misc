/*
Problem: Find Peak Element
Description: Find an element that is greater than its neighbors
Time Complexity: O(log n)
*/

#include <stdio.h>

int findPeak(int arr[], int left, int right) {
    // Find mid point
    int mid = left + (right - left) / 2;
    
    // Check if mid element is peak
    if ((mid == 0 || arr[mid] >= arr[mid-1]) && 
        (mid == right || arr[mid] >= arr[mid+1])) {
        return mid;
    }
    
    // If left neighbor is greater, peak lies in left half
    if (mid > 0 && arr[mid-1] > arr[mid]) {
        return findPeak(arr, left, mid-1);
    }
    
    // If right neighbor is greater, peak lies in right half
    return findPeak(arr, mid+1, right);
}

int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter %d numbers: ", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int peakIndex = findPeak(arr, 0, n-1);
    printf("A peak element is %d at index %d\n", arr[peakIndex], peakIndex);
    
    return 0;
}
