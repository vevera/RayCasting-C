#ifndef VECTOR_H
#define VECTOR_H

#define vec_type double
#define THREE_DIM 3
#define FOUR_DIM 4

#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>

typedef struct vector {
    char n;
    vec_type* data_;
} vector;

typedef struct matrix {
    char n;
    char m;
    vec_type* data_;
} matrix;

#define VECTOR_AT(vec, where) (vec)->data_[(where)]
#define MATRIX_AT(matrix, r, c) (matrix)->data_[(r * (matrix)->m + c)]

//Vector 3d 
vector* vector_create_empty();
vector* vector_create(vec_type a, vec_type b, vec_type c);
void vector_set(vector* vec, vec_type* elements);
void vector_reset(vector* vector);
void vector_print(vector* vector);
void vector_delete(vector* source);
void vector_add(vector* dest, vector* source1, vector* source2);
void vector_sub(vector* dest, vector* source1, vector* source2);
void vector_mul(vector* dest, vector* source1, vector* source2);
void vector_scale(vector* dest, vector* source1, double source2);
void vector_div(vector* dest, vector* source1, vector* source2);
void vector_normalize(vector* dest, vector* source);
void vector3_crossproduct(vector* dest, vector* source1, vector* source2);
double vector_lenght(vector* source1);
vec_type vector_dot(vector* source1, vector* source2);
vec_type vector_max(vector* vector);

//Vector 3d 
vector* vector_create_empty() {
    vector* vec = vector_create(0, 0, 0);
    vec->n = THREE_DIM;
    return vec;
}

vector* vector_create(vec_type a, vec_type b, vec_type c) {
    vector* vec = (vector*)malloc(sizeof(vector));
    vec->data_ = (vec_type*)malloc(THREE_DIM * sizeof(vec_type));
    vec->n = THREE_DIM;
    vec->data_[0] = a;
    vec->data_[1] = b;
    vec->data_[2] = c;
    return vec;
}

void vector_set(vector* vec, vec_type* elements) {
    for (char i = 0; i < vec->n; i++){
        VECTOR_AT(vec, i) = elements[i];
    }
}

void vector_reset(vector* vector){
    vec_type zeros[] = {0, 0, 0};
    vector_set(vector, zeros);
}

void vector_print(vector* vector) {
    printf("(%f, %f, %f)\n", VECTOR_AT(vector, 0), 
            VECTOR_AT(vector, 1),VECTOR_AT(vector, 2));
}

void vector_delete(vector* source){
    free(source->data_);
    free(source);
}

void vector_add(vector* dest, vector* source1, vector* source2){
    for (char i=0; i<dest->n; ++i) {
        VECTOR_AT(dest, i) = VECTOR_AT(source1, i) + VECTOR_AT(source2, i);
    }
}
void vector_sub(vector* dest, vector* source1, vector* source2){
    for (char i=0; i<dest->n; ++i) {
        VECTOR_AT(dest, i) = VECTOR_AT(source1, i) - VECTOR_AT(source2, i);
    }
}
void vector_mul(vector* dest, vector* source1, vector* source2){
    for (char i=0; i<dest->n; ++i) {
        VECTOR_AT(dest, i) = VECTOR_AT(source1, i) * VECTOR_AT(source2, i);
    }
}
void vector_scale(vector* dest, vector* source1, double source2){
    for (char i=0; i<dest->n; ++i) {
        VECTOR_AT(dest, i) = VECTOR_AT(source1, i) * source2;
    }
}
void vector_div(vector* dest, vector* source1, vector* source2){
    for (char i=0; i<dest->n; ++i) {
        VECTOR_AT(dest, i) = VECTOR_AT(source1, i) / VECTOR_AT(source2, i);
    }
}
void vector_normalize(vector* dest, vector* source){
    vector_scale(dest, source, 1/vector_lenght(source));
}

