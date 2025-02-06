/*
Problem: Closest Pair of Points
Description: Given n points in a 2D plane, find the pair of points with the 
smallest Euclidean distance between them using divide and conquer.
Time Complexity: O(n log n)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

struct Point {
    int x, y;
};

// Compare function for qsort
int compareX(const void* a, const void* b) {
    return ((struct Point*)a)->x - ((struct Point*)b)->x;
}

int compareY(const void* a, const void* b) {
    return ((struct Point*)a)->y - ((struct Point*)b)->y;
}

float dist(struct Point p1, struct Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + 
                (p1.y - p2.y) * (p1.y - p2.y));
}

float bruteForce(struct Point P[], int n, struct Point* p1, struct Point* p2) {
    float min = FLT_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            float distance = dist(P[i], P[j]);
            if (distance < min) {
                min = distance;
                *p1 = P[i];
                *p2 = P[j];
            }
        }
    }
    return min;
}

float stripClosest(struct Point strip[], int size, float d, 
                   struct Point* p1, struct Point* p2) {
    float min = d;
    qsort(strip, size, sizeof(struct Point), compareY);

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
            float distance = dist(strip[i], strip[j]);
            if (distance < min) {
                min = distance;
                *p1 = strip[i];
                *p2 = strip[j];
            }
        }
    }
    return min;
}

float closestUtil(struct Point P[], int n, struct Point* p1, struct Point* p2) {
    if (n <= 3) 
        return bruteForce(P, n, p1, p2);

    int mid = n/2;
    struct Point midPoint = P[mid];

    float dl = closestUtil(P, mid, p1, p2);
    struct Point p3, p4;
    float dr = closestUtil(P + mid, n - mid, &p3, &p4);

    float d = dl;
    if (dr < d) {
        d = dr;
        *p1 = p3;
        *p2 = p4;
    }

    struct Point* strip = (struct Point*)malloc(n * sizeof(struct Point));
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (abs(P[i].x - midPoint.x) < d) {
            strip[j] = P[i];
            j++;
        }
    }

    float min = stripClosest(strip, j, d, p1, p2);
    free(strip);
    return min;
}

float closest(struct Point P[], int n, struct Point* p1, struct Point* p2) {
    qsort(P, n, sizeof(struct Point), compareX);
    return closestUtil(P, n, p1, p2);
}

int main() {
    int n;
    printf("Enter number of points: ");
    scanf("%d", &n);

    struct Point* P = (struct Point*)malloc(n * sizeof(struct Point));
    printf("Enter %d points (x y format):\n", n);
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &P[i].x, &P[i].y);
    }

    struct Point p1, p2;
    float min_dist = closest(P, n, &p1, &p2);

    printf("The closest distance is %f\n", min_dist);
    printf("Between points (%d,%d) and (%d,%d)\n", 
           p1.x, p1.y, p2.x, p2.y);

    free(P);
    return 0;
}
