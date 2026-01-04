/**
 *student name [meseud hadis redi]
 *student id[2210205530]
 */

#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_HEAP_SIZE 100

// Heap structure
typedef struct {
    int data[MAX_HEAP_SIZE];
    int size;
    int is_min_heap; // 1 for min-heap, 0 for max-heap
} Heap;

// Function declarations
Heap* create_heap(int is_min_heap);
int heap_insert(Heap* heap, int value);
int heap_delete_root(Heap* heap);
int heap_peek(Heap* heap);
int is_valid_heap(Heap* heap);
Heap* build_heap(int arr[], int n, int is_min_heap);
void heap_sort(int arr[], int n, int ascending);
void print_heap(Heap* heap);

#endif
