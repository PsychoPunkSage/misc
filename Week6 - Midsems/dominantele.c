/*
Dominant Element Finding
Given an array of n integers, find all elements that appear more than n/3 times in the array using divide and conquer approach. The algorithm should run in O(n log n) time.
*/

#include <stdio.h>
#include <stdlib.h>

// Structure to store element and its count
typedef struct {
    int element;
    int count;
} ElementCount;

// Merge two sorted arrays of ElementCount
ElementCount* merge(ElementCount* left, int leftSize, ElementCount* right, int rightSize) {
    ElementCount* result = (ElementCount*)malloc((leftSize + rightSize) * sizeof(ElementCount));
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if (left[i].element <= right[j].element) {
            if (k > 0 && result[k-1].element == left[i].element) {
                result[k-1].count += left[i].count;
            } else {
                result[k] = left[i];
                k++;
            }
            i++;
        } else {
            if (k > 0 && result[k-1].element == right[j].element) {
                result[k-1].count += right[j].count;
            } else {
                result[k] = right[j];
                k++;
            }
            j++;
        }
    }

    while (i < leftSize) {
        if (k > 0 && result[k-1].element == left[i].element) {
            result[k-1].count += left[i].count;
        } else {
            result[k] = left[i];
            k++;
        }
        i++;
    }

    while (j < rightSize) {
        if (k > 0 && result[k-1].element == right[j].element) {
            result[k-1].count += right[j].count;
        } else {
            result[k] = right[j];
            k++;
        }
        j++;
    }

    return result;
}

// Find dominant elements using divide and conquer
ElementCount* findDominantElements(int arr[], int start, int end, int* resultSize) {
    if (start == end) {
        ElementCount* result = (ElementCount*)malloc(sizeof(ElementCount));
        result[0].element = arr[start];
        result[0].count = 1;
        *resultSize = 1;
        return result;
    }

    int mid = (start + end) / 2;
    int leftSize, rightSize;

    ElementCount* left = findDominantElements(arr, start, mid, &leftSize);
    ElementCount* right = findDominantElements(arr, mid + 1, end, &rightSize);

    ElementCount* merged = merge(left, leftSize, right, rightSize);
    free(left);
    free(right);

    *resultSize = leftSize + rightSize;
    return merged;
}

int main() {
    int n;
    printf("Enter the size of array: ");
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int resultSize;
    ElementCount* result = findDominantElements(arr, 0, n-1, &resultSize);

    printf("\nElements appearing more than %d times:\n", n/3);
    for (int i = 0; i < resultSize; i++) {
        if (result[i].count > n/3) {
            printf("%d (count: %d)\n", result[i].element, result[i].count);
        }
    }

    free(result);
    free(arr);
    return 0;
}
