/*
 * Problem 2: Bellman-Ford Algorithm
 *
 * Description: Implement the Bellman-Ford algorithm to find the shortest paths from a source vertex
 * to all other vertices in a weighted graph. Unlike Dijkstra's algorithm, Bellman-Ford works
 * for graphs with negative weight edges and can detect negative weight cycles.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// A structure to represent an edge in the graph
struct Edge
{
    int src, dest, weight;
};

// Function to print the solution
void printBellmanFordSolution(int dist[], int V, int src)
{
    printf("Vertex \t Distance from Source %d\n", src);
    for (int i = 0; i < V; i++)
    {
        printf("%d \t %d\n", i, dist[i]);
    }
}

// The main function that finds shortest distances from src to all other vertices using Bellman-Ford algorithm
void bellmanFord(struct Edge *edges, int E, int V, int src)
{
    // Step 1: Initialize distances from src to all other vertices as INFINITE
    int *dist = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times
    for (int i = 1; i < V; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int i = 0; i < E; i++)
    {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
        {
            printf("Graph contains negative weight cycle\n");
            free(dist);
            return; // If negative cycle is detected, simply return
        }
    }

    // Print the solution
    printBellmanFordSolution(dist, V, src);

    // Free allocated memory
    free(dist);
}

int main()
{
    int V, E, src;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    struct Edge *edges = (struct Edge *)malloc(E * sizeof(struct Edge));

    printf("Enter the edges (src dest weight):\n");
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    printf("Enter the source vertex: ");
    scanf("%d", &src);

    bellmanFord(edges, E, V, src);

    // Free allocated memory
    free(edges);

    return 0;
}
