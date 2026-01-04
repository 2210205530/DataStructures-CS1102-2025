/**
*student name [meseud hadis redi]
 *student id[2210205530]
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>

// Include the functions from dfs_bfs.c
#include "dfs_bfs.c"

/**
 * Test graph creation and edge addition
 */
void test_graph_operations() {
    printf("Test 1: Graph operations... ");
    
    Graph* graph = create_graph(5, false);
    assert(graph != NULL);
    assert(graph->vertices == 5);
    assert(graph->is_directed == false);
    
    // Test edge addition
    add_edge(graph, 0, 1, 1);
    assert(graph->adj_matrix[0][1] == 1);
    assert(graph->adj_matrix[1][0] == 1); // Undirected
    
    add_edge(graph, 0, 2, 1);
    assert(graph->adj_matrix[0][2] == 1);
    assert(graph->adj_matrix[2][0] == 1);
    
    // Test directed graph
    Graph* directed = create_graph(3, true);
    add_edge(directed, 0, 1, 1);
    assert(directed->adj_matrix[0][1] == 1);
    assert(directed->adj_matrix[1][0] == 0); // Not in undirected
    
    free(graph);
    free(directed);
    printf("PASS\n");
}

/**
 * Test DFS implementations
 */
void test_dfs() {
    printf("Test 2: DFS implementations... ");
    
    // Create a simple graph: 0-1-2
    Graph* graph = create_graph(3, false);
    add_edge(graph, 0, 1, 1);
    add_edge(graph, 1, 2, 1);
    
    // Test recursive DFS
    int* dfs_rec = dfs_recursive(graph, 0);
    assert(dfs_rec[0] == 0);
    assert(dfs_rec[1] == 1 || dfs_rec[1] == 2); // Order depends on implementation
    assert(dfs_rec[2] == 2 || dfs_rec[2] == 1);
    free(dfs_rec);
    
    // Test iterative DFS
    int* dfs_iter = dfs_iterative(graph, 0);
    assert(dfs_iter[0] == 0);
    // Both neighbors should be visited
    bool found1 = false, found2 = false;
    for (int i = 1; i < 3; i++) {
        if (dfs_iter[i] == 1) found1 = true;
        if (dfs_iter[i] == 2) found2 = true;
    }
    assert(found1 && found2);
    free(dfs_iter);
    
    free(graph);
    printf("PASS\n");
}

/**
 * Test BFS implementation
 */
void test_bfs() {
    printf("Test 3: BFS implementation... ");
    
    // Create a tree-like graph
    Graph* graph = create_graph(5, false);
    add_edge(graph, 0, 1, 1);
    add_edge(graph, 0, 2, 1);
    add_edge(graph, 1, 3, 1);
    add_edge(graph, 1, 4, 1);
    
    int* bfs_order = bfs(graph, 0);
    
    // BFS should visit in level order
    assert(bfs_order[0] == 0); // Root
    // Level 1: vertices 1 and 2 (order may vary)
    assert((bfs_order[1] == 1 && bfs_order[2] == 2) ||
           (bfs_order[1] == 2 && bfs_order[2] == 1));
    // Level 2: vertices 3 and 4
    assert((bfs_order[3] == 3 && bfs_order[4] == 4) ||
           (bfs_order[3] == 4 && bfs_order[4] == 3));
    
    free(bfs_order);
    free(graph);
    printf("PASS\n");
}

/**
 * Test shortest path BFS
 */
void test_shortest_path() {
    printf("Test 4: Shortest path BFS... ");
    
    // Create a graph with a known shortest path
    Graph* graph = create_graph(6, false);
    add_edge(graph, 0, 1, 1);
    add_edge(graph, 0, 2, 1);
    add_edge(graph, 1, 3, 1);
    add_edge(graph, 2, 3, 1);
    add_edge(graph, 3, 4, 1);
    add_edge(graph, 4, 5, 1);
    
    int distance[MAX_VERTICES];
    int* parent = shortest_path_bfs(graph, 0, distance);
    
    // Test distances
    assert(distance[0] == 0);
    assert(distance[1] == 1);
    assert(distance[2] == 1);
    assert(distance[3] == 2); // Two paths: 0-1-3 or 0-2-3
    assert(distance[5] == 4); // 0-1-3-4-5 or similar
    
    // Test path reconstruction
    // Path from 0 to 5 should have length 4
    bool visited[MAX_VERTICES] = {false};
    int current = 5;
    int path_length = 0;
    
    while (current != -1) {
        visited[current] = true;
        current = parent[current];
        path_length++;
    }
    
    assert(path_length == 5); // Includes start and end vertices
    assert(visited[0]); // Should include start
    assert(visited[5]); // Should include end
    
    free(parent);
    free(graph);
    printf("PASS\n");
}

/**
 * Test connectivity
 */
