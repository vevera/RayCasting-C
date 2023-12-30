#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "light.h"

Light light_create_point_light(vector* position, vector* intensity);

void point_light_contribution(vector* output, Color* color_,
                                        vector* l, vector* n, 
                                        vector* v, vector* r, struct light *light);
void point_light_l_from_point_p(vector* output, vector* p, struct light* light);
double point_light_distance_from_point_p(vector* p, struct light *light);
void point_light_cordinates_transformation(matrix* transformation_matrix, struct light *light);


//Implementation
Light light_create_point_light(vector* position, vector* intensity) {
    Light light = {
        .position_ = position,
        .intensity_ = intensity,
        .calc_light_contribution = point_light_contribution,
        .calc_light_l_from_point_p = point_light_l_from_point_p,
        .calc_light_distance_from_point_p = point_light_distance_from_point_p,
        .light_cordinates_transformation = point_light_cordinates_transformation,
        .concrete_light_ = NULL
    };
    
    return light;
}

void point_light_contribution(vector* output, Color* color_,
                                        vector* l, vector* n, 
                                        vector* v, vector* r, struct light *light) {
    calc_light_diffuse_specular_contribution(output, color_, light->intensity_, l, n, v, r);                                       
}

void point_light_l_from_point_p(vector* output, vector* p, struct light* light) {
    vector_sub(output, light->position_, p);
    vector_normalize(output, output);
}

double point_light_distance_from_point_p(vector* p, struct light *light) {
    vector* dr = vector_create_empty(THREE_DIM);
    vector_sub(dr, light->position_, p);
    double lenght = vector_lenght(dr);
    vector_delete(dr);
    return lenght;
}

void point_light_cordinates_transformation(matrix* transformation_matrix, struct light *light) {
    vector* aux_position = vector_create(FOUR_DIM, 
                                        VECTOR_AT(light->position_, 0), 
                                        VECTOR_AT(light->position_, 1), 
                                        VECTOR_AT(light->position_, 2), 1);
    vector* new_position = vector_create_empty(FOUR_DIM);

    matrix_vec_mul(new_position, transformation_matrix, aux_position);

    vector_delete(aux_position);

    if (light->position_ != NULL) {
        vector_delete(light->position_);
    }

    light->position_ = vector_create(FOUR_DIM, 
                                        VECTOR_AT(new_position, 0), 
                                        VECTOR_AT(new_position, 1), 
                                        VECTOR_AT(new_position, 2), 1);
    vector_delete(new_position);
}

#endif