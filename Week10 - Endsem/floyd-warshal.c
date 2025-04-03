/*
 * Problem 3: Floyd-Warshall Algorithm
 *
 * Description: Implement the Floyd-Warshall algorithm to find the shortest paths between all pairs
 * of vertices in a weighted graph. This algorithm works for graphs with positive or negative
 * edge weights (but no negative cycles) and is a good choice when we need all-pairs shortest paths.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to print the solution
void printFloydWarshallSolution(int **dist, int V)
{
    printf("The following matrix shows the shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INT_MAX)
            {
                printf("INF\t");
            }
            else
            {
                printf("%d\t", dist[i][j]);
            }
        }
        printf("\n");
    }
}

// Floyd-Warshall algorithm to find all-pairs shortest paths
void floydWarshall(int **graph, int V)
{
    // Create dist[][] matrix with same values as input graph
    int **dist = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
    {
        dist[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++)
        {
            dist[i][j] = graph[i][j];
        }
    }

    // Add all vertices one by one to the set of intermediate vertices
    for (int k = 0; k < V; k++)
    {
        // Pick all vertices as source one by one
        for (int i = 0; i < V; i++)
        {
            // Pick all vertices as destination for the above source
            for (int j = 0; j < V; j++)
            {
                // If vertex k is on the shortest path from i to j, update dist[i][j]
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Check for negative cycles
    for (int i = 0; i < V; i++)
    {
        if (dist[i][i] < 0)
        {
            printf("Graph contains negative cycle\n");

            // Free allocated memory
            for (int j = 0; j < V; j++)
            {
                free(dist[j]);
            }
            free(dist);

            return;
        }
    }

    // Print the shortest distance matrix
    printFloydWarshallSolution(dist, V);

    // Free allocated memory
    for (int i = 0; i < V; i++)
    {
        free(dist[i]);
    }
    free(dist);
}

int main()
{
    int V;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    // Dynamically allocate memory for the graph
    int **graph = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
    {
        graph[i] = (int *)malloc(V * sizeof(int));
    }

    printf("Enter the adjacency matrix (use -1 for infinity, 0 for self-loops):\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            int value;
            scanf("%d", &value);
            if (value == -1)
            {
                graph[i][j] = INT_MAX;
            }
            else
            {
                graph[i][j] = value;
            }
        }
    }

    floydWarshall(graph, V);

    // Free allocated memory
    for (int i = 0; i < V; i++)
    {
        free(graph[i]);
    }
    free(graph);

    return 0;
}