/**
*student name [meseud hadis redi]
 *student id[2210205530]
 * Time Complexity:
 *   - DFS: O(V + E) for adjacency list, O(V²) for adjacency matrix
 *   - BFS: O(V + E) for adjacency list, O(V²) for adjacency matrix
 * Space Complexity: O(V) for visited array and queue/stack
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

// Graph structure using adjacency matrix
typedef struct {
    int vertices;
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];
    bool is_directed;
} Graph;

// Stack structure for DFS (iterative)
typedef struct {
    int data[MAX_VERTICES];
    int top;
} Stack;

// Queue structure for BFS
typedef struct {
    int data[MAX_VERTICES];
    int front;
    int rear;
    int size;
} Queue;

/**
 * Create a new graph
 */
Graph* create_graph(int vertices, bool is_directed) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    
    graph->vertices = vertices;
    graph->is_directed = is_directed;
    
    // Initialize adjacency matrix with zeros
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adj_matrix[i][j] = 0;
        }
    }
    
    return graph;
}

/**
 * Add edge to graph
 */
void add_edge(Graph* graph, int src, int dest, int weight) {
    if (!graph || src < 0 || src >= graph->vertices || dest < 0 || dest >= graph->vertices) {
        printf("Error: Invalid vertices\n");
        return;
    }
    
    graph->adj_matrix[src][dest] = weight;
    if (!graph->is_directed) {
        graph->adj_matrix[dest][src] = weight;
    }
}

/**
 * Print adjacency matrix
 */
void print_graph(Graph* graph) {
    if (!graph) {
        printf("Graph is NULL\n");
        return;
    }
    
    printf("Graph (%d vertices, %s):\n", 
           graph->vertices, 
           graph->is_directed ? "directed" : "undirected");
    
    printf("    ");
    for (int i = 0; i < graph->vertices; i++) {
        printf("%3d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < graph->vertices; i++) {
        printf("%3d ", i);
        for (int j = 0; j < graph->vertices; j++) {
            printf("%3d ", graph->adj_matrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * Stack operations for DFS
 */
Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

bool is_stack_empty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int value) {
    if (stack->top >= MAX_VERTICES - 1) {
        printf("Error: Stack overflow\n");
        return;
    }
    stack->data[++stack->top] = value;
}

int pop(Stack* stack) {
    if (is_stack_empty(stack)) {
        printf("Error: Stack underflow\n");
        return -1;
    }
    return stack->data[stack->top--];
}

int peek(Stack* stack) {
    if (is_stack_empty(stack)) {
        return -1;
    }
    return stack->data[stack->top];
}

/**
 * Queue operations for BFS
 */
Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    return queue;
}

bool is_queue_empty(Queue* queue) {
    return queue->size == 0;
}

void enqueue(Queue* queue, int value) {
    if (queue->size >= MAX_VERTICES) {
        printf("Error: Queue overflow\n");
        return;
    }
    queue->rear = (queue->rear + 1) % MAX_VERTICES;
    queue->data[queue->rear] = value;
    queue->size++;
}

int dequeue(Queue* queue) {
    if (is_queue_empty(queue)) {
        printf("Error: Queue underflow\n");
        return -1;
    }
    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAX_VERTICES;
    queue->size--;
    return value;
}

/**
 * Recursive DFS
 */
void dfs_recursive_util(Graph* graph, int vertex, bool visited[], int* order, int* index) {
    visited[vertex] = true;
    order[(*index)++] = vertex;
    
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adj_matrix[vertex][i] > 0 && !visited[i]) {
            dfs_recursive_util(graph, i, visited, order, index);
        }
    }
}

/**
 * Recursive DFS wrapper
 */
int* dfs_recursive(Graph* graph, int start_vertex) {
    if (!graph || start_vertex < 0 || start_vertex >= graph->vertices) {
        printf("Error: Invalid start vertex\n");
        return NULL;
    }
    
    bool visited[MAX_VERTICES] = {false};
    int* traversal_order = (int*)malloc(graph->vertices * sizeof(int));
    int index = 0;
    
    dfs_recursive_util(graph, start_vertex, visited, traversal_order, &index);
    
    // Visit any unconnected vertices (for disconnected graphs)
    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            dfs_recursive_util(graph, i, visited, traversal_order, &index);
        }
    }
    
    return traversal_order;
}

/**
 * Iterative DFS using stack
 */
