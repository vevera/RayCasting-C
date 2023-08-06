#ifndef VECTOR_H
#define VECTOR_H

#define vec_type double
#define THREE_DIM 3
#define FOUR_DIM 4

#include <stdlib.h>
#include <math.h>

typedef struct vector {
    char n;
    vec_type* data_;
} vector;

#define VECTOR_AT(vec, where) (vec)->data_[(where)]

//Vector 3d 
vector* vector3d_create_empty();
vector* vector3d_create(vec_type a, vec_type b, vec_type c);
void vector3d_set(vector* vec, vec_type* elements, char vec_size);
void vector3d_print(vector* vector);
void vector_delete(vector* source);
void vector3d_add(vector* dest, vector* source1, vector* source2);
void vector3d_sub(vector* dest, vector* source1, vector* source2);
void vector3d_mul(vector* dest, vector* source1, vector* source2);
void vector3d_scale(vector* dest, vector* source1, double source2);
void vector3d_div(vector* dest, vector* source1, vector* source2);
void vector3d_normalize(vector* dest, vector* source);
void vector3d_crossproduct(vector* dest, vector* source1, vector* source2);
double vector3d_lenght(vector* source1);
vec_type vector3d_dot(vector* source1, vector* source2);


//Vector 3d 
vector* vector3d_create_empty() {
    vector* vec = vector3d_create(0, 0, 0);
    return vec;
}

vector* vector3d_create(vec_type a, vec_type b, vec_type c) {
    vector* vec = (vector*)malloc(sizeof(vector));
    vec->data_ = (vec_type*)malloc(THREE_DIM * sizeof(vec_type));
    vec->n = THREE_DIM;
    vec->data_[0] = a;
    vec->data_[1] = b;
    vec->data_[2] = c;
    return vec;
}

void vector3d_set(vector* vec, vec_type* elements, char vec_size) {
    for (char i = 0; i < vec_size; i++){
        VECTOR_AT(vec, i) = elements[i];
    }
}

void vector3d_print(vector* vector) {
    printf("(%f, %f, %f)\n", VECTOR_AT(vector, 0), 
            VECTOR_AT(vector, 1),VECTOR_AT(vector, 2));
}

void vector_delete(vector* source){
    free(source->data_);
    free(source);
}

void vector3d_add(vector* dest, vector* source1, vector* source2){
    for (char i=0; i<THREE_DIM; ++i) {
        VECTOR_AT(dest, i) = VECTOR_AT(source1, i) + VECTOR_AT(source2, i);
    }
}
void vector3d_sub(vector* dest, vector* source1, vector* source2){
    for (char i=0; i<THREE_DIM; ++i) {
        VECTOR_AT(dest, i) = VECTOR_AT(source1, i) - VECTOR_AT(source2, i);
    }
}
void vector3d_mul(vector* dest, vector* source1, vector* source2){
    for (char i=0; i<THREE_DIM; ++i) {
        VECTOR_AT(dest, i) = VECTOR_AT(source1, i) * VECTOR_AT(source2, i);
    }
}
void vector3d_scale(vector* dest, vector* source1, double source2){
    for (char i=0; i<THREE_DIM; ++i) {
        VECTOR_AT(dest, i) = VECTOR_AT(source1, i) * source2;
    }
}
void vector3d_div(vector* dest, vector* source1, vector* source2){
    for (char i=0; i<THREE_DIM; ++i) {
        VECTOR_AT(dest, i) = VECTOR_AT(source1, i) / VECTOR_AT(source2, i);
    }
}
void vector3d_normalize(vector* dest, vector* source){
    vector3d_scale(dest, source, 1/vector3d_lenght(source));
}

void vector3d_crossproduct(vector* dest, vector* source1, vector* source2){

}

double vector3d_lenght(vector* source1){
    vec_type dot_prod = vector3d_dot(source1, source1);
    return sqrt(dot_prod);
}

vec_type vector3d_dot(vector* source1, vector* source2){
    vec_type ret = 0;
    for (char i=0; i<THREE_DIM; ++i) {
        ret += VECTOR_AT(source1, i) * VECTOR_AT(source2, i);
    }
    return ret;
}

#endif