void test_connectivity() {
    printf("Test 5: Graph connectivity... ");
    
    // Test connected graph
    Graph* connected = create_graph(4, false);
    add_edge(connected, 0, 1, 1);
    add_edge(connected, 1, 2, 1);
    add_edge(connected, 2, 3, 1);
    
    assert(is_connected(connected) == true);
    assert(count_connected_components(connected) == 1);
    
    // Test disconnected graph
    Graph* disconnected = create_graph(5, false);
    add_edge(disconnected, 0, 1, 1); // Component 1: 0-1
    add_edge(disconnected, 1, 2, 1); // Component 1: 0-1-2
    add_edge(disconnected, 3, 4, 1); // Component 2: 3-4
    
    assert(is_connected(disconnected) == false);
    assert(count_connected_components(disconnected) == 2);
    
    free(connected);
    free(disconnected);
    printf("PASS\n");
}

/**
 * Test stack operations
 */
void test_stack() {
    printf("Test 6: Stack operations... ");
    
    Stack* stack = create_stack();
    assert(is_stack_empty(stack) == true);
    
    push(stack, 10);
    assert(is_stack_empty(stack) == false);
    assert(peek(stack) == 10);
    
    push(stack, 20);
    assert(peek(stack) == 20);
    
    assert(pop(stack) == 20);
    assert(pop(stack) == 10);
    assert(is_stack_empty(stack) == true);
    
    free(stack);
    printf("PASS\n");
}

/**
 * Test queue operations
 */
void test_queue() {
    printf("Test 7: Queue operations... ");
    
    Queue* queue = create_queue();
    assert(is_queue_empty(queue) == true);
    
    enqueue(queue, 10);
    assert(is_queue_empty(queue) == false);
    
    enqueue(queue, 20);
    enqueue(queue, 30);
    
    assert(dequeue(queue) == 10);
    assert(dequeue(queue) == 20);
    assert(dequeue(queue) == 30);
    assert(is_queue_empty(queue) == true);
    
    free(queue);
    printf("PASS\n");
}

/**
 * Test edge cases
 */
void test_edge_cases() {
    printf("Test 8: Edge cases... ");
    
    // Test empty graph
    Graph* empty = create_graph(0, false);
    assert(count_connected_components(empty) == 0);
    free(empty);
    
    // Test single vertex graph
    Graph* single = create_graph(1, false);
    assert(is_connected(single) == true);
    assert(count_connected_components(single) == 1);
    
    int* dfs_single = dfs_recursive(single, 0);
    assert(dfs_single[0] == 0);
    free(dfs_single);
    free(single);
    
    // Test invalid vertex in DFS/BFS
    Graph* graph = create_graph(3, false);
    int* invalid = dfs_recursive(graph, 5); // Invalid vertex
    assert(invalid == NULL);
    
    invalid = bfs(graph, -1); // Invalid vertex
    assert(invalid == NULL);
    
    // Test NULL graph
    assert(is_connected(NULL) == true);
    assert(count_connected_components(NULL) == 0);
    
    free(graph);
    printf("PASS\n");
}

/**
 * Test directed vs undirected
 */
void test_directed_undirected() {
    printf("Test 9: Directed vs undirected... ");
    
    // Create same edges in directed and undirected graphs
    Graph* undirected = create_graph(3, false);
    Graph* directed = create_graph(3, true);
    
    add_edge(undirected, 0, 1, 1);
    add_edge(directed, 0, 1, 1);
    
    // In undirected, edge should be symmetric
    assert(undirected->adj_matrix[0][1] == 1);
    assert(undirected->adj_matrix[1][0] == 1);
    
    // In directed, edge should be one-way
    assert(directed->adj_matrix[0][1] == 1);
    assert(directed->adj_matrix[1][0] == 0);
    
    // Test connectivity in directed vs undirected
    add_edge(directed, 1, 2, 1);
    add_edge(directed, 2, 0, 1); // Creates a cycle
    
    int* dfs_dir = dfs_recursive(directed, 0);
    bool all_visited = true;
    for (int i = 0; i < 3; i++) {
        bool found = false;
        for (int j = 0; j < 3; j++) {
            if (dfs_dir[j] == i) found = true;
        }
        if (!found) all_visited = false;
    }
    assert(all_visited); // Should visit all in directed cycle
    
    free(dfs_dir);
    free(undirected);
    free(directed);
    printf("PASS\n");
}

/**
 * Main test runner
 */
int main() {
    printf("\n=== TESTING DFS & BFS IMPLEMENTATIONS ===\n\n");
    
    test_graph_operations();
    test_dfs();
    test_bfs();
    test_shortest_path();
    test_connectivity();
    test_stack();
    test_queue();
    test_edge_cases();
    test_directed_undirected();
    
    printf("\n=== ALL TESTS PASSED ===\n\n");
    
    printf("To run the main program:\n");
    printf("1. cd 9_DFS_BFS\n");
    printf("2. gcc -o dfs_bfs dfs_bfs.c\n");
    printf("3. ./dfs_bfs\n");
    
    return 0;
}
