[file name]: Sparse_matrix.c
[file content begin]
/**
*student name [meseud hadis redi]
 *student id[2210205530]
 * Time Complexity:
 *   - Transpose: O(n + cols) where n = non-zero elements
 *   - Addition: O(n1 + n2)
 * Space Complexity: O(n) for non-zero elements
 */

#include "sparse_matrix.h"
#include <assert.h>

/**
 * Creates a new sparse matrix
 */
SparseMatrix* create_sparse(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        fprintf(stderr, "Error: Invalid matrix dimensions\n");
        return NULL;
    }
    
    SparseMatrix* matrix = (SparseMatrix*)malloc(sizeof(SparseMatrix));
    if (!matrix) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->num_non_zero = 0;
    
    return matrix;
}

/**
 * Inserts an element into sparse matrix
 */
void insert_element(SparseMatrix* matrix, int row, int col, int value) {
    if (!matrix) {
        fprintf(stderr, "Error: Matrix is NULL\n");
        return;
    }
    
    if (row < 0 || row >= matrix->rows || col < 0 || col >= matrix->cols) {
        fprintf(stderr, "Error: Index out of bounds\n");
        return;
    }
    
    if (value == 0) {
        return; // Don't store zero values in sparse representation
    }
    
    if (matrix->num_non_zero >= MAX_SIZE) {
        fprintf(stderr, "Error: Sparse matrix is full\n");
        return;
    }
    
    // Insert maintaining row-major order
    int i;
    for (i = matrix->num_non_zero - 1; i >= 0; i--) {
        if (matrix->data[i].row > row || 
            (matrix->data[i].row == row && matrix->data[i].col > col)) {
            matrix->data[i + 1] = matrix->data[i];
        } else {
            break;
        }
    }
    
    matrix->data[i + 1].row = row;
    matrix->data[i + 1].col = col;
    matrix->data[i + 1].value = value;
    matrix->num_non_zero++;
}

/**
 * Transposes a sparse matrix
 */
SparseMatrix* transpose_sparse(SparseMatrix* matrix) {
    if (!matrix) return NULL;
    
    SparseMatrix* transposed = create_sparse(matrix->cols, matrix->rows);
    if (!transposed) return NULL;
    
    // Count non-zero elements in each column
    int* count = (int*)calloc(matrix->cols, sizeof(int));
    if (!count) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        free_sparse(transposed);
        return NULL;
    }
    
    for (int i = 0; i < matrix->num_non_zero; i++) {
        count[matrix->data[i].col]++;
    }
    
    // Calculate starting position for each column
    int* index = (int*)malloc(matrix->cols * sizeof(int));
    if (!index) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        free(count);
        free_sparse(transposed);
        return NULL;
    }
    
    index[0] = 0;
    for (int i = 1; i < matrix->cols; i++) {
        index[i] = index[i - 1] + count[i - 1];
    }
    
    // Place elements in transposed matrix
    for (int i = 0; i < matrix->num_non_zero; i++) {
        int col = matrix->data[i].col;
        int pos = index[col];
        
        transposed->data[pos].row = matrix->data[i].col;
        transposed->data[pos].col = matrix->data[i].row;
        transposed->data[pos].value = matrix->data[i].value;
        
        index[col]++;
        transposed->num_non_zero++;
    }
    
    free(count);
    free(index);
    return transposed;
}

SparseMatrix* add_sparse(SparseMatrix* a, SparseMatrix* b) {
    if (!a || !b) {
        fprintf(stderr, "Error: Matrix is NULL\n");
        return NULL;
    }
    
    if (a->rows != b->rows || a->cols != b->cols) {
        fprintf(stderr, "Error: Matrix dimensions don't match\n");
        return NULL;
    }
    
    SparseMatrix* result = create_sparse(a->rows, a->cols);
    if (!result) return NULL;
    
    int i = 0, j = 0;
    
    while (i < a->num_non_zero && j < b->num_non_zero) {
        int pos_a = a->data[i].row * a->cols + a->data[i].col;
        int pos_b = b->data[j].row * b->cols + b->data[j].col;
        
        if (pos_a < pos_b) {
            insert_element(result, a->data[i].row, a->data[i].col, a->data[i].value);
            i++;
        } else if (pos_a > pos_b) {
            insert_element(result, b->data[j].row, b->data[j].col, b->data[j].value);
            j++;
        } else {
            // Same position, add values
            int sum = a->data[i].value + b->data[j].value;
            if (sum != 0) {
                insert_element(result, a->data[i].row, a->data[i].col, sum);
            }
            i++;
            j++;
        }
    }
    
    // Add remaining elements from a
    while (i < a->num_non_zero) {
        insert_element(result, a->data[i].row, a->data[i].col, a->data[i].value);
        i++;
    }
    
    // Add remaining elements from b
    while (j < b->num_non_zero) {
        insert_element(result, b->data[j].row, b->data[j].col, b->data[j].value);
        j++;
    }
    
    return result;
}

/**
 * Prints sparse matrix in dense format
 */
void print_sparse(SparseMatrix* matrix) {
    if (!matrix) {
        printf("Matrix is NULL\n");
        return;
    }
    
    printf("Sparse Matrix (%dx%d), Non-zero: %d\n", 
           matrix->rows, matrix->cols, matrix->num_non_zero);
    
    // Create dense representation using dynamic allocation
    int** dense = (int**)malloc(matrix->rows * sizeof(int*));
    if (!dense) {
        printf("Error: Memory allocation failed\n");
        return;
    }
    
    for (int i = 0; i < matrix->rows; i++) {
        dense[i] = (int*)calloc(matrix->cols, sizeof(int));
        if (!dense[i]) {
            // Free already allocated rows
            for (int j = 0; j < i; j++) {
                free(dense[j]);
            }
            free(dense);
            printf("Error: Memory allocation failed\n");
            return;
        }
    }
    
    // Fill with non-zero values
    for (int i = 0; i < matrix->num_non_zero; i++) {
        dense[matrix->data[i].row][matrix->data[i].col] = matrix->data[i].value;
    }
    
    // Print dense matrix
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%4d", dense[i][j]);
        }
        printf("\n");
    }
    
    // Free allocated memory
    for (int i = 0; i < matrix->rows; i++) {
        free(dense[i]);
    }
    free(dense);
}

void free_sparse(SparseMatrix* matrix) {
    if (matrix) {
        free(matrix);
    }
}
[file content end]
