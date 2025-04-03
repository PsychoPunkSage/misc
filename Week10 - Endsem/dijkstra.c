/*
 * Problem 1: Dijkstra's Algorithm
 *
 * Description: Implement Dijkstra's algorithm to find the shortest path from a source vertex
 * to all other vertices in a weighted graph. The graph is represented as an adjacency matrix.
 * The algorithm works for graphs with non-negative edge weights.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Function to find the vertex with minimum distance value
int minDistance(int dist[], bool sptSet[], int V)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
    {
        if (sptSet[v] == false && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the solution
void printSolution(int dist[], int V, int src)
{
    printf("Vertex \t Distance from Source %d\n", src);
    for (int i = 0; i < V; i++)
    {
        printf("%d \t %d\n", i, dist[i]);
    }
}

// Function that implements Dijkstra's algorithm
void dijkstra(int **graph, int src, int V)
{
    int *dist = (int *)malloc(V * sizeof(int));
    bool *sptSet = (bool *)malloc(V * sizeof(bool));

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet, V);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++)
        {
            // Update dist[v] only if is not in sptSet, there is an edge from u to v,
            // and total weight of path from src to v through u is smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the constructed distance array
    printSolution(dist, V, src);

    // Free allocated memory
    free(dist);
    free(sptSet);
}

int main()
{
    int V, src;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    // Dynamically allocate memory for the graph
    int **graph = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
    {
        graph[i] = (int *)malloc(V * sizeof(int));
    }

    printf("Enter the adjacency matrix (use 0 for no edge):\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, src, V);

    // Free allocated memory
    for (int i = 0; i < V; i++)
    {
        free(graph[i]);
    }
    free(graph);

    return 0;
}