void vector3_crossproduct(vector* dest, vector* source1, vector* source2){
    VECTOR_AT(dest, 0) = VECTOR_AT(source1, 1) * VECTOR_AT(source2, 2) - 
                            VECTOR_AT(source1, 2) * VECTOR_AT(source2, 1);

    VECTOR_AT(dest, 1) = VECTOR_AT(source1, 2) * VECTOR_AT(source2, 0) - 
                            VECTOR_AT(source1, 0) * VECTOR_AT(source2, 2);
                            
    VECTOR_AT(dest, 2) = VECTOR_AT(source1, 0) * VECTOR_AT(source2, 1) - 
                            VECTOR_AT(source1, 1) * VECTOR_AT(source2, 0);                                                
}

double vector_lenght(vector* source1){
    vec_type dot_prod = vector_dot(source1, source1);
    return sqrt(dot_prod);
}

vec_type vector_dot(vector* source1, vector* source2){
    vec_type ret = 0;
    for (char i=0; i<THREE_DIM; ++i) {
        ret += (VECTOR_AT(source1, i) * VECTOR_AT(source2, i));
    }
    return ret;
}

vec_type vector_max(vector* vector){
    vec_type max = -INFINITY;
    for (char i = 0; i < vector->n; i++){
        if (VECTOR_AT(vector, i) > max) {
            max = VECTOR_AT(vector, i);
        }
    }
    return max;
}

// Matrix 
matrix* matrix_create_empty(char n, char m);
matrix* matrix_create(char n, char m, ...);
void matrix_delete(matrix* matrix);
void matrix_print(matrix* matrix);
void matrix_set(matrix* matrix, ...);

void matrix_mul(matrix* dest, matrix* src_1, matrix* src_2);
void matrix_vec_mul(vector* dest, matrix* src_m, vector* src_v);
// Matrix

matrix* matrix_create_empty(char n, char m) {
    matrix* mat = (matrix*)malloc(sizeof(matrix));
    mat->n = n;
    mat->m = m;
    mat->data_ = (vec_type*)malloc(sizeof(vec_type)*n*m);

    return mat;
}

matrix* matrix_create(char n, char m, ...){

    char n_args = n * m;

    va_list args;
    va_start(args, m);
    
    matrix* mat = matrix_create_empty(n, m);

    for (char i = 0; i < n_args; i++) {
        mat->data_[i] = va_arg(args, vec_type);
    }

    va_end(args);
    return mat;
}

void matrix_delete(matrix* matrix) {
    free(matrix->data_);
    free(matrix);
}

void matrix_print(matrix* matrix) {
    for (char i = 0; i < matrix->n; i++) {
        for (char j = 0; j < matrix->m; j++) {
            printf("|%f", MATRIX_AT(matrix, i, j));
        }
        printf("\n");
    }
}

void matrix_set(matrix* matrix, ...){

    char n_args = matrix->n * matrix->m;

    va_list args;
    va_start(args, matrix);

    for (char i = 0; i < n_args; i++) {
        matrix->data_[i] = va_arg(args, vec_type);
    }

    va_end(args);
}

void matrix_mul(matrix* dest, matrix* src_1, matrix* src_2) {
    vec_type sum = 0.0;

    for (char i = 0; i < src_1->n; i++) {
        for (char j = 0; j < src_2->m; j++) {
            sum = 0.0;
            for (char k = 0; k < src_1->n; k++){
                sum = sum + MATRIX_AT(src_1, i, k) * MATRIX_AT(src_2, k, j);
            }
            MATRIX_AT(dest, i, j) = sum;
        }
    }
}

void matrix_vec_mul(vector* dest, matrix* src_m, vector* src_v) {
    vec_type sum = 0.0;
    for (char i = 0; i < src_m->n; i++) {
        sum = 0.0;
        for (char j = 0; j < src_m->m; j++) {
            sum = sum + MATRIX_AT(src_m, i, j) * VECTOR_AT(src_v, j);
        }
        VECTOR_AT(dest, i) = sum;
    }
}


#endif