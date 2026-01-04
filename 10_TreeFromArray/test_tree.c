/**
*student name [meseud hadis redi]
 *student id[2210205530]
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>

// Include the functions from tree_from_array.c
#include "tree_from_array.c"

/**
 * Test tree creation from array
 */
void test_tree_creation() {
    printf("Test 1: Tree creation from array... ");
    
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    
    Tree* tree = build_tree_from_array(arr, size);
    assert(tree != NULL);
    assert(tree->root != NULL);
    assert(tree->size == size);
    
    // Check root
    assert(tree->root->data == 1);
    
    // Check children
    assert(tree->root->left->data == 2);
    assert(tree->root->right->data == 3);
    
    // Check grandchildren
    assert(tree->root->left->left->data == 4);
    assert(tree->root->left->right->data == 5);
    
    free_tree_structure(tree);
    printf("PASS\n");
}

/**
 * Test BST creation from sorted array
 */
void test_bst_creation() {
    printf("Test 2: BST creation from sorted array... ");
    
    int sorted_arr[] = {1, 2, 3, 4, 5, 6, 7};
    int size = 7;
    
    Tree* bst = build_bst_from_sorted_array(sorted_arr, size);
    assert(bst != NULL);
    assert(bst->root != NULL);
    
    // Check BST property (root should be middle element)
    assert(bst->root->data == 4);
    
    // Check left subtree (should contain 1,2,3)
    assert(bst->root->left->data == 2);
    assert(bst->root->left->left->data == 1);
    assert(bst->root->left->right->data == 3);
    
    // Check right subtree (should contain 5,6,7)
    assert(bst->root->right->data == 6);
    assert(bst->root->right->left->data == 5);
    assert(bst->root->right->right->data == 7);
    
    // Verify BST property
    assert(is_bst(bst->root) == true);
    
    free_tree_structure(bst);
    printf("PASS\n");
}

/**
 * Test tree traversals
 */
void test_traversals() {
    printf("Test 3: Tree traversals... ");
    
    // Create a simple tree: 1
    //                    /   \
    //                   2     3
    //                  / \
    //                 4   5
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    
    Tree* tree = build_tree_from_array(arr, size);
    
    // Test inorder (should be 4 2 5 1 3)
    printf("\n  Inorder test: ");
    inorder_traversal(tree->root);
    
    // Test preorder (should be 1 2 4 5 3)
    printf("\n  Preorder test: ");
    preorder_traversal(tree->root);
    
    // Test postorder (should be 4 5 2 3 1)
    printf("\n  Postorder test: ");
    postorder_traversal(tree->root);
    
    // Test level order (should be 1 2 3 4 5)
    printf("\n  Levelorder test: ");
    level_order_traversal(tree->root);
    
    free_tree_structure(tree);
    printf("\n  PASS\n");
}

/**
 * Test tree properties
 */
void test_tree_properties() {
    printf("Test 4: Tree properties... ");
    
    // Tree: 1
    //      / \
    //     2   3
    //    /   / \
    //   4   5   6
    int arr[] = {1, 2, 3, 4, INT_MIN, 5, 6};
    int size = 7;
    
    Tree* tree = build_tree_from_array(arr, size);
    
    // Test height (should be 3)
    assert(tree_height(tree->root) == 3);
    
    // Test node count (should be 6)
    assert(count_nodes(tree->root) == 6);
    
    // Test leaf count (should be 3: nodes 4, 5, 6)
    assert(count_leaves(tree->root) == 3);
    
    // Test max value (should be 6)
    assert(find_max(tree->root) == 6);
    
    // Test min value (should be 1)
    assert(find_min(tree->root) == 1);
    
    free_tree_structure(tree);
    printf("PASS\n");
}

/**
 * Test search operations
 */
void test_search() {
    printf("Test 5: Search operations... ");
    
    int arr[] = {10, 5, 15, 3, 7, 12, 18};
    int size = 7;
    
    Tree* tree = build_tree_from_array(arr, size);
    
    // Test search in general tree
    assert(search_tree(tree->root, 7) == true);
    assert(search_tree(tree->root, 12) == true);
    assert(search_tree(tree->root, 99) == false);
    
    // Create a BST for optimized search
    int sorted_arr[] = {1, 2, 3, 4, 5, 6, 7};
    Tree* bst = build_bst_from_sorted_array(sorted_arr, 7);
    
    // Test BST search
    assert(search_bst(bst->root, 4) == true);
    assert(search_bst(bst->root, 7) == true);
    assert(search_bst(bst->root, 10) == false);
    
    free_tree_structure(tree);
    free_tree_structure(bst);
    printf("PASS\n");
}

