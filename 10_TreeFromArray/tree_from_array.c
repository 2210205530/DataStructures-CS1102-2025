/**
*student name [meseud hadis redi]
 *student id[2210205530]
 */

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

/**
 * Create a new tree node
 */
TreeNode* create_node(int data) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!new_node) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/**
 * Create an empty tree
 */
Tree* create_tree() {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    if (!tree) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

/**
 * Build complete binary tree from array representation
 * Array representation: For node at index i:
 *   - Left child at index 2*i + 1
 *   - Right child at index 2*i + 2
 *   - Parent at index (i-1)/2
 */
TreeNode* build_tree_from_array_util(int arr[], int index, int size) {
    if (index >= size || arr[index] == INT_MIN) {
        return NULL;
    }
    
    TreeNode* root = create_node(arr[index]);
    
    // Recursively build left and right subtrees
    root->left = build_tree_from_array_util(arr, 2*index + 1, size);
    root->right = build_tree_from_array_util(arr, 2*index + 2, size);
    
    return root;
}

/**
 * Build complete binary tree from array (wrapper function)
 */
Tree* build_tree_from_array(int arr[], int size) {
    Tree* tree = create_tree();
    if (!tree) return NULL;
    
    tree->root = build_tree_from_array_util(arr, 0, size);
    tree->size = size;
    
    return tree;
}

/**
 * Build Binary Search Tree (BST) from sorted array
 */
TreeNode* build_bst_from_sorted_array_util(int arr[], int start, int end) {
    if (start > end) {
        return NULL;
    }
    
    // Middle element becomes root
    int mid = start + (end - start) / 2;
    TreeNode* root = create_node(arr[mid]);
    
    // Recursively build left and right subtrees
    root->left = build_bst_from_sorted_array_util(arr, start, mid - 1);
    root->right = build_bst_from_sorted_array_util(arr, mid + 1, end);
    
    return root;
}

/**
 * Build BST from sorted array (balanced)
 */
Tree* build_bst_from_sorted_array(int arr[], int size) {
    Tree* tree = create_tree();
    if (!tree) return NULL;
    
    tree->root = build_bst_from_sorted_array_util(arr, 0, size - 1);
    tree->size = size;
    
    return tree;
}

/**
 * Inorder traversal (Left, Root, Right)
 */
void inorder_traversal(TreeNode* root) {
    if (root == NULL) return;
    
    inorder_traversal(root->left);
    printf("%d ", root->data);
    inorder_traversal(root->right);
}

/**
 * Preorder traversal (Root, Left, Right)
 */
void preorder_traversal(TreeNode* root) {
    if (root == NULL) return;
    
    printf("%d ", root->data);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

/**
 * Postorder traversal (Left, Right, Root)
 */
void postorder_traversal(TreeNode* root) {
    if (root == NULL) return;
    
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    printf("%d ", root->data);
}

/**
 * Level order traversal (Breadth-First)
 */
void level_order_traversal(TreeNode* root) {
    if (root == NULL) return;
    
    // Create queue for BFS
    TreeNode* queue[MAX_SIZE];
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        TreeNode* current = queue[front++];
        printf("%d ", current->data);
        
        if (current->left) {
            queue[rear++] = current->left;
        }
        if (current->right) {
            queue[rear++] = current->right;
        }
    }
}

/**
 * Calculate tree height
 */
int tree_height(TreeNode* root) {
    if (root == NULL) return 0;
    
    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);
    
    return (left_height > right_height ? left_height : right_height) + 1;
}

/**
 * Count total nodes
 */
