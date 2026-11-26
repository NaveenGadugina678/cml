#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "mat/mat.h"
#include <time.h>

#define MAT_NEW(rows, cols) {rows, cols, (float[(rows) * (cols)]) {}}

float randf(void) {
    return 2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f;
}

float sigmoid(float val) { return 1.0f / (1.0f + expf(-val)); }

int main() {
    srand(2);
    puts("\nXOR Neural Network\n");
    
    // TRAINING DATA
    Mat xs = {4, 2, (float[]) {
        0, 0,
        1, 0,
        0, 1,
        1, 1,
    }};

    Mat ys = {4, 1, (float[]) {
        0,
        1,
        1,
        0,
    }};
    
    // CREATE MATRICES 
    Mat a0  = MAT_NEW(4, 3);
    Mat w0  = MAT_NEW(3, 2);
    Mat dw0 = MAT_NEW(3, 2);
    Mat z0  = MAT_NEW(4, 2);

    Mat a1  = MAT_NEW(4, 3);
    Mat w1  = MAT_NEW(3, 1);
    Mat dw1 = MAT_NEW(3, 1);
    Mat z1  = MAT_NEW(4, 1);

    Mat a2  = MAT_NEW(4, 1);

    // INIT RANDOM WEIGHTS
    mat_gen(w0, randf);
    mat_gen(w1, randf);

    // SET BIAS
    mat_set(a0, 1.0f);
    mat_set(a1, 1.0f);
    
    // SET INPUT
    mat_cpy(a0, xs);

    float eps = 1e-2f;
    float alpha = 1e-1f;
    size_t EPOCHS = 50001;
    for (size_t epoch = 1 ; epoch < EPOCHS ; ++epoch) {

        // FORWARD PASS
        mat_mul(z0, a0, w0);
        mat_fun(a1, z0, sigmoid);
        mat_mul(z1, a1, w1);
        mat_fun(a2, z1, sigmoid);
        float loss;
        mat_mse(&loss, a2, ys);

        // NUMERICAL GRADIENTS
        for (size_t i = 0 ; i < w0.rows * w0.cols ; ++i) {
            float orig_w = w0.data[i];

            w0.data[i] += eps;

            // FORWARD PASS
            mat_mul(z0, a0, w0);
            mat_fun(a1, z0, sigmoid);
            mat_mul(z1, a1, w1);
            mat_fun(a2, z1, sigmoid);
            float new_loss;
            mat_mse(&new_loss, a2, ys);

            dw0.data[i] = (new_loss - loss) / eps; // Gradient

            w0.data[i] = orig_w;
        }
        for (size_t i = 0 ; i < w1.rows * w1.cols ; ++i) {
            float orig_w = w1.data[i];

            w1.data[i] += eps;

            // FORWARD PASS
            mat_mul(z0, a0, w0);
            mat_fun(a1, z0, sigmoid);
            mat_mul(z1, a1, w1);
            mat_fun(a2, z1, sigmoid);
            float new_loss;
            mat_mse(&new_loss, a2, ys);

            dw1.data[i] = (new_loss - loss) / eps; // Gradient

            w1.data[i] = orig_w;
        }

        // GRADIENT DESCENT
        for (size_t i = 0 ; i < w0.rows * w0.cols ; ++i) {
            w0.data[i] -= alpha * dw0.data[i]; 
        }
        for (size_t i = 0 ; i < w1.rows * w1.cols ; ++i) {
            w1.data[i] -= alpha * dw1.data[i]; 
        }
        
        mat_mse(&loss, a2, ys);
        if (epoch % 5000 == 0)
            printf("loss after %5zu epochs: %.4f\n", epoch, loss);
    }

    // PRINTING STUFF
    printf("\noutput:\n");
    mat_print(a2);
    printf("\ntarget:\n");
    mat_print(ys);

    return 0;
}