int* dfs_iterative(Graph* graph, int start_vertex) {
    if (!graph || start_vertex < 0 || start_vertex >= graph->vertices) {
        printf("Error: Invalid start vertex\n");
        return NULL;
    }
    
    bool visited[MAX_VERTICES] = {false};
    int* traversal_order = (int*)malloc(graph->vertices * sizeof(int));
    int index = 0;
    
    Stack* stack = create_stack();
    push(stack, start_vertex);
    
    while (!is_stack_empty(stack)) {
        int current = pop(stack);
        
        if (!visited[current]) {
            visited[current] = true;
            traversal_order[index++] = current;
            
            // Push all unvisited neighbors (in reverse order for natural ordering)
            for (int i = graph->vertices - 1; i >= 0; i--) {
                if (graph->adj_matrix[current][i] > 0 && !visited[i]) {
                    push(stack, i);
                }
            }
        }
    }
    
    free(stack);
    return traversal_order;
}

/**
 * BFS using queue
 */
int* bfs(Graph* graph, int start_vertex) {
    if (!graph || start_vertex < 0 || start_vertex >= graph->vertices) {
        printf("Error: Invalid start vertex\n");
        return NULL;
    }
    
    bool visited[MAX_VERTICES] = {false};
    int* traversal_order = (int*)malloc(graph->vertices * sizeof(int));
    int index = 0;
    
    Queue* queue = create_queue();
    visited[start_vertex] = true;
    enqueue(queue, start_vertex);
    
    while (!is_queue_empty(queue)) {
        int current = dequeue(queue);
        traversal_order[index++] = current;
        
        // Enqueue all unvisited neighbors
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adj_matrix[current][i] > 0 && !visited[i]) {
                visited[i] = true;
                enqueue(queue, i);
            }
        }
    }
    
    free(queue);
    return traversal_order;
}

/**
 * Find shortest path using BFS (unweighted graph)
 */
int* shortest_path_bfs(Graph* graph, int start_vertex, int* distance) {
    if (!graph || start_vertex < 0 || start_vertex >= graph->vertices) {
        printf("Error: Invalid start vertex\n");
        return NULL;
    }
    
    bool visited[MAX_VERTICES] = {false};
    int* parent = (int*)malloc(graph->vertices * sizeof(int));
    
    for (int i = 0; i < graph->vertices; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }
    
    Queue* queue = create_queue();
    visited[start_vertex] = true;
    distance[start_vertex] = 0;
    enqueue(queue, start_vertex);
    
    while (!is_queue_empty(queue)) {
        int current = dequeue(queue);
        
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adj_matrix[current][i] > 0 && !visited[i]) {
                visited[i] = true;
                distance[i] = distance[current] + 1;
                parent[i] = current;
                enqueue(queue, i);
            }
        }
    }
    
    free(queue);
    return parent;
}

/**
 * Reconstruct path from BFS parent array
 */
void reconstruct_path(int* parent, int start_vertex, int end_vertex) {
    if (parent[end_vertex] == -1 && end_vertex != start_vertex) {
        printf("No path exists from %d to %d\n", start_vertex, end_vertex);
        return;
    }
    
    // Build path in reverse
    int path[MAX_VERTICES];
    int current = end_vertex;
    int path_length = 0;
    
    while (current != -1) {
        path[path_length++] = current;
        current = parent[current];
    }
    
    // Print path in correct order
    printf("Path from %d to %d: ", start_vertex, end_vertex);
    for (int i = path_length - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) printf(" -> ");
    }
    printf(" (Length: %d)\n", path_length - 1);
}

/**
 * Check if graph is connected using BFS
 */
bool is_connected(Graph* graph) {
    if (!graph || graph->vertices == 0) return true;
    
    bool visited[MAX_VERTICES] = {false};
    Queue* queue = create_queue();
    
    visited[0] = true;
    enqueue(queue, 0);
    int visited_count = 1;
    
    while (!is_queue_empty(queue)) {
        int current = dequeue(queue);
        
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adj_matrix[current][i] > 0 && !visited[i]) {
                visited[i] = true;
                visited_count++;
                enqueue(queue, i);
            }
        }
    }
    
    free(queue);
    return visited_count == graph->vertices;
}

/**
 * Count connected components using DFS
 */
int count_connected_components(Graph* graph) {
    if (!graph || graph->vertices == 0) return 0;
    
    bool visited[MAX_VERTICES] = {false};
    int components = 0;
    
    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            components++;
            
            // DFS to mark all vertices in this component
            Stack* stack = create_stack();
            push(stack, i);
            
            while (!is_stack_empty(stack)) {
                int current = pop(stack);
                
                if (!visited[current]) {
                    visited[current] = true;
                    
                    for (int j = 0; j < graph->vertices; j++) {
                        if (graph->adj_matrix[current][j] > 0 && !visited[j]) {
                            push(stack, j);
                        }
                    }
                }
            }
            
            free(stack);
        }
    }
    
    return components;
}

/**
 * Print traversal order
 */
void print_traversal(int* traversal, int vertices, char* algorithm) {
    printf("%s Traversal Order: ", algorithm);
    for (int i = 0; i < vertices; i++) {
        printf("%d", traversal[i]);
        if (i < vertices - 1) printf(" -> ");
    }
    printf("\n");
}

