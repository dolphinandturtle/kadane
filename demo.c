#include <stdio.h>
#include "include/kadane.h"

int main(void) {
    printf("Greatest sum in segment: %d\n", kadane_1d(7, (int[]){1, 1, -2, 3, -2, 1, 1}));
    printf("Greatest sum in loop: %d\n", kadane_loop_1d(7, (int[]){1, 1, -2, 3, -2, 1, 1}));

    printf("Greatest sum in segment: %d\n", kadane_1d(7, (int[]){1, 1, -3, 3, -3, 1, 1}));
    printf("Greatest sum in loop: %d\n", kadane_loop_1d(7, (int[]){1, 1, -3, 3, -3, 1, 1}));

    int M[6][6] = {
        { +1,  +1,  +1,  +1,  +1,  +1},
        { +1, -10, -10, -10, -10,  +1},
        { +1, -10, +10, +10, -10,  +1},
        { +1, -10, +10, +10, -10,  +1},
        { +1, -10, -10, -10, -10,  +1},
        { +1,  +1,  +1,  +1,  +1,  +1},
    };

    printf("Greatest boxed sum: %d\n", kadane_nd(2, (size_t []){6, 6}, (int*)M));

    int T[4][4][4] = {
        {{-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}},
        {{-1, -1, -1, -1}, {-1, +1, +1, -1}, {-1, +1, +1, -1}, {-1, -1, -1, -1}},
        {{-1, -1, -1, -1}, {-1, +1, +1, -1}, {-1, +1, +1, -1}, {-1, -1, -1, -1}},
        {{-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}},
    };
    printf("Greatest boxed sum: %d\n", kadane_nd(3, (size_t []){4, 4, 4}, (int*)T));

    return 0;
}
