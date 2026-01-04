/**
 *student name [meseud hadis redi]
 *student id[2210205530]
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// Include the header file instead of .c file
#include "graph_cluster.h"

/**
 * Test Union-Find operations
 */
void test_union_find() {
    printf("Test 1: Union-Find operations... ");
    
    UnionFind* uf = create_union_find(5);
    assert(uf != NULL);
    assert(uf->size == 5);
    
    // Initially, each element is its own parent
    for (int i = 0; i < 5; i++) {
        assert(find(uf, i) == i);
    }
    
    // Test union operations
    union_sets(uf, 0, 1);
    assert(find(uf, 0) == find(uf, 1));
    assert(find(uf, 0) != find(uf, 2));
    
    union_sets(uf, 1, 2);
    assert(find(uf, 0) == find(uf, 2));
    
    union_sets(uf, 3, 4);
    assert(find(uf, 3) == find(uf, 4));
    assert(find(uf, 0) != find(uf, 3));
    
    // Test path compression
    union_sets(uf, 2, 3);
    assert(find(uf, 0) == find(uf, 4));
    
    free(uf);
    printf("PASS\n");
}

/**
 * Test graph creation
 */
void test_graph_creation() {
    printf("Test 2: Graph creation... ");
    
    int adj_matrix[3][3] = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    
    // Convert to MAX_VERTICES format
    int adj_large[MAX_VERTICES][MAX_VERTICES] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            adj_large[i][j] = adj_matrix[i][j];
        }
    }
    
    Graph* graph = create_graph(3, adj_large);
    assert(graph != NULL);
    assert(graph->vertices == 3);
    assert(graph->adj_matrix[0][1] == 1);
    assert(graph->adj_matrix[1][0] == 1);
    assert(graph->adj_matrix[0][0] == 0);
    
    free(graph);
    printf("PASS\n");
}

/**
 * Test connectivity-based clustering
 */
void test_connectivity_clustering() {
    printf("Test 3: Connectivity clustering... ");
    
    // Create a graph with two disconnected components
    int adj_matrix[6][6] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0},
        {1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };
    
    int adj_large[MAX_VERTICES][MAX_VERTICES] = {0};
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            adj_large[i][j] = adj_matrix[i][j];
        }
    }
    
    Graph* graph = create_graph(6, adj_large);
    assert(graph != NULL);
    
    int num_clusters;
    int* clusters = cluster_by_connectivity(graph, &num_clusters);
    assert(clusters != NULL);
    
    assert(num_clusters == 2);
    
    // First 3 vertices should be in same cluster
    assert(clusters[0] == clusters[1]);
    assert(clusters[1] == clusters[2]);
    
    // Last 3 vertices should be in same cluster
    assert(clusters[3] == clusters[4]);
    assert(clusters[4] == clusters[5]);
    
    // The two clusters should be different
    assert(clusters[0] != clusters[3]);
    
    free(clusters);
    free(graph);
    printf("PASS\n");
}

/**
 * Test DFS clustering
 */
void test_dfs_clustering() {
    printf("Test 4: DFS clustering... ");
    
    // Same graph as previous test
    int adj_matrix[6][6] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0},
        {1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };
    
    int adj_large[MAX_VERTICES][MAX_VERTICES] = {0};
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            adj_large[i][j] = adj_matrix[i][j];
        }
    }
    
    Graph* graph = create_graph(6, adj_large);
    assert(graph != NULL);
    
    int num_clusters;
    int* clusters = cluster_dfs(graph, &num_clusters);
    assert(clusters != NULL);
    
    assert(num_clusters == 2);
    assert(clusters[0] == clusters[1]);
    assert(clusters[1] == clusters[2]);
    assert(clusters[3] == clusters[4]);
    assert(clusters[4] == clusters[5]);
    assert(clusters[0] != clusters[3]);
    
    free(clusters);
    free(graph);
    printf("PASS\n");
}

/**
 * Test distance threshold clustering
 */
