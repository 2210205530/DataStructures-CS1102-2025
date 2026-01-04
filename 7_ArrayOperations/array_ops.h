/**
 *student name [meseud hadis redi]
 *student id[2210205530]
 */

#ifndef ARRAY_OPS_H
#define ARRAY_OPS_H

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2

// Dynamic Array structure
typedef struct {
    int* data;
    int size;
    int capacity;
} DynamicArray;

// Function declarations
DynamicArray* create_array();
void resize_if_needed(DynamicArray* arr);
void insert_at_end(DynamicArray* arr, int value);
void insert_at_beginning(DynamicArray* arr, int value);
int insert_at_position(DynamicArray* arr, int value, int position);
int delete_from_end(DynamicArray* arr);
int delete_from_beginning(DynamicArray* arr);
int delete_from_position(DynamicArray* arr, int position);
int delete_by_value(DynamicArray* arr, int value);
int search(DynamicArray* arr, int value);
int get_at_position(DynamicArray* arr, int position);
int update_at_position(DynamicArray* arr, int position, int new_value);
void reverse_array(DynamicArray* arr);
void sort_array(DynamicArray* arr);
void remove_duplicates(DynamicArray* arr);
void rotate_left(DynamicArray* arr, int k);
void rotate_right(DynamicArray* arr, int k);
DynamicArray* merge_sorted_arrays(DynamicArray* arr1, DynamicArray* arr2);
void print_array(DynamicArray* arr);
int get_size(DynamicArray* arr);
void free_array(DynamicArray* arr);

#endif
