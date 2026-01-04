/**
 *student name [meseud hadis redi]
 *student id[2210205530]
 */

#ifndef GRAPH_CLUSTER_H
#define GRAPH_CLUSTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Union-Find structure
typedef struct {
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES];
    int size;
} UnionFind;

// Graph structure
typedef struct {
    int vertices;
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];
    bool is_weighted;
} Graph;

// Union-Find functions
UnionFind* create_union_find(int size);
int find(UnionFind* uf, int x);
void union_sets(UnionFind* uf, int x, int y);

// Graph functions
Graph* create_graph(int vertices, int adj_matrix[MAX_VERTICES][MAX_VERTICES]);
Graph* create_random_graph(int vertices, float edge_probability);
void print_graph(Graph* graph);

// Clustering algorithms
int* cluster_by_connectivity(Graph* graph, int* num_clusters);
int* cluster_by_distance_threshold(Graph* graph, int threshold, int* num_clusters);
int* k_clusters(Graph* graph, int k, int* success);
int* cluster_dfs(Graph* graph, int* num_clusters);

// Utility functions
void print_clusters(int* cluster_map, int num_vertices, int num_clusters);
void calculate_cluster_stats(int* cluster_map, int num_vertices, int num_clusters);

#endif