int count_nodes(TreeNode* root) {
    if (root == NULL) return 0;
    
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

/**
 * Count leaf nodes
 */
int count_leaves(TreeNode* root) {
    if (root == NULL) return 0;
    
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    
    return count_leaves(root->left) + count_leaves(root->right);
}

/**
 * Search for a value in tree
 */
bool search_tree(TreeNode* root, int value) {
    if (root == NULL) return false;
    
    if (root->data == value) return true;
    
    return search_tree(root->left, value) || search_tree(root->right, value);
}

/**
 * Search in BST (optimized)
 */
bool search_bst(TreeNode* root, int value) {
    if (root == NULL) return false;
    
    if (root->data == value) return true;
    
    if (value < root->data) {
        return search_bst(root->left, value);
    } else {
        return search_bst(root->right, value);
    }
}

/**
 * Find maximum value in tree
 */
int find_max(TreeNode* root) {
    if (root == NULL) return INT_MIN;
    
    int max_val = root->data;
    int left_max = find_max(root->left);
    int right_max = find_max(root->right);
    
    if (left_max > max_val) max_val = left_max;
    if (right_max > max_val) max_val = right_max;
    
    return max_val;
}

/**
 * Find minimum value in tree
 */
int find_min(TreeNode* root) {
    if (root == NULL) return INT_MAX;
    
    int min_val = root->data;
    int left_min = find_min(root->left);
    int right_min = find_min(root->right);
    
    if (left_min < min_val) min_val = left_min;
    if (right_min < min_val) min_val = right_min;
    
    return min_val;
}

/**
 * Check if tree is a BST
 */
bool is_bst_util(TreeNode* root, int min, int max) {
    if (root == NULL) return true;
    
    if (root->data <= min || root->data >= max) {
        return false;
    }
    
    return is_bst_util(root->left, min, root->data) &&
           is_bst_util(root->right, root->data, max);
}

bool is_bst(TreeNode* root) {
    return is_bst_util(root, INT_MIN, INT_MAX);
}

/**
 * Convert tree back to array representation
 */
void tree_to_array_util(TreeNode* root, int arr[], int index, int size) {
    if (root == NULL || index >= size) return;
    
    arr[index] = root->data;
    
    tree_to_array_util(root->left, arr, 2*index + 1, size);
    tree_to_array_util(root->right, arr, 2*index + 2, size);
}

int* tree_to_array(Tree* tree) {
    if (!tree || !tree->root) return NULL;
    
    int* arr = (int*)malloc(tree->size * sizeof(int));
    if (!arr) return NULL;
    
    // Initialize with INT_MIN (indicates null nodes)
    for (int i = 0; i < tree->size; i++) {
        arr[i] = INT_MIN;
    }
    
    tree_to_array_util(tree->root, arr, 0, tree->size);
    return arr;
}

/**
 * Print array representation
 */
void print_array(int arr[], int size) {
    printf("Array representation: [");
    for (int i = 0; i < size; i++) {
        if (arr[i] == INT_MIN) {
            printf("null");
        } else {
            printf("%d", arr[i]);
        }
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

/**
 * Print tree structure (visual)
 */
void print_tree_visual_util(TreeNode* root, int space) {
    if (root == NULL) return;
    
    // Increase distance between levels
    space += 10;
    
    // Process right child first
    print_tree_visual_util(root->right, space);
    
    // Print current node
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);
    
    // Process left child
    print_tree_visual_util(root->left, space);
}

void print_tree_visual(TreeNode* root) {
    printf("\nTree Structure (rotated 90° clockwise):\n");
    printf("--------------------------------------\n");
    print_tree_visual_util(root, 0);
}

/**
 * Free tree memory
 */
void free_tree(TreeNode* root) {
    if (root == NULL) return;
    
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/**
 * Free entire tree structure
 */
void free_tree_structure(Tree* tree) {
    if (!tree) return;
    
    free_tree(tree->root);
    free(tree);
}

/**
 * Main function to demonstrate tree creation from array
 */
int main() {
    printf("=== TREE CREATION FROM ARRAY ===\n\n");
    
    printf("Test 1: Complete Binary Tree from Array\n");
    printf("=======================================\n");
    
    // Array representation of a complete binary tree
    // INT_MIN represents null nodes
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size1 = 10;
    
    printf("Input array: ");
    for (int i = 0; i < size1; i++) printf("%d ", arr1[i]);
    printf("\n");
    
    Tree* tree1 = build_tree_from_array(arr1, size1);
    
    printf("\nTree Traversals:\n");
    printf("Inorder:   "); inorder_traversal(tree1->root); printf("\n");
    printf("Preorder:  "); preorder_traversal(tree1->root); printf("\n");
    printf("Postorder: "); postorder_traversal(tree1->root); printf("\n");
    printf("Levelorder:"); level_order_traversal(tree1->root); printf("\n");
    
    printf("\nTree Properties:\n");
    printf("Height: %d\n", tree_height(tree1->root));
    printf("Total nodes: %d\n", count_nodes(tree1->root));
    printf("Leaf nodes: %d\n", count_leaves(tree1->root));
    printf("Max value: %d\n", find_max(tree1->root));
    printf("Min value: %d\n", find_min(tree1->root));
    
    printf("\nSearch operations:\n");
    printf("Search 5: %s\n", search_tree(tree1->root, 5) ? "Found" : "Not found");
    printf("Search 15: %s\n", search_tree(tree1->root, 15) ? "Found" : "Not found");
    
    // Convert back to array
    int* reconstructed_arr = tree_to_array(tree1);
    print_array(reconstructed_arr, size1);
    free(reconstructed_arr);
    
    print_tree_visual(tree1->root);
    
    printf("\nTest 2: Tree with NULL nodes\n");
    printf("=============================\n");
    
    int arr2[] = {1, 2, 3, INT_MIN, 4, INT_MIN, 5, INT_MIN, INT_MIN, 6};
    int size2 = 10;
    
    printf("Input array with null nodes:\n");
    print_array(arr2, size2);
    
    Tree* tree2 = build_tree_from_array(arr2, size2);
    
    printf("\nLevel order traversal: ");
    level_order_traversal(tree2->root);
    printf("\n");
    
    printf("Height: %d\n", tree_height(tree2->root));
    printf("Total nodes: %d\n", count_nodes(tree2->root));
    
    print_tree_visual(tree2->root);
    
    printf("\nTest 3: BST from Sorted Array\n");
    printf("=============================\n");
    
    int sorted_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sorted_size = 10;
    
    printf("Sorted array: ");
    for (int i = 0; i < sorted_size; i++) printf("%d ", sorted_arr[i]);
    printf("\n");
    
    Tree* bst = build_bst_from_sorted_array(sorted_arr, sorted_size);
    
    printf("\nBST Traversals:\n");
    printf("Inorder (should be sorted): ");
    inorder_traversal(bst->root);
    printf("\n");
    
    printf("Preorder:  ");
    preorder_traversal(bst->root);
    printf("\n");
    
    printf("Levelorder:");
    level_order_traversal(bst->root);
    printf("\n");
    
    printf("\nBST Properties:\n");
    printf("Height: %d (balanced BST)\n", tree_height(bst->root));
    printf("Is BST? %s\n", is_bst(bst->root) ? "Yes" : "No");
    
    printf("\nBST Search (optimized):\n");
    printf("Search 7: %s\n", search_bst(bst->root, 7) ? "Found" : "Not found");
    printf("Search 12: %s\n", search_bst(bst->root, 12) ? "Found" : "Not found");
    
    printf("\nTest 4: BST Validation\n");
    printf("=====================\n");
    
    // Create a non-BST tree
    int non_bst_arr[] = {5, 3, 7, 2, 8, 4, 6}; // Not a BST (8 > 5 but in left subtree)
    int non_bst_size = 7;
    
    Tree* non_bst = build_tree_from_array(non_bst_arr, non_bst_size);
    
    printf("Tree structure (not a BST):\n");
    printf("Level order: ");
    level_order_traversal(non_bst->root);
    printf("\n");
    
    printf("Is BST? %s\n", is_bst(non_bst->root) ? "Yes" : "No");
    
    printf("\nTest 5: Edge Cases\n");
    printf("==================\n");
    
    // Empty tree
    int empty_arr[] = {};
    Tree* empty_tree = build_tree_from_array(empty_arr, 0);
    printf("Empty tree height: %d\n", tree_height(empty_tree->root));
    printf("Empty tree nodes: %d\n", count_nodes(empty_tree->root));
    
    // Single node tree
    int single_arr[] = {42};
    Tree* single_tree = build_tree_from_array(single_arr, 1);
    printf("\nSingle node tree:\n");
    printf("Inorder: "); inorder_traversal(single_tree->root); printf("\n");
    printf("Height: %d\n", tree_height(single_tree->root));
    
    // Clean up
    free_tree_structure(tree1);
    free_tree_structure(tree2);
    free_tree_structure(bst);
    free_tree_structure(non_bst);
    free_tree_structure(empty_tree);
    free_tree_structure(single_tree);
    
    printf("\n=== PROGRAM COMPLETED ===\n");
    
    return 0;
}
