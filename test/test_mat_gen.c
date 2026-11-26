#include "mat/mat.h"
#include "helpers.h"

float one(void) {return 1.0f;}

void test_mat_fun_ones(void) {
    Mat a = {.rows = 2, .cols = 2, (float[4]){0}};
    Mat exp = {2, 2, (float[4]){
        1, 1,
        1, 1,
    }};

    mat_gen(a, one);

    assert(mat_eq(a, exp));
}

int main(void) {
    test_mat_fun_ones();
    return 0;
}
