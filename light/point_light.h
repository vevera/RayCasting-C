#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "light.h"

Light* light_create_point_light(vector* position, vector*intensity);

void point_light_contribution(vector* output, Color* color_,
                                        vector* l, vector* n, 
                                        vector* v, vector* r, struct light *light);
void point_light_l_from_point_p(vector* output, vector* p, struct light* light);
double point_light_distance_from_point_p(vector* p, struct light *light);

//Implementation

Light* light_create_point_light(vector* position, vector*intensity) {
    Light* light = (Light*)malloc(sizeof(Light));
    light->position_ = position;
    light->intensity_ = intensity;
    light->calc_light_contribution = point_light_contribution;
    light->calc_light_l_from_point_p = point_light_l_from_point_p;
    light->calc_light_distance_from_point_p = point_light_distance_from_point_p;
    light->concrete_light_ = NULL;
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

#endif