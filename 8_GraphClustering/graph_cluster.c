/**
 *student name [meseud hadis redi]
 *student id[2210205530]
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

// Union-Find (Disjoint Set Union) structure
typedef struct {
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES];
    int size;
} UnionFind;

// Graph structure (adjacency matrix)
typedef struct {
    int vertices;
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];
    bool is_weighted;
} Graph;

/**
 * Create and initialize Union-Find structure
 */
UnionFind* create_union_find(int size) {
    UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    if (!uf) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    
    uf->size = size;
    for (int i = 0; i < size; i++) {
        uf->parent[i] = i;  // Each element is its own parent initially
        uf->rank[i] = 0;    // Initial rank is 0
    }
    return uf;
}

/**
 * Find with path compression
 */
int find(UnionFind* uf, int x) {
    if (uf->parent[x] != x) {
        uf->parent[x] = find(uf, uf->parent[x]);  // Path compression
    }
    return uf->parent[x];
}

/**
 * Union by rank
 */
void union_sets(UnionFind* uf, int x, int y) {
    int root_x = find(uf, x);
    int root_y = find(uf, y);
    
    if (root_x == root_y) return;  // Already in same set
    
    // Union by rank
    if (uf->rank[root_x] < uf->rank[root_y]) {
        uf->parent[root_x] = root_y;
    } else if (uf->rank[root_x] > uf->rank[root_y]) {
        uf->parent[root_y] = root_x;
    } else {
        uf->parent[root_y] = root_x;
        uf->rank[root_x]++;
    }
}

/**
 * Create graph from adjacency matrix
 */
Graph* create_graph(int vertices, int adj_matrix[MAX_VERTICES][MAX_VERTICES]) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    
    graph->vertices = vertices;
    graph->is_weighted = false;
    
    // Copy adjacency matrix
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adj_matrix[i][j] = adj_matrix[i][j];
            if (adj_matrix[i][j] > 1) {
                graph->is_weighted = true;
            }
        }
    }
    
    return graph;
}

/**
 * Create a random graph for testing
 */
Graph* create_random_graph(int vertices, float edge_probability) {
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];
    
    // Initialize with zeros
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j) {
                adj_matrix[i][j] = 0;  // No self-loops
            } else {
                // Random edge based on probability
                float random_val = (float)rand() / RAND_MAX;
                adj_matrix[i][j] = (random_val < edge_probability) ? 1 : 0;
                // Make it undirected
                adj_matrix[j][i] = adj_matrix[i][j];
            }
        }
    }
    
    return create_graph(vertices, adj_matrix);
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
           graph->is_weighted ? "weighted" : "unweighted");
    
    printf("Adjacency Matrix:\n   ");
    for (int i = 0; i < graph->vertices; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < graph->vertices; i++) {
        printf("%2d ", i);
        for (int j = 0; j < graph->vertices; j++) {
            printf("%2d ", graph->adj_matrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * Clustering based on threshold (connect components)
 * Clusters vertices that are connected (edge > 0)
 */
int* cluster_by_connectivity(Graph* graph, int* num_clusters) {
    if (!graph) {
        *num_clusters = 0;
        return NULL;
    }
    
    UnionFind* uf = create_union_find(graph->vertices);
    
    // Union all connected vertices
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = i + 1; j < graph->vertices; j++) {
            if (graph->adj_matrix[i][j] > 0) {
                union_sets(uf, i, j);
            }
        }
    }
    
    // Count clusters and assign cluster IDs
    int* cluster_map = (int*)malloc(graph->vertices * sizeof(int));
    int cluster_ids[MAX_VERTICES] = {0};
    int next_cluster_id = 1;
    
    for (int i = 0; i < graph->vertices; i++) {
        int root = find(uf, i);
        if (cluster_ids[root] == 0) {
            cluster_ids[root] = next_cluster_id++;
        }
        cluster_map[i] = cluster_ids[root];
    }
    
    *num_clusters = next_cluster_id - 1;
    free(uf);
    return cluster_map;
}

/**
 * Clustering based on distance threshold
 * For weighted graphs, cluster vertices with weight <= threshold
 */
int* cluster_by_distance_threshold(Graph* graph, int threshold, int* num_clusters) {
    if (!graph) {
        *num_clusters = 0;
        return NULL;
    }
    
    UnionFind* uf = create_union_find(graph->vertices);
    
    // Union vertices with distance <= threshold
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = i + 1; j < graph->vertices; j++) {
            if (graph->adj_matrix[i][j] > 0 && graph->adj_matrix[i][j] <= threshold) {
                union_sets(uf, i, j);
            }
        }
    }
    
    // Count clusters and assign cluster IDs
    int* cluster_map = (int*)malloc(graph->vertices * sizeof(int));
    int cluster_ids[MAX_VERTICES] = {0};
    int next_cluster_id = 1;
    
    for (int i = 0; i < graph->vertices; i++) {
        int root = find(uf, i);
        if (cluster_ids[root] == 0) {
            cluster_ids[root] = next_cluster_id++;
        }
        cluster_map[i] = cluster_ids[root];
    }
    
    *num_clusters = next_cluster_id - 1;
    free(uf);
    return cluster_map;
}

