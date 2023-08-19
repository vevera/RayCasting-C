#ifndef CAMERA_H
#define CAMERA_H

#include "../vector/vector.h"

void camera_calculate_wc_mat(matrix* wc_dest, vector* eye, vector* at, vector* up);


void camera_calculate_wc_mat(matrix* wc_dest, vector* eye, vector* at, vector* up)  {

    vector* vup = vector3d_create_empty();
    vector* kc = vector3d_create_empty();
    vector* ic = vector3d_create_empty();
    vector* jc = vector3d_create_empty();

    // eye -> up vector
    vector3d_sub(vup, up, eye);

    // at -> eye direction (camera coordinates z)
    vector3d_sub(kc, eye, at);
    vector3d_normalize(kc, kc);

    // (camera coordinates x)
    vector3d_crossproduct(ic, vup, kc);

    // (camera coordinates y)
    vector3d_crossproduct(jc, kc, ic);

    vec_type z1, z2, z3;
    z1 = -vector3d_dot(ic, eye);
    z2 = -vector3d_dot(jc, eye);
    z3 = -vector3d_dot(kc, eye);

    matrix_set(wc_dest, 
                VECTOR_AT(ic, 0), VECTOR_AT(ic, 1), VECTOR_AT(ic, 2),  z1,    
                VECTOR_AT(jc, 0), VECTOR_AT(jc, 1), VECTOR_AT(jc, 2),  z2,  
                VECTOR_AT(kc, 0), VECTOR_AT(kc, 1), VECTOR_AT(kc, 2),  z1,
                0.0, 0.0, 0.0, 1.0);  

    vector_delete(vup);
    vector_delete(kc);
    vector_delete(ic);
    vector_delete(jc);
}



#endif