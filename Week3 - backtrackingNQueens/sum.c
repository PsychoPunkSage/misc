#include <stdio.h>
#include <stdbool.h>

#define MAX 100

void printSubset(int A[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void subsetSum(int set[], int subset[], int n, int subsize, int sum, int target, int index) {
    if (sum == target) {
        printSubset(subset, subsize);
        return;
    }
    
    if (sum > target || index >= n)
        return;
        
    subset[subsize] = set[index];
    subsetSum(set, subset, n, subsize + 1, sum + set[index], target, index + 1);
    subsetSum(set, subset, n, subsize, sum, target, index + 1);
}

int main() {
    int set[] = {10, 7, 5, 18, 12, 20, 15};
    int n = sizeof(set)/sizeof(set[0]);
    int subset[MAX];
    int target = 35;
    
    subsetSum(set, subset, n, 0, 0, target, 0);
    return 0;
}
