#ifndef CAMERA_H
#define CAMERA_H

#include "../vector/vector.h"

typedef struct camera {
    vector* eye;
    vector* up;
    vector* at;
    vector* vup;
    vector* kc;
    vector* ic;
    vector* jc;
} Camera;


void camera_calculate_wc_mat(matrix* wc_dest, matrix* cw_dest, Camera* camera);
void camera_generate_wc_and_cw_mat(matrix* wc_dest, matrix* cw_dest, Camera* camera);

void camera_calculate_wc_mat(matrix* wc_dest, matrix* cw_dest, Camera* camera)  {

    vector* vup = vector_create_empty(THREE_DIM);
    vector* kc = vector_create_empty(THREE_DIM);
    vector* ic = vector_create_empty(THREE_DIM);
    vector* jc = vector_create_empty(THREE_DIM);

    // eye -> up vector
    vector_sub(vup, camera->up, camera->eye);
    vector_normalize(vup, vup);
    // at -> eye direction (camera coordinates z)
    vector_sub(kc, camera->eye, camera->at);
    vector_normalize(kc, kc);

    // (camera coordinates x)
    vector3_crossproduct(ic, vup, kc);

    // (camera coordinates y)
    vector3_crossproduct(jc, kc, ic);

    vector_normalize(ic, ic);
    vector_normalize(jc, jc);

    camera->vup = vup;
    camera->kc = kc;
    camera->ic = ic;
    camera->jc = jc;

    camera_generate_wc_and_cw_mat(wc_dest, cw_dest, camera);
    
    // vec_type z1, z2, z3;
    // z1 = -vector_dot(ic, camera->eye);
    // z2 = -vector_dot(jc, camera->eye);
    // z3 = -vector_dot(kc, camera->eye);

    // matrix_set(wc_dest, 
    //             VECTOR_AT(ic, 0), VECTOR_AT(ic, 1), VECTOR_AT(ic, 2),  z1,    
    //             VECTOR_AT(jc, 0), VECTOR_AT(jc, 1), VECTOR_AT(jc, 2),  z2,  
    //             VECTOR_AT(kc, 0), VECTOR_AT(kc, 1), VECTOR_AT(kc, 2),  z3,
    //             0.0, 0.0, 0.0, 1.0);  


    // matrix_set(cw_dest, 
    //             VECTOR_AT(ic, 0), VECTOR_AT(jc, 0), VECTOR_AT(kc, 0),  VECTOR_AT(camera->eye, 0),    
    //             VECTOR_AT(ic, 1), VECTOR_AT(jc, 1), VECTOR_AT(kc, 1),  VECTOR_AT(camera->eye, 1),  
    //             VECTOR_AT(ic, 2), VECTOR_AT(jc, 2), VECTOR_AT(kc, 2),  VECTOR_AT(camera->eye, 2),
    //             0.0, 0.0, 0.0, 1.0);

    // vector_delete(vup);
    // vector_delete(kc);
    // vector_delete(ic);
    // vector_delete(jc);
}


void camera_generate_wc_and_cw_mat(matrix* wc_dest, matrix* cw_dest, Camera* camera) {

    vec_type z1, z2, z3;
    z1 = -vector_dot(camera->ic, camera->eye);
    z2 = -vector_dot(camera->jc, camera->eye);
    z3 = -vector_dot(camera->kc, camera->eye);

    matrix_set(wc_dest, 
                VECTOR_AT(camera->ic, 0), VECTOR_AT(camera->ic, 1), VECTOR_AT(camera->ic, 2),  z1,    
                VECTOR_AT(camera->jc, 0), VECTOR_AT(camera->jc, 1), VECTOR_AT(camera->jc, 2),  z2,  
                VECTOR_AT(camera->kc, 0), VECTOR_AT(camera->kc, 1), VECTOR_AT(camera->kc, 2),  z3,
                0.0, 0.0, 0.0, 1.0);  


    matrix_set(cw_dest, 
                VECTOR_AT(camera->ic, 0), VECTOR_AT(camera->jc, 0), VECTOR_AT(camera->kc, 0),  VECTOR_AT(camera->eye, 0),    
                VECTOR_AT(camera->ic, 1), VECTOR_AT(camera->jc, 1), VECTOR_AT(camera->kc, 1),  VECTOR_AT(camera->eye, 1),  
                VECTOR_AT(camera->ic, 2), VECTOR_AT(camera->jc, 2), VECTOR_AT(camera->kc, 2),  VECTOR_AT(camera->eye, 2),
                0.0, 0.0, 0.0, 1.0);
}



#endif