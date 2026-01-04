/**
*student name [meseud hadis redi]
 *student id[2210205530]
 */

#ifndef TREE_FROM_ARRAY_H
#define TREE_FROM_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 100

// Tree Node structure
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Tree structure
typedef struct {
    TreeNode* root;
    int size;
} Tree;

// Tree creation functions
TreeNode* create_node(int data);
Tree* create_tree();
Tree* build_tree_from_array(int arr[], int size);
TreeNode* build_tree_from_array_util(int arr[], int index, int size);
Tree* build_bst_from_sorted_array(int arr[], int size);
TreeNode* build_bst_from_sorted_array_util(int arr[], int start, int end);

// Traversal functions
void inorder_traversal(TreeNode* root);
void preorder_traversal(TreeNode* root);
void postorder_traversal(TreeNode* root);
void level_order_traversal(TreeNode* root);
void print_tree_visual_util(TreeNode* root, int space);

// Tree property functions
int tree_height(TreeNode* root);
int count_nodes(TreeNode* root);
int count_leaves(TreeNode* root);
bool search_tree(TreeNode* root, int value);
bool search_bst(TreeNode* root, int value);
int find_max(TreeNode* root);
int find_min(TreeNode* root);
bool is_bst(TreeNode* root);
bool is_bst_util(TreeNode* root, int min, int max);

// Conversion functions
int* tree_to_array(Tree* tree);
void tree_to_array_util(TreeNode* root, int arr[], int index, int size);

// Utility functions
void print_array(int arr[], int size);
void print_tree_visual(TreeNode* root);
void print_tree_visual_util(TreeNode* root, int space);

// Memory management
void free_tree(TreeNode* root);
void free_tree_structure(Tree* tree);

#endif
