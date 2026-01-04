/**
 *student name [meseud hadis redi]
 *student id[2210205530]
 */

#ifndef DFS_BFS_H
#define DFS_BFS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

// Graph structure
typedef struct {
    int vertices;
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];
    bool is_directed;
} Graph;

// Stack structure
typedef struct {
    int data[MAX_VERTICES];
    int top;
} Stack;

// Queue structure
typedef struct {
    int data[MAX_VERTICES];
    int front;
    int rear;
    int size;
} Queue;

// Graph functions
Graph* create_graph(int vertices, bool is_directed);
void add_edge(Graph* graph, int src, int dest, int weight);
void print_graph(Graph* graph);

// Stack functions
Stack* create_stack();
bool is_stack_empty(Stack* stack);
void push(Stack* stack, int value);
int pop(Stack* stack);
int peek(Stack* stack);

// Queue functions
Queue* create_queue();
bool is_queue_empty(Queue* queue);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);

// DFS functions
int* dfs_recursive(Graph* graph, int start_vertex);
void dfs_recursive_util(Graph* graph, int vertex, bool visited[], int* order, int* index);
int* dfs_iterative(Graph* graph, int start_vertex);

// BFS functions
int* bfs(Graph* graph, int start_vertex);
int* shortest_path_bfs(Graph* graph, int start_vertex, int* distance);

// Path reconstruction
void reconstruct_path(int* parent, int start_vertex, int end_vertex);

// Connectivity functions
bool is_connected(Graph* graph);
int count_connected_components(Graph* graph);

// Utility functions
void print_traversal(int* traversal, int vertices, char* algorithm);

#endif
