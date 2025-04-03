/*
 * Problem 5: Single-Source Shortest Path in Directed Acyclic Graph (DAG)
 *
 * Description: Implement a topological sort based algorithm to find shortest paths from a single source
 * to all other vertices in a Directed Acyclic Graph (DAG). This approach is more efficient than
 * Dijkstra's algorithm for DAGs as it runs in O(V+E) time.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode *next;
};

// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;
};

// A structure to represent a graph
struct Graph
{
    int V;
    struct AdjList *array;
};

// Function to create a new adjacency list node
struct AdjListNode *newAdjListNode(int dest, int weight)
{
    struct AdjListNode *newNode = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists
    graph->array = (struct AdjList *)malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty
    for (int i = 0; i < V; i++)
    {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph *graph, int src, int dest, int weight)
{
    // Add an edge from src to dest
    struct AdjListNode *newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// A utility function to do DFS starting from vertex v
void topologicalSortUtil(struct Graph *graph, int v, bool visited[], int stack[], int *stackIndex)
{
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all adjacent vertices
    struct AdjListNode *pCrawl = graph->array[v].head;
    while (pCrawl != NULL)
    {
        if (!visited[pCrawl->dest])
        {
            topologicalSortUtil(graph, pCrawl->dest, visited, stack, stackIndex);
        }
        pCrawl = pCrawl->next;
    }

    // Push current vertex to stack which stores the topological sort
    stack[(*stackIndex)++] = v;
}

// The function to find shortest paths from given source vertex
void shortestPath(struct Graph *graph, int src)
{
    int V = graph->V;
    // Create a stack to store topological sort
    int *stack = (int *)malloc(V * sizeof(int));
    int stackIndex = 0;

    // Mark all the vertices as not visited
    bool *visited = (bool *)malloc(V * sizeof(bool));
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }

    // Call the recursive helper function to store Topological Sort
    // starting from all vertices one by one
    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            topologicalSortUtil(graph, i, visited, stack, &stackIndex);
        }
    }

    // Initialize distances to all vertices as infinite and
    // distance to source as 0
    int *dist = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    // Process vertices in topological order
    while (stackIndex > 0)
    {
        // Get the next vertex from topological order
        int u = stack[--stackIndex];

        // Update distances of all adjacent vertices
        if (dist[u] != INT_MAX)
        {
            struct AdjListNode *pCrawl = graph->array[u].head;
            while (pCrawl != NULL)
            {
                if (dist[u] + pCrawl->weight < dist[pCrawl->dest])
                {
                    dist[pCrawl->dest] = dist[u] + pCrawl->weight;
                }
                pCrawl = pCrawl->next;
            }
        }
    }

    // Print the calculated shortest distances
    printf("Vertex \t Distance from Source %d\n", src);
    for (int i = 0; i < V; i++)
    {
        if (dist[i] == INT_MAX)
        {
            printf("%d \t INF\n", i);
        }
        else
        {
            printf("%d \t %d\n", i, dist[i]);
        }
    }

    // Free allocated memory
    free(stack);
    free(visited);
    free(dist);
}

int main()
{
    int V, E, src;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    // Create a graph
    struct Graph *graph = createGraph(V);

    printf("Enter the edges (src dest weight):\n");
    for (int i = 0; i < E; i++)
    {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    printf("Enter the source vertex: ");
    scanf("%d", &src);

    // Find shortest paths from source
    shortestPath(graph, src);

    // Free allocated memory
    for (int i = 0; i < V; i++)
    {
        struct AdjListNode *current = graph->array[i].head;
        while (current)
        {
            struct AdjListNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);

    return 0;
}