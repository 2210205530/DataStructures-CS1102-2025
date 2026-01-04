/**
 * file test_sparse.c
 * brief Test cases for sparse matrix implementation
 */

#include "sparse_matrix.h"
#include <assert.h>

void test_create_and_insert() {
    printf("Test 1: Create and insert elements... ");
    
    SparseMatrix* m = create_sparse(3, 3);
    assert(m != NULL);
    assert(m->rows == 3);
    assert(m->cols == 3);
    assert(m->num_non_zero == 0);
    
    insert_element(m, 0, 0, 1);
    insert_element(m, 1, 1, 2);
    insert_element(m, 2, 2, 3);
    
    assert(m->num_non_zero == 3);
    assert(m->data[0].value == 1);
    assert(m->data[1].value == 2);
    assert(m->data[2].value == 3);
    
    free_sparse(m);
    printf("PASS\n");
}

void test_transpose() {
    printf("Test 2: Transpose matrix... ");
    
    SparseMatrix* m = create_sparse(2, 3);
    insert_element(m, 0, 1, 5);
    insert_element(m, 1, 0, 8);
    insert_element(m, 1, 2, 9);
    
    SparseMatrix* t = transpose_sparse(m);
    assert(t != NULL);
    assert(t->rows == 3);
    assert(t->cols == 2);
    assert(t->num_non_zero == 3);
    
    // Verify transposed values
    int found[3] = {0};
    for (int i = 0; i < t->num_non_zero; i++) {
        if (t->data[i].row == 1 && t->data[i].col == 0 && t->data[i].value == 5) found[0] = 1;
        if (t->data[i].row == 0 && t->data[i].col == 1 && t->data[i].value == 8) found[1] = 1;
        if (t->data[i].row == 2 && t->data[i].col == 1 && t->data[i].value == 9) found[2] = 1;
    }
    assert(found[0] && found[1] && found[2]);
    
    free_sparse(m);
    free_sparse(t);
    printf("PASS\n");
}

void test_addition() {
    printf("Test 3: Add two matrices... ");
    
    SparseMatrix* a = create_sparse(2, 2);
    SparseMatrix* b = create_sparse(2, 2);
    
    insert_element(a, 0, 0, 1);
    insert_element(a, 1, 1, 2);
    
    insert_element(b, 0, 0, 3);
    insert_element(b, 1, 1, 4);
    
    SparseMatrix* c = add_sparse(a, b);
    assert(c != NULL);
    assert(c->num_non_zero == 2);
    
    // Check values
    assert(c->data[0].row == 0 && c->data[0].col == 0 && c->data[0].value == 4);
    assert(c->data[1].row == 1 && c->data[1].col == 1 && c->data[1].value == 6);
    
    free_sparse(a);
    free_sparse(b);
    free_sparse(c);
    printf("PASS\n");
}

void test_edge_cases() {
    printf("Test 4: Edge cases... ");
    
    // Test invalid dimensions
    SparseMatrix* m1 = create_sparse(-1, 5);
    assert(m1 == NULL);
    
    // Test out of bounds insert
    SparseMatrix* m2 = create_sparse(2, 2);
    insert_element(m2, 5, 5, 10); 
    assert(m2->num_non_zero == 0);
    
    // Test NULL matrix
    insert_element(NULL, 0, 0, 1); 
    
    free_sparse(m2);
    printf("PASS\n");
}

int main() {
    printf("\n=== Testing Sparse Matrix Implementation ===\n\n");
    
    test_create_and_insert();
    test_transpose();
    test_addition();
    test_edge_cases();
    
    printf("\n All sparse matrix tests passed!\n");
    return 0;
}
