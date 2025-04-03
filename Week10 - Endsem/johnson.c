/*
 * Problem 4: Johnson's Algorithm
 *
 * Description: Implement Johnson's algorithm for finding all-pairs shortest paths in a sparse graph.
 * Johnson's algorithm uses Dijkstra's and Bellman-Ford as subroutines and is more efficient than
 * Floyd-Warshall for sparse graphs. It can handle negative edge weights but not negative cycles.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// A structure to represent an edge in the graph
struct Edge
{
    int src, dest, weight;
};

// A structure to represent a weighted edge in the graph (for adjacency list)
struct AdjListNode
{
    int dest, weight;
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
    int V, E;
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
    graph->E = 0;

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
    graph->E++;
}

// Min Heap node structure for Dijkstra's algorithm
struct MinHeapNode
{
    int v;
    int dist;
};

// Min Heap structure
struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    struct MinHeapNode **array;
};

// Function to create a new Min Heap Node
struct MinHeapNode *newMinHeapNode(int v, int dist)
{
    struct MinHeapNode *minHeapNode = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// Function to create a Min Heap
struct MinHeap *createMinHeap(int capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode **)malloc(capacity * sizeof(struct MinHeapNode *));
    return minHeap;
}

// Function to swap two nodes of a min heap
void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b)
{
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

// Min heapify function
void minHeapify(struct MinHeap *minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
    {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
    {
        smallest = right;
    }

    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// Function to check if the given heap is empty
int isEmpty(struct MinHeap *minHeap)
{
    return minHeap->size == 0;
}

// Function to extract minimum node from heap
struct MinHeapNode *extractMin(struct MinHeap *minHeap)
{
    if (isEmpty(minHeap))
    {
        return NULL;
    }

    // Store the root node
    struct MinHeapNode *root = minHeap->array[0];

    // Replace root node with last node
    struct MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update position of last node
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Function to decrease dist value of a given vertex v
void decreaseKey(struct MinHeap *minHeap, int v, int dist)
{
    // Get the index of v in heap array
    int i = minHeap->pos[v];

    // Update distance value
    minHeap->array[i]->dist = dist;

    // Heapify up until the node reaches its correct position
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap with parent
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        // Move to parent index
        i = (i - 1) / 2;
    }
}

// Function to check if a given vertex 'v' is in min heap
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
    {
        return true;
    }
    return false;
}

// Function to run Dijkstra's algorithm from a source vertex
int *dijkstra(struct Graph *graph, int src)
{
    int V = graph->V;
    int *dist = (int *)malloc(V * sizeof(int));

    // Create a min heap
    struct MinHeap *minHeap = createMinHeap(V);

    // Initialize min heap with all vertices
    for (int v = 0; v < V; v++)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    // Make dist value of src vertex as 0
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    // Initially size of min heap is equal to V
    minHeap->size = V;

    // In this loop, min heap contains all nodes whose shortest distance is not yet finalized
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with minimum distance value
        struct MinHeapNode *minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        // Traverse through all adjacent vertices of u and update their distance values
        struct AdjListNode *pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;

            // If shortest distance to v is not finalized yet, and if the current distance
            // to v through u is less than its previously calculated distance
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;

                // Update distance value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }

        free(minHeapNode);
    }

    // Free the min heap
    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);

    return dist;
}

// Function to run Bellman-Ford algorithm from a source vertex
int *bellmanFord(struct Edge *edges, int E, int V, int src)
{
    int *dist = (int *)malloc(V * sizeof(int));

    // Step 1: Initialize distances from src to all other vertices as INFINITE
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
            return NULL; // If negative cycle is detected, return NULL
        }
    }

    return dist;
}

// Function to print the solution matrix
void printSolution(int **dist, int V)
{
    printf("Following matrix shows the shortest distances between every pair of vertices:\n");
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

// Function to implement Johnson's algorithm for all-pairs shortest paths
void johnson(struct Graph *graph)
{
    int V = graph->V;
    int E = graph->E;

    // Step 1: Add a new vertex s, and add edges from s to all other vertices with weight 0
    // We create a new graph with V+1 vertices and E+V edges
    struct Graph *augmentedGraph = createGraph(V + 1);
    for (int v = 0; v < V; v++)
    {
        // Add edge from new vertex to all existing vertices
        addEdge(augmentedGraph, V, v, 0);

        // Add all original edges to the augmented graph
        struct AdjListNode *pCrawl = graph->array[v].head;
        while (pCrawl != NULL)
        {
            addEdge(augmentedGraph, v, pCrawl->dest, pCrawl->weight);
            pCrawl = pCrawl->next;
        }
    }

    // Step 2: Run Bellman-Ford from the new vertex s to get h values
    // First, convert the adjacency list to edge list
    struct Edge *edges = (struct Edge *)malloc(augmentedGraph->E * sizeof(struct Edge));
    int edgeIndex = 0;
    for (int v = 0; v <= V; v++)
    {
        struct AdjListNode *pCrawl = augmentedGraph->array[v].head;
        while (pCrawl != NULL)
        {
            edges[edgeIndex].src = v;
            edges[edgeIndex].dest = pCrawl->dest;
            edges[edgeIndex].weight = pCrawl->weight;
            edgeIndex++;
            pCrawl = pCrawl->next;
        }
    }

    int *h = bellmanFord(edges, augmentedGraph->E, V + 1, V);
    if (h == NULL)
    {
        free(edges);
        // Clean up augmented graph
        for (int i = 0; i <= V; i++)
        {
            struct AdjListNode *current = augmentedGraph->array[i].head;
            while (current)
            {
                struct AdjListNode *temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(augmentedGraph->array);
        free(augmentedGraph);
        return; // Negative cycle exists, return
    }

    // Step 3: Reweight the edges of the original graph
    struct Graph *reweightedGraph = createGraph(V);
    for (int v = 0; v < V; v++)
    {
        struct AdjListNode *pCrawl = graph->array[v].head;
        while (pCrawl != NULL)
        {
            int newWeight = pCrawl->weight + h[v] - h[pCrawl->dest];
            addEdge(reweightedGraph, v, pCrawl->dest, newWeight);
            pCrawl = pCrawl->next;
        }
    }

    // Step 4: Run Dijkstra for each vertex as source
    int **dist = (int **)malloc(V * sizeof(int *));
    for (int src = 0; src < V; src++)
    {
        dist[src] = dijkstra(reweightedGraph, src);

        // Correct the distances (undo the reweighting)
        for (int v = 0; v < V; v++)
        {
            if (dist[src][v] != INT_MAX)
            {
                dist[src][v] = dist[src][v] - h[src] + h[v];
            }
        }
    }

    // Print the final result
    printSolution(dist, V);

    // Free allocated memory
    free(edges);
    free(h);
    for (int i = 0; i < V; i++)
    {
        free(dist[i]);

        // Clean up reweighted graph
        struct AdjListNode *current = reweightedGraph->array[i].head;
        while (current)
        {
            struct AdjListNode *temp = current;
            current = current->next;
            free(temp);
        }

        // Clean up augmented graph
        if (i < V)
        {
            current = augmentedGraph->array[i].head;
            while (current)
            {
                struct AdjListNode *temp = current;
                current = current->next;
                free(temp);
            }
        }
    }

    // Clean up the last vertex in augmented graph
    struct AdjListNode *current = augmentedGraph->array[V].head;
    while (current)
    {
        struct AdjListNode *temp = current;
        current = current->next;
        free(temp);
    }

    free(dist);
    free(reweightedGraph->array);
    free(reweightedGraph);
    free(augmentedGraph->array);
    free(augmentedGraph);
}

int main()
{
    int V, E;

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

    johnson(graph);

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
