#include <stdio.h>

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;        // Pointers to traverse arrays
    int n1 = m - l + 1; // Size of the left subarray
    int n2 = r - m;     // Size of the right subarray

    // Create temporary arrays to store left and right subarrays
    int L[n1], R[n2];

    // Copy elements from arr[l...m] to L[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];

    // Copy elements from arr[m+1...r] to R[]
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Initialize indices for L[], R[], and arr[]
    i = 0; // Initial index of left subarray (L)
    j = 0; // Initial index of right subarray (R)
    k = l; // Initial index of the merged array (arr)

    // Merge elements from L[] and R[] back into arr[]
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements in L[] to arr[]
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy any remaining elements in R[] to arr[]
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Recursive merge sort function
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Find the middle point
        int m = l + (r - l) / 2;

        // Sort the left and right halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

int main()
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d non-negative elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Call merge sort on the entire array
    mergeSort(arr, 0, n - 1);

    // Print the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
