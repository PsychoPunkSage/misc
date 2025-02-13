#include <stdio.h>
#include <stdlib.h>

#define BASE 10  // Decimal base for radix sort

// Function to get the maximum value in an array
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Counting Sort used as a subroutine in Radix Sort
void countingSort(int arr[], int n, int exp) {
    int *output = (int *)malloc(n * sizeof(int));  // Output array
    int count[BASE] = {0};  // Count array initialized to zero

    // Count occurrences of each digit at current place value
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % BASE]++;
    }

    // Update count[i] to store actual position of the digit
    for (int i = 1; i < BASE; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array by placing elements in sorted order
    for (int i = n - 1; i >= 0; i--) {
        int index = (arr[i] / exp) % BASE;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }

    // Copy the sorted values back to the original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);  // Free allocated memory
}

// Main function for Radix Sort
void radixSort(int arr[], int n) {
    int max = getMax(arr, n);  // Find the maximum number

    // Apply counting sort for each digit (place value: 1, 10, 100, ...)
    for (int exp = 1; max / exp > 0; exp *= BASE) {
        countingSort(arr, n, exp);
    }
}

int main() {
    int n;

    // Input array size
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));  // Dynamic allocation

    // Input array elements
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sorting the array using Radix Sort
    radixSort(arr, n);

    // Output sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);  // Free allocated memory
    return 0;
}

