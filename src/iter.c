#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "iter.h"


void print_row(size_t n, size_t a[n]) {
    printf("{");
    for (int i = 0; i < n - 1; i++) {
        printf("%d, ", a[i]);
    }
    printf("%d}\n", a[n - 1]);
    return;
}

void print_matrix(size_t m, size_t n, size_t M[m][n]) {
    for (int i = 0; i < m; i++) {
        printf("[");
        for (int j = 0; j < n - 1; j++) {
            printf("%d, ", M[i][j]);
        }
        printf("%d]\n", M[i][n-1]);
    }
    return;
}

static void zero(size_t n, size_t a[n]) {
    for (int i = 0; i < n; i++) {
        a[i] = 0;
    }
    return;
}

size_t multi_index_flatten(struct MultiIndex* loop) {
    size_t flat = 0;
    size_t offset = 1;
    for (int i = 0; i < loop->count; i++) {
        offset = 1;
        for (int j = i + 1; j < loop->count; j++) {
            offset *= loop->range[j];
        }
        flat += offset * loop->coord[i];
    }
    return flat;
}

struct MultiIndex multi_index_init(size_t count, size_t index[count], size_t range[count]) {
    return (struct MultiIndex){index, range, count, count - 1};
}

bool multi_index_conditional(struct MultiIndex* x) {
    while (1) {
        if (x->coord[x->i] == x->range[x->i]) {
            if (x-> i == 0) {
                return false;
            }
            else {
                x->coord[x->i] = 0;
                x->coord[--x->i]++;
            }
        }
        else if (x->i == x->count - 1) {
            return true;
        }
        else {
            x->i++;
        }
    }
}

void multi_index_iteration(struct MultiIndex* x) {
    x->coord[x->i]++;
    return;
}
