#include <stddef.h>
#include <stdbool.h>

struct MultiIndex {
    size_t* index;
    size_t* range;
    size_t  count;
    size_t  i;
};

void print_row(size_t n, size_t a[n]);
void print_matrix(size_t m, size_t n, size_t M[m][n]);

struct MultiIndex multi_index_init(size_t count, size_t index[count], size_t range[count]);
size_t multi_index_flatten(struct MultiIndex* loop);
bool multi_index_conditional(struct MultiIndex* loop);
void multi_index_iteration(struct MultiIndex* loop);
