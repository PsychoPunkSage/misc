/*
Given n points in a 2D plane where each point has a color (represented by an integer), find the closest pair of points that have different colors. Use divide and conquer approach with O(n log n) complexity.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct {
    double x, y;
    int color;
} Point;

// Compare function for qsort - sort by x coordinate
int compareX(const void* a, const void* b) {
    return ((Point*)a)->x - ((Point*)b)->x;
}

// Compare function for qsort - sort by y coordinate
int compareY(const void* a, const void* b) {
    return ((Point*)a)->y - ((Point*)b)->y;
}

// Calculate distance between two points
double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

// Find minimum distance among strip points
double stripClosest(Point strip[], int size, double d) {
    double min = d;

    // Sort by y coordinate
    qsort(strip, size, sizeof(Point), compareY);

    // Compare points in strip
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; j++) {
            if (strip[i].color != strip[j].color) {
                double dist_ij = dist(strip[i], strip[j]);
                if (dist_ij < min) {
                    min = dist_ij;
                }
            }
        }
    }
    return min;
}

// Recursive function to find closest pair
double closestUtil(Point points[], int n) {
    if (n <= 3) {
        double min = DBL_MAX;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (points[i].color != points[j].color) {
                    double dist_ij = dist(points[i], points[j]);
                    if (dist_ij < min) {
                        min = dist_ij;
                    }
                }
            }
        }
        return min;
    }

    int mid = n/2;
    Point midPoint = points[mid];

    double dl = closestUtil(points, mid);
    double dr = closestUtil(points + mid, n - mid);

    double d = dl < dr ? dl : dr;

    Point* strip = (Point*)malloc(n * sizeof(Point));
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (abs(points[i].x - midPoint.x) < d) {
            strip[j] = points[i];
            j++;
        }
    }

    double min = stripClosest(strip, j, d);
    free(strip);

    return min < d ? min : d;
}

// Main function to find closest pair
double closestPair(Point points[], int n) {
    qsort(points, n, sizeof(Point), compareX);
    return closestUtil(points, n);
}

int main() {
    int n;
    printf("Enter number of points: ");
    scanf("%d", &n);

    Point* points = (Point*)malloc(n * sizeof(Point));
    printf("Enter points (x y color):\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %d", &points[i].x, &points[i].y, &points[i].color);
    }

    double minDist = closestPair(points, n);
    printf("Minimum distance between points of different colors: %lf\n", minDist);

    free(points);
    return 0;
}
