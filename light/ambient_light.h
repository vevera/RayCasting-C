#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "light.h"

Light light_create_ambient_light(vector* intensity);

void ambient_light_contribution(vector* output, Color* color_,
                                        vector* l, vector* n, 
                                        vector* v, vector* r, struct light *light);
void ambient_light_l_from_point_p(vector* output, vector* p, struct light* light);
double ambient_light_distance_from_point_p(vector* p, struct light *light);
void ambient_light_cordinates_tranformation(matrix* transformation_matrix, struct light* light) {};

//Implementation

Light light_create_ambient_light(vector*intensity) {
    Light light = {
        .position_ = NULL,
        .intensity_ = intensity,
        .calc_light_contribution = ambient_light_contribution,
        .calc_light_l_from_point_p = ambient_light_l_from_point_p,
        .calc_light_distance_from_point_p = ambient_light_distance_from_point_p,
        .light_cordinates_transformation = ambient_light_cordinates_tranformation,
        .concrete_light_ = NULL
    };

    return light;
}

void ambient_light_contribution(vector* output, Color* color_,
                                        vector* l, vector* n, 
                                        vector* v, vector* r, struct light *light) {
    vector* ka = color_->ka;
    vector_mul(output, light->intensity_, ka);                                       
}

void ambient_light_l_from_point_p(vector* output, vector* p, struct light* light) {  
    vector_reset(output);
}

double ambient_light_distance_from_point_p(vector* p, struct light *light) {
    return -1;
}

#endif