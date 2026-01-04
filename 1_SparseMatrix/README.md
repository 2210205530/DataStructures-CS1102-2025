# Assignment 1: Sparse Matrix Transformation

## Overview
Implementation of sparse matrix operations using Compressed Sparse Row (CSR) format.

## Data Structure
```c
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
