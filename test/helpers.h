#ifndef _TEST_HELPERS_H
#define _TEST_HELPERS_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "mat/mat.h"

static inline bool mat_eq(Mat a, Mat b) {
    if(a.rows != b.rows) {
        printf("rows mismatch, (a: %u != b: %u)", a.rows, b.rows);
        return false;
    }
    if(a.cols != b.cols){
        printf("cols mismatch, (a: %u != b: %u)", a.cols, b.cols);
        return false;
    }
    for (size_t i = 0 ; i < b.cols * b.rows ; ++i) {
        if(a.data[i] != b.data[i]) {
            printf("a:\n");
            mat_print(a);
            printf("b:\n");
            mat_print(b);
            printf("data mismatch @%zu, (dst: %f != exp: %f", i, a.data[i], b.data[i]);
            return false;
        }
    }

    return true;
}

#endif // _TEST_HELPERS_H
