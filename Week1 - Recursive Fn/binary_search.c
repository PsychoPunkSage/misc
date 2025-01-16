#include <stdio.h>

int bst(int arr[], int left, int right, int n)
{
    if (left > right)
    {
        return -1;
    }

    int mid = (left + right) / 2;

    if (arr[mid] == n)
    {
        return mid;
    }

    if (arr[mid] > n)
    {
        return bst(arr, left, mid - 1, n);
    }
    else
    {
        return bst(arr, mid + 1, right, n);
    }
}

int bstfindFirstOccurrence(int arr[], int left, int right, int n)
{
    if (left > right)
    {
        return -1;
    }

    int mid = (left + right) / 2;

    if (arr[mid] == n)
    {
        if (mid == 0 || arr[mid - 1] != n)
        {
            return mid;
        }

        return bstfindFirstOccurrence(arr, left, mid - 1, n);
    }

    if (arr[mid] > n)
    {
        return bstfindFirstOccurrence(arr, left, mid - 1, n);
    }
    else
    {
        return bstfindFirstOccurrence(arr, mid + 1, right, n);
    }
}

int bstLastOccurrence(int arr[], int left, int right, int n)
{
    if (left > right)
    {
        return -1;
    }

    int mid = (left + right) / 2;

    if (arr[mid] == n)
    {
        if (mid == right || arr[mid + 1] != n)
        {
            return mid;
        }

        return bstLastOccurrence(arr, mid + 1, right, n);
    }

    if (arr[mid] > n)
    {
        return bstLastOccurrence(arr, left, mid - 1, n);
    }
    else
    {
        return bstLastOccurrence(arr, mid + 1, right, n);
    }
}

int bstFloorVal(int arr[], int left, int right, int n)
{
    // largest element smaller than or equal to target
    if (left > right)
    {
        return -1;
    }

    int mid = (left + right) / 2;

    if (arr[mid] == n)
    {
        return mid;
    }

    if (arr[mid] > n)
    {
        return bstFloorVal(arr, left, mid - 1, n);
    }
    else
    {
        int possibleFloor = bstFloorVal(arr, mid + 1, right, n);
        return (possibleFloor == -1) ? mid : possibleFloor;
    }
}

int main()
{
    int arr[] = {2, 5, 5, 5, 8, 8, 12, 16, 23, 38, 56, 56, 56, 56, 72, 91};
    // int size = 10;
    int target = 57;

    int res = bst(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1, target);

    printf("NO(%d) -> (%d)\n", target, res);
    printf("FO(%d) -> (%d)\n", target, bstfindFirstOccurrence(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1, target));
    printf("LO(%d) -> (%d)\n", target, bstLastOccurrence(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1, target));
    printf("FLOOR(%d) -> (%d)\n", target, bstFloorVal(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1, target));
    return 0;
}