/**
 * K-means like clustering (simplified)
 * Clusters vertices into k clusters based on connectivity
 */
// In the k_clusters function, fix the array bounds issue:
int* k_clusters(Graph* graph, int k, int* success) {
    if (!graph || k <= 0 || k > graph->vertices) {
        *success = 0;
        return NULL;
    }
    
    // Simplified k-clusters algorithm
    int* cluster_map = (int*)malloc(graph->vertices * sizeof(int));
    if (!cluster_map) {
        *success = 0;
        return NULL;
    }
    
    // Initialize clusters (simple round-robin assignment)
    for (int i = 0; i < graph->vertices; i++) {
        cluster_map[i] = (i % k) + 1;
    }
    
    // Simple iterative improvement
    for (int iter = 0; iter < 10; iter++) {
        int changed = 0;
        
        for (int v = 0; v < graph->vertices; v++) {
            // Count connections to each cluster
            int* cluster_connections = (int*)calloc(k + 1, sizeof(int));
            if (!cluster_connections) continue;
            
            for (int u = 0; u < graph->vertices; u++) {
                if (graph->adj_matrix[v][u] > 0) {
                    int cluster = cluster_map[u];
                    if (cluster >= 1 && cluster <= k) {
                        cluster_connections[cluster] += graph->adj_matrix[v][u];
                    }
                }
            }
            
            // Find best cluster (most connections)
            int best_cluster = 1;
            for (int c = 2; c <= k; c++) {
                if (cluster_connections[c] > cluster_connections[best_cluster]) {
                    best_cluster = c;
                }
            }
            
            // Reassign if better
            if (cluster_map[v] != best_cluster) {
                cluster_map[v] = best_cluster;
                changed = 1;
            }
            
            free(cluster_connections);
        }
        
        if (!changed) break;
    }
    
    *success = 1;
    return cluster_map;
}

// Make dfs_clustering static to avoid linker issues
static void dfs_clustering(Graph* graph, int vertex, bool visited[], int cluster_id, int* cluster_map) {
    visited[vertex] = true;
    cluster_map[vertex] = cluster_id;
    
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adj_matrix[vertex][i] > 0 && !visited[i]) {
            dfs_clustering(graph, i, visited, cluster_id, cluster_map);
        }
    }
}

/**
 * Print clusters
 */
void print_clusters(int* cluster_map, int num_vertices, int num_clusters) {
    if (!cluster_map) {
        printf("No clusters to print\n");
        return;
    }
    
    printf("\nClusters (%d clusters found):\n", num_clusters);
    
    // Group vertices by cluster
    int clusters[num_clusters + 1][MAX_VERTICES];
    int cluster_sizes[num_clusters + 1] = {0};
    
    for (int i = 0; i < num_vertices; i++) {
        int cluster = cluster_map[i];
        clusters[cluster][cluster_sizes[cluster]++] = i;
    }
    
    // Print each cluster
    for (int c = 1; c <= num_clusters; c++) {
        if (cluster_sizes[c] > 0) {
            printf("Cluster %d (%d vertices): ", c, cluster_sizes[c]);
            for (int i = 0; i < cluster_sizes[c]; i++) {
                printf("%d ", clusters[c][i]);
            }
            printf("\n");
        }
    }
}

/**
 * Calculate cluster statistics
 */
void calculate_cluster_stats(int* cluster_map, int num_vertices, int num_clusters) {
    if (!cluster_map) return;
    
    int cluster_sizes[num_clusters + 1] = {0};
    int min_size = num_vertices, max_size = 0;
    
    // Count cluster sizes
    for (int i = 0; i < num_vertices; i++) {
        cluster_sizes[cluster_map[i]]++;
    }
    
    // Find min and max
    for (int c = 1; c <= num_clusters; c++) {
        if (cluster_sizes[c] < min_size) min_size = cluster_sizes[c];
        if (cluster_sizes[c] > max_size) max_size = cluster_sizes[c];
    }
    
    printf("\nCluster Statistics:\n");
    printf("Number of clusters: %d\n", num_clusters);
    printf("Min cluster size: %d\n", min_size);
    printf("Max cluster size: %d\n", max_size);
    printf("Average cluster size: %.2f\n", (float)num_vertices / num_clusters);
}

