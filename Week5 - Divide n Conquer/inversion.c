/*
Problem: Count Inversions
Description: Count the number of inversions in an array. An inversion occurs when 
i < j but arr[i] > arr[j]. This is useful in analyzing how far an array is from 
being sorted.
Time Complexity: O(n log n)
*/

#include <stdio.h>

long long mergeAndCount(int arr[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    long long invCount = 0;
    int temp[right - left + 1];
    
    while(i <= mid && j <= right) {
        if(arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            invCount += (mid - i + 1); // Count inversions
        }
    }
    
    // Copy remaining elements
    while(i <= mid)
        temp[k++] = arr[i++];
        
    while(j <= right)
        temp[k++] = arr[j++];
        
    // Copy back to original array
    for(i = left, k = 0; i <= right; i++, k++)
        arr[i] = temp[k];
        
    return invCount;
}

long long countInversions(int arr[], int left, int right) {
    long long invCount = 0;
    if(left < right) {
        int mid = (left + right) / 2;
        
        invCount += countInversions(arr, left, mid);
        invCount += countInversions(arr, mid + 1, right);
        invCount += mergeAndCount(arr, left, mid, right);
    }
    return invCount;
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
    
    long long inversions = countInversions(arr, 0, n-1);
    printf("Number of inversions: %lld\n", inversions);
    
    return 0;
}
