#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int row;
    int col;
    int value;
} Element;

typedef struct {
    int rows;
    int cols;
    int num_non_zero;
    Element data[MAX_SIZE];
} SparseMatrix;

// Function declarations
SparseMatrix* create_sparse(int rows, int cols);
void insert_element(SparseMatrix* matrix, int row, int col, int value);
SparseMatrix* transpose_sparse(SparseMatrix* matrix);
SparseMatrix* add_sparse(SparseMatrix* a, SparseMatrix* b);
void print_sparse(SparseMatrix* matrix);
void free_sparse(SparseMatrix* matrix);

#endif