/**
 * Find connected components using DFS
 */
void dfs_clustering(Graph* graph, int vertex, bool visited[], int cluster_id, int* cluster_map) {
    visited[vertex] = true;
    cluster_map[vertex] = cluster_id;
    
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adj_matrix[vertex][i] > 0 && !visited[i]) {
            dfs_clustering(graph, i, visited, cluster_id, cluster_map);
        }
    }
}

/**
 * Cluster using DFS (connected components)
 */
int* cluster_dfs(Graph* graph, int* num_clusters) {
    if (!graph) {
        *num_clusters = 0;
        return NULL;
    }
    
    bool visited[MAX_VERTICES] = {false};
    int* cluster_map = (int*)malloc(graph->vertices * sizeof(int));
    int cluster_id = 1;
    
    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            dfs_clustering(graph, i, visited, cluster_id, cluster_map);
            cluster_id++;
        }
    }
    
    *num_clusters = cluster_id - 1;
    return cluster_map;
}

/**
 * Main function to demonstrate graph clustering
 */
int main() {
    printf("=== GRAPH CLUSTERING IMPLEMENTATION ===\n\n");
    
    // Seed random number generator
    srand(42);
    
    // Create a sample graph (6 vertices)
    int vertices = 6;
    int adj_matrix[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0, 0, 1, 0},
        {1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 1},
        {1, 1, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0}
    };
    
    Graph* graph = create_graph(vertices, adj_matrix);
    
    printf("Test 1: Basic Graph\n");
    printf("===================\n");
    print_graph(graph);
    
    printf("\nTest 2: Clustering by Connectivity (Union-Find)\n");
    printf("===============================================\n");
    
    int num_clusters;
    int* clusters = cluster_by_connectivity(graph, &num_clusters);
    print_clusters(clusters, vertices, num_clusters);
    calculate_cluster_stats(clusters, vertices, num_clusters);
    free(clusters);
    
    printf("\nTest 3: Clustering using DFS (Connected Components)\n");
    printf("===================================================\n");
    
    clusters = cluster_dfs(graph, &num_clusters);
    print_clusters(clusters, vertices, num_clusters);
    free(clusters);
    
    printf("\nTest 4: Weighted Graph Clustering by Distance\n");
    printf("============================================\n");
    
    // Create a weighted graph
    int weighted_adj[MAX_VERTICES][MAX_VERTICES] = {
        {0, 5, 0, 0, 2, 0},
        {5, 0, 3, 0, 4, 0},
        {0, 3, 0, 6, 0, 0},
        {0, 0, 6, 0, 1, 8},
        {2, 4, 0, 1, 0, 0},
        {0, 0, 0, 8, 0, 0}
    };
    
    Graph* weighted_graph = create_graph(vertices, weighted_adj);
    print_graph(weighted_graph);
    
    printf("\nClustering with distance threshold 3:\n");
    clusters = cluster_by_distance_threshold(weighted_graph, 3, &num_clusters);
    print_clusters(clusters, vertices, num_clusters);
    free(clusters);
    
    printf("\nClustering with distance threshold 5:\n");
    clusters = cluster_by_distance_threshold(weighted_graph, 5, &num_clusters);
    print_clusters(clusters, vertices, num_clusters);
    free(clusters);
    
    printf("\nTest 5: K-Clusters (Simplified K-means)\n");
    printf("=======================================\n");
    
    int success;
    clusters = k_clusters(graph, 2, &success);
    if (success) {
        print_clusters(clusters, vertices, 2);
        free(clusters);
    }
    
    printf("\nTest 6: Random Graph Clustering\n");
    printf("===============================\n");
    
    // Create random graph with 10 vertices
    Graph* random_graph = create_random_graph(10, 0.3);
    print_graph(random_graph);
    
    clusters = cluster_by_connectivity(random_graph, &num_clusters);
    print_clusters(clusters, 10, num_clusters);
    calculate_cluster_stats(clusters, 10, num_clusters);
    
    // Clean up
    free(clusters);
    free(graph);
    free(weighted_graph);
    free(random_graph);
    
    printf("\n=== PROGRAM COMPLETED ===\n");
    
    return 0;
}
