#include <assert.h>
#include <stddef.h>
#include <limits.h>
#include "loop.h"

static inline int max(int a, int b) {
    return (a > b) ? a : b;
}

int kadane_1d(size_t n, int a[n]) {
    int xmax = INT_MIN;
    int xi = 0;
    int xf = 0;
    for (int i = 0; i < n; i++) {
        xf = xi + a[i];
        xi = max(xf, a[i]);
        xmax = max(xmax, xi);
    }
    return xmax;
}

static void zero1d(size_t n, int a[n]) {
    for (int i = 0; i < n; i++) {
        a[i] = 0;
    }
    return;
}

static void add1d(size_t n, int a[n], const int b[n]) {
    for (int i = 0; i < n; i++) {
        a[i] += b[i];
    }
    return;
}

int kadane_2d(size_t m, size_t n, int M[m][n]) {
    int xmax = INT_MIN;
    int acc[n];
    for (int l = 0; l < m; l++) {
        zero1d(n, acc);
        for (int r = l; r < m; r++) {
            add1d(n, acc, M[r]);
            xmax = max(kadane_1d(n, acc), xmax);
        }
    }
    return xmax;
}

void zero_nd(size_t n, size_t dim[n], int* T) {
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

void add_nd(size_t n, size_t dim[n], int* T, int* U) {
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

int kadane_nd(size_t n, size_t dim[n], int* T) {
    int xmax = INT_MIN;

    // The accumulator becomes a higher order tensor
    int prod = 1;
    for (int i = 1; i < n; i++) {
        prod *= dim[i];
    }
    int acc[prod];

    for (int l = 0; l < dim[0]; l++) {
        zero_nd(n - 1, dim + 1, acc);
        for (int r = l; r < dim[0]; r++) {
            add_nd(n - 1, dim + 1, acc, T + r*prod);
            if (n == 2) {
                xmax = max(kadane_1d(prod, acc), xmax);
            }
            else {
                xmax = max(kadane_nd(n - 1, dim + 1, acc), xmax);
            }
        }
    }
    return xmax;
}
