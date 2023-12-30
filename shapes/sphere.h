#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"
#include "../vector/vector.h"
#include "../utils.h"

typedef struct sphere
{
    double radius_;
    vector* center_;
} Sphere;


double sphere_intersect(vector* p0, vector* dr, Sphere * sphere);
void sphere_normal(vector* dest, vector* pi, Sphere * sphere);
void sphere_cordinates_transformation(matrix* transformation_matrix, Sphere * sphere);
Sphere* sphere_copy(Sphere* dest, Sphere* src);
Sphere sphere_create(vector* center, double radius, Color* color);
void sphere_delete(Sphere* sphere);

double sphere_intersect(vector* p0, vector* dr, Sphere * sphere) {
    double t1, t2, a, b, c, delta;

    vector* w = vector_create_empty(THREE_DIM);
    vector_sub(w, p0, sphere->center_);

    a = vector_dot(dr, dr);
    b = 2 * (vector_dot(w, dr));
    c = vector_dot(w, w) - pow(sphere->radius_, 2);

    vector_delete(w);
    
    delta = pow(b, 2) - 4 * a * c;

    if (delta < 0) {
        return INFINITY;
    }

    t1 = (-b + sqrt(delta))/ (2 * a);
    t2 = (-b - sqrt(delta))/ (2 * a);

    return min(t1, t2);
}

void sphere_normal(vector* dest, vector* pi, Sphere * sphere){
    vector_sub(dest, pi, sphere->center_);
    vector_scale(dest, dest, 1/sphere->radius_);
}

void sphere_cordinates_transformation(matrix* transformation_matrix, Sphere * sphere) {
    vector* aux_center = vector_create(FOUR_DIM, 
                                        VECTOR_AT(sphere->center_, 0), 
                                        VECTOR_AT(sphere->center_, 1), 
                                        VECTOR_AT(sphere->center_, 2), 1);
    vector* new_center = vector_create_empty(FOUR_DIM);

    matrix_vec_mul(new_center, transformation_matrix, aux_center);

    free(aux_center);
    if (sphere->center_ != NULL) {
        free(sphere->center_);
    }

    sphere->center_ = vector_create(FOUR_DIM, 
                                        VECTOR_AT(new_center, 0), 
                                        VECTOR_AT(new_center, 1), 
                                        VECTOR_AT(new_center, 2), 1);
    free(new_center);
}

Sphere* sphere_copy(Sphere* dest, Sphere* src) {
    memcpy(dest, src, sizeof(Sphere));
    dest->center_ = vector_create_empty(src->center_->n);
    vector_copy(dest->center_, src->center_);
    return dest;
}

Sphere sphere_create(vector* center, double radius, Color* color){

    Sphere sphere = {
        .center_ = center,
        .radius_ = radius
    };

    return sphere;
}

void sphere_delete(Sphere* sphere) {
    vector_delete(sphere->center_);
    free(sphere);
}




#endif