/**
 * Main function to demonstrate DFS and BFS
 */
int main() {
    printf("=== DFS & BFS IMPLEMENTATION ===\n\n");
    
    // Create an undirected graph
    Graph* graph = create_graph(8, false);
    
    // Add edges (undirected)
    add_edge(graph, 0, 1, 1);
    add_edge(graph, 0, 2, 1);
    add_edge(graph, 1, 3, 1);
    add_edge(graph, 1, 4, 1);
    add_edge(graph, 2, 5, 1);
    add_edge(graph, 2, 6, 1);
    add_edge(graph, 3, 7, 1);
    add_edge(graph, 4, 7, 1);
    
    printf("Test 1: Graph Structure\n");
    printf("=======================\n");
    print_graph(graph);
    
    printf("\nTest 2: DFS Traversals\n");
    printf("=====================\n");
    
    int* dfs_rec = dfs_recursive(graph, 0);
    print_traversal(dfs_rec, graph->vertices, "DFS Recursive");
    free(dfs_rec);
    
    int* dfs_iter = dfs_iterative(graph, 0);
    print_traversal(dfs_iter, graph->vertices, "DFS Iterative");
    free(dfs_iter);
    
    printf("\nTest 3: BFS Traversal\n");
    printf("====================\n");
    
    int* bfs_order = bfs(graph, 0);
    print_traversal(bfs_order, graph->vertices, "BFS");
    free(bfs_order);
    
    printf("\nTest 4: Shortest Path using BFS\n");
    printf("===============================\n");
    
    int distance[MAX_VERTICES];
    int* parent = shortest_path_bfs(graph, 0, distance);
    
    printf("Shortest distances from vertex 0:\n");
    for (int i = 0; i < graph->vertices; i++) {
        if (distance[i] == INT_MAX) {
            printf("Vertex %d: Unreachable\n", i);
        } else {
            printf("Vertex %d: Distance %d\n", i, distance[i]);
        }
    }
    
    printf("\n");
    reconstruct_path(parent, 0, 7);
    reconstruct_path(parent, 0, 5);
    reconstruct_path(parent, 0, 3);
    
    free(parent);
    
    printf("\nTest 5: Graph Connectivity\n");
    printf("=========================\n");
    
    printf("Graph is %sconnected\n", is_connected(graph) ? "" : "not ");
    printf("Number of connected components: %d\n", count_connected_components(graph));
    
    printf("\nTest 6: Disconnected Graph\n");
    printf("==========================\n");
    
    // Create a disconnected graph
    Graph* disconnected_graph = create_graph(6, false);
    
    // First component
    add_edge(disconnected_graph, 0, 1, 1);
    add_edge(disconnected_graph, 0, 2, 1);
    add_edge(disconnected_graph, 1, 2, 1);
    
    // Second component
    add_edge(disconnected_graph, 3, 4, 1);
    add_edge(disconnected_graph, 3, 5, 1);
    add_edge(disconnected_graph, 4, 5, 1);
    
    printf("Disconnected graph:\n");
    print_graph(disconnected_graph);
    
    printf("\nDFS from vertex 0 (first component only):\n");
    int* dfs_disconnected = dfs_recursive(disconnected_graph, 0);
    for (int i = 0; i < 3; i++) { // Only first 3 vertices in first component
        printf("%d ", dfs_disconnected[i]);
    }
    printf("\n");
    free(dfs_disconnected);
    
    printf("Number of connected components: %d\n", 
           count_connected_components(disconnected_graph));
    
    printf("\nTest 7: Directed Graph\n");
    printf("=====================\n");
    
    Graph* directed_graph = create_graph(5, true);
    add_edge(directed_graph, 0, 1, 1);
    add_edge(directed_graph, 0, 2, 1);
    add_edge(directed_graph, 1, 3, 1);
    add_edge(directed_graph, 2, 4, 1);
    add_edge(directed_graph, 3, 4, 1);
    
    printf("Directed graph:\n");
    print_graph(directed_graph);
    
    printf("\nDFS from vertex 0:\n");
    int* dfs_directed = dfs_recursive(directed_graph, 0);
    print_traversal(dfs_directed, directed_graph->vertices, "DFS");
    free(dfs_directed);
    
    printf("\nBFS from vertex 0:\n");
    int* bfs_directed = bfs(directed_graph, 0);
    print_traversal(bfs_directed, directed_graph->vertices, "BFS");
    free(bfs_directed);
    
    // Clean up
    free(graph);
    free(disconnected_graph);
    free(directed_graph);
    
    printf("\n=== PROGRAM COMPLETED ===\n");
    
    return 0;
}