/**
 * Test BST validation
 */
void test_bst_validation() {
    printf("Test 6: BST validation... ");
    
    // Create a BST
    int bst_arr[] = {4, 2, 6, 1, 3, 5, 7};
    int bst_size = 7;
    Tree* bst = build_tree_from_array(bst_arr, bst_size);
    assert(is_bst(bst->root) == true);
    
    // Create a non-BST
    int non_bst_arr[] = {1, 2, 3, 4, 5}; 
    int non_bst_size = 5;
    Tree* non_bst = build_tree_from_array(non_bst_arr, non_bst_size);
    assert(is_bst(non_bst->root) == false);
    
    free_tree_structure(bst);
    free_tree_structure(non_bst);
    printf("PASS\n");
}

/**
 * Test tree to array conversion
 */
void test_tree_to_array() {
    printf("Test 7: Tree to array conversion... ");
    
    // Original array
    int original_arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    
    // Build tree from array
    Tree* tree = build_tree_from_array(original_arr, size);
    
    // Convert back to array
    int* reconstructed_arr = tree_to_array(tree);
    assert(reconstructed_arr != NULL);
    
    // Compare with original
    for (int i = 0; i < size; i++) {
        assert(reconstructed_arr[i] == original_arr[i]);
    }
    
    free(reconstructed_arr);
    free_tree_structure(tree);
    printf("PASS\n");
}

/**
 * Test edge cases
 */
void test_edge_cases() {
    printf("Test 8: Edge cases... ");
    
    // Test empty tree
    int empty_arr[] = {};
    Tree* empty_tree = build_tree_from_array(empty_arr, 0);
    assert(empty_tree != NULL);
    assert(empty_tree->root == NULL);
    assert(tree_height(empty_tree->root) == 0);
    assert(count_nodes(empty_tree->root) == 0);
    free_tree_structure(empty_tree);
    
    // Test single node
    int single_arr[] = {42};
    Tree* single_tree = build_tree_from_array(single_arr, 1);
    assert(single_tree->root->data == 42);
    assert(tree_height(single_tree->root) == 1);
    assert(count_nodes(single_tree->root) == 1);
    assert(count_leaves(single_tree->root) == 1);
    free_tree_structure(single_tree);
    
    // Test tree with null nodes
    int null_arr[] = {1, INT_MIN, 2, INT_MIN, INT_MIN, 3};
    Tree* null_tree = build_tree_from_array(null_arr, 6);
    assert(null_tree->root->data == 1);
    assert(null_tree->root->left == NULL);
    assert(null_tree->root->right->data == 2);
    assert(null_tree->root->right->right->data == 3);
    free_tree_structure(null_tree);
    
    printf("PASS\n");
}

/**
 * Test memory management
 */
void test_memory_management() {
    printf("Test 9: Memory management... ");
    
    // Create large tree
    int large_arr[100];
    for (int i = 0; i < 100; i++) {
        large_arr[i] = i;
    }
    
    Tree* large_tree = build_tree_from_array(large_arr, 100);
    assert(large_tree != NULL);
    assert(count_nodes(large_tree->root) == 100);
    
    // Free should not crash
    free_tree_structure(large_tree);
    
    printf("PASS\n");
}

/**
 * Test visual print (just verify it doesn't crash)
 */
void test_visual_print() {
    printf("Test 10: Visual print (no crash)... ");
    
    int arr[] = {1, 2, 3, 4, 5};
    Tree* tree = build_tree_from_array(arr, 5);
    
    // Just verify function doesn't crash
    print_tree_visual(tree->root);
    
    free_tree_structure(tree);
    printf("PASS\n");
}

/**
 * Main test runner
 */
int main() {
    printf("\n=== TESTING TREE CREATION FROM ARRAY ===\n\n");
    
    test_tree_creation();
    test_bst_creation();
    test_traversals();
    test_tree_properties();
    test_search();
    test_bst_validation();
    test_tree_to_array();
    test_edge_cases();
    test_memory_management();
    test_visual_print();
    
    printf("\n=== ALL TESTS PASSED ===\n\n");
    
    printf("To run the main program:\n");
    printf("1. cd 10_TreeFromArray\n");
    printf("2. gcc -o tree_from_array tree_from_array.c\n");
    printf("3. ./tree_from_array\n");
    
    return 0;
}
