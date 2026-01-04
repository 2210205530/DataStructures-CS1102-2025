#ifndef HANOI_H
#define HANOI_H

void hanoi_recursive(int n, char from, char to, char aux, int *move_count);
void hanoi_iterative(int n);
int calculate_min_moves(int n);

#endif
