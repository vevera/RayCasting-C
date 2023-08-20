#ifndef CAMERA_H
#define CAMERA_H

#include "../vector/vector.h"

void camera_calculate_wc_mat(matrix* wc_dest, vector* eye, vector* at, vector* up);


void camera_calculate_wc_mat(matrix* wc_dest, vector* eye, vector* at, vector* up)  {

    vector* vup = vector_create_empty(THREE_DIM);
    vector* kc = vector_create_empty(THREE_DIM);
    vector* ic = vector_create_empty(THREE_DIM);
    vector* jc = vector_create_empty(THREE_DIM);

    // eye -> up vector
    vector_sub(vup, up, eye);

    // at -> eye direction (camera coordinates z)
    vector_sub(kc, eye, at);
    vector_normalize(kc, kc);

    // (camera coordinates x)
    vector3_crossproduct(ic, vup, kc);

    // (camera coordinates y)
    vector3_crossproduct(jc, kc, ic);

    vector_normalize(ic, ic);
    vector_normalize(jc, jc);

    vec_type z1, z2, z3;
    z1 = -vector_dot(ic, eye);
    z2 = -vector_dot(jc, eye);
    z3 = -vector_dot(kc, eye);

    matrix_set(wc_dest, 
                VECTOR_AT(ic, 0), VECTOR_AT(ic, 1), VECTOR_AT(ic, 2),  z1,    
                VECTOR_AT(jc, 0), VECTOR_AT(jc, 1), VECTOR_AT(jc, 2),  z2,  
                VECTOR_AT(kc, 0), VECTOR_AT(kc, 1), VECTOR_AT(kc, 2),  z3,
                0.0, 0.0, 0.0, 1.0);  

    vector_delete(vup);
    vector_delete(kc);
    vector_delete(ic);
    vector_delete(jc);
}



#endif