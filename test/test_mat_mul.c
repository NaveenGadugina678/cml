#include "mat/mat.h"
#include "helpers.h"

void test_mat_mul_square(void) {
    Mat a = {.rows = 2, .cols = 2, (float[]) {
        1, 2,
        3, 4,
    }};
    Mat b = {.rows = 2, .cols = 2, (float[]) {
        1, 2,
        3, 4,
    }};
    Mat exp = {.rows = 2, .cols = 2, (float[]) {
        7, 10,
        15, 22,
    }};
    Mat dst = {.rows = 2, .cols = 2, (float[4]){0}};
    // set it up
    // run 
    // assert
    mat_mul(dst, a, b);

    assert(mat_eq(dst, exp)); 
}

void test_mat_mul_rect(void) {
    Mat a = {.rows = 3, .cols = 1, (float[]) {
        1,
        2,
        3,
    }};
    Mat b = {.rows = 1, .cols = 4, (float[]) {
        1, 2, 3, 4,
    }};
    Mat exp = {.rows = 3, .cols = 4, (float[]) {
        1, 2, 3, 4,
        2, 4, 6, 8,
        3, 6, 9, 12,  
    }};
    Mat dst = {.rows = 3, .cols = 4, (float[3 * 4]){0}};
    
    mat_mul(dst, a, b);
    
    assert(mat_eq(dst, exp)); 
}

int main(void) {
    test_mat_mul_square();
    test_mat_mul_rect();

    return 0;
}
