#include <stdio.h>
#include "../src/loop.h"


void zero_nd(size_t n, size_t dim[n], size_t* T) {
    size_t index[n];
    for (int i = 0; i < n; i++) {
        index[i] = 0;
    }
    for (
        struct MultiIndex loop = multi_index_init(n, index, dim);
        multi_index_conditional(&loop);
        multi_index_iteration(&loop)
    ) {
        T[multi_index_flatten(&loop)] = 0;
    }
    return;
}

void add_nd(size_t n, size_t dim[n], size_t* T, size_t* U) {
    size_t index[n];
    for (int i = 0; i < n; i++) {
        index[i] = 0;
    }
    for (
        struct MultiIndex loop = multi_index_init(n, index, dim);
        multi_index_conditional(&loop);
        multi_index_iteration(&loop)
    ) {
        T[multi_index_flatten(&loop)] += U[multi_index_flatten(&loop)];
    }
    return;
}

int main(void) {
    size_t M[4][2] = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    };
    size_t U[4][2] = {
        {8, 7},
        {6, 5},
        {4, 3},
        {2, 1}
    };
    add_nd(2, (size_t[]){4, 2}, (size_t*)M, (size_t*)U);
    print_matrix(4, 2, M);
    zero_nd(2, (size_t[]){4, 2}, (size_t*)M);
    print_matrix(4, 2, M);
}
