#ifndef LIGHT_H
#define LIGHT_H

#include "../vector/vector.h"
#include "../shapes/shape.h"
#include "../utils.h"

typedef struct light {
    vector* position_;
    vector* intensity_;
    void (*calc_light_contribution)(vector* output, Color* color_,
                                                vector* l, vector* n, 
                                                vector* v, vector* r, struct light *light);
    void (*calc_light_l_from_point_p)(vector* output, vector* p, struct light* light);
    double (*calc_light_distance_from_point_p)(vector* p, struct light *light);
    void* concrete_light_;
} Light;

typedef struct lightArray {
    Light** lights;
    int size_;
    int max_size_;
} LightArray;

void light_delete_light(Light* light);
void calc_light_diffuse_specular_contribution(vector* output, Color* color_, vector* intensity_,
                                                vector* l, vector* n, 
                                                vector* v, vector* r);
LightArray* light_create_light_array(int max_size);
void light_free_light_array(LightArray* lights);
void light_add_light_to_array(Light** light, LightArray* array);

//Implementation

void light_delete_light(Light* light) {
    if (light->concrete_light_ != NULL)
        free(light->concrete_light_);
    if (light != NULL)
        free(light);
}

void calc_light_diffuse_specular_contribution(  vector* output, Color* color_, 
                                                vector* intensity_,
                                                vector* l, vector* n, 
                                                vector* v, vector* r){
    vector* kd = color_->kd;
    vector* ke = color_->ke;  
   
    double shininess = color_->shininess;

    vector* id = vector_create_empty();
    vector* ie = vector_create_empty();

    double max_v;

    vector_mul(id, intensity_, kd);
    vector_scale(id, id, max(vector_dot(l, n), 0.0));

    vector_mul(ie, intensity_, ke);
    vector_scale(ie, ie, max(pow(vector_dot(v, r), shininess), 0.0));
    
    vector_add(output, id, ie);
 
    max_v = vector_max(output);
   
    if (max_v > 1.0)  {
        vector_scale(output, output, 1/max_v);
    }

    vector_delete(id);
    vector_delete(ie);                                      
}

LightArray* light_create_light_array(int max_size) {
    LightArray* array = (LightArray*)malloc(sizeof(LightArray));
    array->lights = (Light**)malloc(max_size * sizeof(Light*));
    array->size_ = 0;
    array->max_size_ = max_size;
}

void light_free_light_array(LightArray* lights) {

    for (int i = 0; i<lights->size_; i++){
        light_delete_light(lights->lights[i]);
    }

    free(lights->lights);
    free(lights);
}

void light_add_light_to_array(Light** light, LightArray* array) {
    if (array->size_ < array->max_size_) {
        array->lights[array->size_++] = *light;
    }
}

#endif