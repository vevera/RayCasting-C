#ifndef MATRIX_H
#define MATRIX_H

#include "vector4d.h"

typedef struct matrix4d {
    vector4d r1;
    vector4d r2;
    vector4d r3;
    vector4d r4;
} matrix4d;

#define MATRIX_AT(matrix, r, c) ((VECTOR_TYPE *)(matrix))[(r * FOUR_DIM + c)]

// Matrix 
matrix4d matrix_create_empty();
matrix4d matrix_create(VECTOR_TYPE initializer_elements[16]);
void matrix_print(matrix4d* matrix);
void matrix_set(matrix4d* matrix, VECTOR_TYPE elements[16]);
void matrix_mul(matrix4d* dest, matrix4d* src_1, matrix4d* src_2);
void matrix_vec_mul(vector4d* dest, matrix4d* src_m, vector4d* src_v);

// Matrix
matrix4d matrix_create_empty() {
    matrix4d mat;
    memset(&mat, 0, sizeof(matrix4d));
    return mat;
}

matrix4d matrix_create(VECTOR_TYPE initializer_elements[16]) {
    matrix4d mat;
    memcpy(&mat, initializer_elements, sizeof(matrix4d));
    return mat;
}

void matrix_print(matrix4d* matrix) {
    char i, j;
    for (i = 0; i < FOUR_DIM; i++) {
        for (j = 0; j < FOUR_DIM; j++) {
            printf("|%f", MATRIX_AT(matrix, i, j));
        }
        printf("\n");
    }
}

void matrix_set(matrix4d* matrix, VECTOR_TYPE elements[16]){
    memcpy(matrix, elements, sizeof(matrix4d));
}

void matrix_mul(matrix4d* dest, matrix4d* src_1, matrix4d* src_2) {
    VECTOR_TYPE sum = 0.0;
    char i, j, k;
    for (i = 0; i < FOUR_DIM; i++) {
        for (j = 0; j < FOUR_DIM; j++) {
            sum = 0.0;
            for (k = 0; k < FOUR_DIM; k++){
                sum = sum + MATRIX_AT(src_1, i, k) * MATRIX_AT(src_2, k, j);
            }
            MATRIX_AT(dest, i, j) = sum;
        }
    }
}

void matrix_vec_mul(vector4d* dest, matrix4d* src_m, vector4d* src_v) {
    VECTOR_TYPE sum = 0.0;
    char i, j;
    for (i = 0; i < FOUR_DIM; i++) {
        sum = 0.0;
        for (j = 0; j < FOUR_DIM; j++) {
            sum = sum + MATRIX_AT(src_m, i, j) * VECTOR_AT(src_v, j);
        }
        VECTOR_AT(dest, i) = sum;
    }
}

#endif