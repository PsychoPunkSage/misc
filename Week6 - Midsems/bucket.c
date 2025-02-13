#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 10  // Number of buckets

// Structure for a bucket (dynamic array)
typedef struct {
    float *values;
    int count;
} Bucket;

// Function to insert an element into a bucket
void insertToBucket(Bucket *bucket, float value) {
    bucket->values[bucket->count++] = value;
}

// Simple insertion sort to sort individual buckets
void insertionSort(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Bucket Sort function
void bucketSort(float arr[], int n) {
    // Step 1: Create buckets
    Bucket *buckets = (Bucket *)malloc(BUCKET_SIZE * sizeof(Bucket));
    for (int i = 0; i < BUCKET_SIZE; i++) {
        buckets[i].values = (float *)malloc(n * sizeof(float));
        buckets[i].count = 0;
    }

    // Step 2: Distribute elements into buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = (int)(arr[i] * BUCKET_SIZE); // Scaling factor
        insertToBucket(&buckets[bucketIndex], arr[i]);
    }

    // Step 3: Sort each bucket and merge results
    int index = 0;
    for (int i = 0; i < BUCKET_SIZE; i++) {
        if (buckets[i].count > 0) {
            insertionSort(buckets[i].values, buckets[i].count);
            for (int j = 0; j < buckets[i].count; j++) {
                arr[index++] = buckets[i].values[j];
            }
        }
        free(buckets[i].values); // Free bucket memory
    }

    free(buckets); // Free bucket array
}

int main() {
    int n;

    // Input array size
    printf("Enter number of elements: ");
    scanf("%d", &n);

    float *arr = (float *)malloc(n * sizeof(float)); // Dynamic allocation

    // Input array elements
    printf("Enter %d floating-point numbers (between 0 and 1): ", n);
    for (int i = 0; i < n; i++) {
        scanf("%f", &arr[i]);
    }

    // Sorting the array using Bucket Sort
    bucketSort(arr, n);

    // Output sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%0.2f ", arr[i]);
    }
    printf("\n");

    free(arr); // Free allocated memory
    return 0;
}

