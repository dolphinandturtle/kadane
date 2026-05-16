#include <assert.h>
#include <stddef.h>
#include <limits.h>
#include "iter.h"


static inline int max(int a, int b) {
    return (a > b) ? a : b;
}

int kadane_1d(size_t n, int a[n]) {
    int xmax = INT_MIN;
    int x = 0;
    for (int i = 0; i < n; i++) {
        x = max(a[i], x + a[i]);
        xmax = max(xmax, x);
    }
    return xmax;
}

int kadane_loop_1d(size_t n, int a[n]) {
    int xmax = INT_MIN;
    int xl = 0, x = 0, xr = 0;
    for (int i = 0, j = 0; i + j < n; (xl < xr) ? i++ : j++) {
        xl = max(a[(n-1)-j], x + a[(n-1)-j]);
        xr = max(a[i], x + a[i]);
        x = max(xl, xr);
        xmax = max(xmax, x);
    }
    return xmax;
}

static void zero_1d(size_t n, int a[n]) {
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
        zero_1d(n, acc);
        for (int r = l; r < m; r++) {
            add1d(n, acc, M[r]);
            xmax = max(kadane_1d(n, acc), xmax);
        }
    }
    return xmax;
}

int kadane_loop_2d(size_t m, size_t n, int M[m][n]) {
    int xmax = INT_MIN;
    int acc[n];
    for (int l = 0; l < m; l++) {
        zero_1d(n, acc);
        for (int r = l; r < m + l; r++) {
            add1d(n, acc, M[r % m]);
            xmax = max(kadane_loop_1d(n, acc), xmax);
        }
    }
    return xmax;
}

static void zero_nd(size_t n, size_t dim[n], int* T) {
    size_t index[n];
    for (int i = 0; i < n; i++) {
        index[i] = 0;
    }
    for (
        struct MultiIndex x = multi_index_init(n, index, dim);
        multi_index_conditional(&x);
        multi_index_iteration(&x)
    ) {
        T[multi_index_flatten(&x)] = 0;
    }
    return;
}

static void add_nd(size_t n, size_t dim[n], int* T, int* U) {
    size_t index[n];
    for (int i = 0; i < n; i++) {
        index[i] = 0;
    }
    for (
        struct MultiIndex x = multi_index_init(n, index, dim);
        multi_index_conditional(&x);
        multi_index_iteration(&x)
    ) {
        T[multi_index_flatten(&x)] += U[multi_index_flatten(&x)];
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

int kadane_loop_nd(size_t n, size_t dim[n], int* T) {
    int xmax = INT_MIN;

    // The accumulator becomes a higher order tensor
    int prod = 1;
    for (int i = 1; i < n; i++) {
        prod *= dim[i];
    }
    int acc[prod];

    for (int l = 0; l < dim[0]; l++) {
        zero_nd(n - 1, dim + 1, acc);
        for (int r = l; r < dim[0] + l; r++) {
            add_nd(n - 1, dim + 1, acc, T + (r % dim[0]) * prod);
            if (n == 2) {
                xmax = max(kadane_loop_1d(prod, acc), xmax);
            }
            else {
                xmax = max(kadane_loop_nd(n - 1, dim + 1, acc), xmax);
            }
        }
    }
    return xmax;
}