void test_distance_clustering() {
    printf("Test 5: Distance threshold clustering... ");
    
    // Weighted graph
    int adj_matrix[5][5] = {
        {0, 3, 0, 0, 8},
        {3, 0, 5, 0, 0},
        {0, 5, 0, 2, 0},
        {0, 0, 2, 0, 6},
        {8, 0, 0, 6, 0}
    };
    
    int adj_large[MAX_VERTICES][MAX_VERTICES] = {0};
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            adj_large[i][j] = adj_matrix[i][j];
        }
    }
    
    Graph* graph = create_graph(5, adj_large);
    assert(graph != NULL);
    
    int num_clusters;
    
    // Test with threshold 4 (should create multiple clusters)
    int* clusters = cluster_by_distance_threshold(graph, 4, &num_clusters);
    assert(clusters != NULL);
    assert(num_clusters > 1);
    free(clusters);
    
    // Test with threshold 10 (all should be in one cluster)
    clusters = cluster_by_distance_threshold(graph, 10, &num_clusters);
    assert(clusters != NULL);
    assert(num_clusters == 1);
    
    free(clusters);
    free(graph);
    printf("PASS\n");
}

/**
 * Test k-clusters (simplified)
 */
void test_k_clusters() {
    printf("Test 6: K-clusters (simplified)... ");
    
    // Simple complete graph
    int adj_matrix[4][4] = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0}
    };
    
    int adj_large[MAX_VERTICES][MAX_VERTICES] = {0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            adj_large[i][j] = adj_matrix[i][j];
        }
    }
    
    Graph* graph = create_graph(4, adj_large);
    assert(graph != NULL);
    
    int success;
    int* clusters = k_clusters(graph, 2, &success);
    
    assert(success == 1);
    assert(clusters != NULL);
    
    // All vertices should be assigned to cluster 1 or 2
    for (int i = 0; i < 4; i++) {
        assert(clusters[i] == 1 || clusters[i] == 2);
    }
    
    free(clusters);
    free(graph);
    printf("PASS\n");
}

/**
 * Test edge cases
 */
void test_edge_cases() {
    printf("Test 7: Edge cases... ");
    
    // Test NULL graph
    int num_clusters;
    int* clusters = cluster_by_connectivity(NULL, &num_clusters);
    assert(clusters == NULL);
    assert(num_clusters == 0);
    
    // Test empty graph (0 vertices)
    int empty_adj[MAX_VERTICES][MAX_VERTICES] = {0};
    Graph* empty_graph = create_graph(0, empty_adj);
    assert(empty_graph != NULL);
    clusters = cluster_by_connectivity(empty_graph, &num_clusters);
    assert(clusters == NULL);
    assert(num_clusters == 0);
    free(empty_graph);
    
    // Test single vertex graph
    int single_adj[MAX_VERTICES][MAX_VERTICES] = {{0}};
    Graph* single_graph = create_graph(1, single_adj);
    assert(single_graph != NULL);
    clusters = cluster_by_connectivity(single_graph, &num_clusters);
    assert(clusters != NULL);
    assert(num_clusters == 1);
    assert(clusters[0] == 1);
    free(clusters);
    free(single_graph);
    
    // Test k-clusters with invalid k
    int success;
    clusters = k_clusters(NULL, 2, &success);
    assert(success == 0);
    assert(clusters == NULL);
    
    printf("PASS\n");
}

/**
 * Test random graph generation
 */
void test_random_graph() {
    printf("Test 8: Random graph generation... ");
    
    // Set seed for reproducibility
    srand(12345);
    
    Graph* graph = create_random_graph(10, 0.5);
    assert(graph != NULL);
    assert(graph->vertices == 10);
    
    // Verify symmetry (undirected graph)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            assert(graph->adj_matrix[i][j] == graph->adj_matrix[j][i]);
        }
        assert(graph->adj_matrix[i][i] == 0);
    }
    
    free(graph);
    printf("PASS\n");
}

/**
 * Test cluster statistics
 */
void test_cluster_stats() {
    printf("Test 9: Cluster statistics... ");
    
    // Create a simple clustering result
    int cluster_map[5] = {1, 1, 2, 2, 3};
    
    // Test the function doesn't crash with valid input
    calculate_cluster_stats(cluster_map, 5, 3);
    
    // Test with NULL input
    calculate_cluster_stats(NULL, 5, 3);
    
    printf("PASS\n");
}

/**
 * Main test runner
 */
int main() {
    printf("\n=== TESTING GRAPH CLUSTERING ===\n\n");
    
    test_union_find();
    test_graph_creation();
    test_connectivity_clustering();
    test_dfs_clustering();
    test_distance_clustering();
    test_k_clusters();
    test_edge_cases();
    test_random_graph();
    test_cluster_stats();
    
    printf("\n=== ALL TESTS PASSED ===\n\n");
    
    printf("To run the main program:\n");
    printf("1. gcc -o test_graph test_graph.c graph_cluster.c\n");
    printf("2. ./test_graph\n");
    
    return 0;
}
