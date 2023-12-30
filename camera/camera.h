#ifndef CAMERA_H
#define CAMERA_H

#include "../vector/vector.h"

typedef struct camera {
    vector4d eye;
    vector4d up;
    vector4d at;
    vector3d vup;
    vector3d kc;
    vector3d ic;
    vector3d jc;
} Camera;


void camera_calculate_wc_mat(matrix4d* wc_dest, matrix4d* cw_dest, Camera* camera);
void camera_generate_wc_and_cw_mat(matrix4d* wc_dest, matrix4d* cw_dest, Camera* camera);

void camera_calculate_wc_mat(matrix4d* wc_dest, matrix4d* cw_dest, Camera* camera)  {

    vector3d vup = vector3d_create_empty();
    vector3d kc = vector3d_create_empty();
    vector3d ic = vector3d_create_empty();
    vector3d jc = vector3d_create_empty();

    // eye -> up vector
    vector3d_sub(&vup, (vector3d *)&camera->up, (vector3d *)&camera->eye);
    vector3d_normalize(&vup, &vup);
    // at -> eye direction (camera coordinates z)
    vector3d_sub(&kc, (vector3d *)&camera->eye, (vector3d *)&camera->at);
    vector3d_normalize(&kc, &kc);

    // (camera coordinates x)
    vector3d_crossproduct(&ic, &vup, &kc);

    // (camera coordinates y)
    vector3d_crossproduct(&jc, &kc, &ic);

    vector3d_normalize(&ic, &ic);
    vector3d_normalize(&jc, &jc);

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


void camera_generate_wc_and_cw_mat(matrix4d* wc_dest, matrix4d* cw_dest, Camera* camera) {

    VECTOR_TYPE z1, z2, z3;
    z1 = -vector3d_dot(&camera->ic, (vector3d *)&camera->eye);
    z2 = -vector3d_dot(&camera->jc, (vector3d *)&camera->eye);
    z3 = -vector3d_dot(&camera->kc, (vector3d *)&camera->eye);

    {
        VECTOR_TYPE elements[16] = {
            VECTOR_AT(&camera->ic, 0), VECTOR_AT(&camera->ic, 1), VECTOR_AT(&camera->ic, 2),  z1,    
            VECTOR_AT(&camera->jc, 0), VECTOR_AT(&camera->jc, 1), VECTOR_AT(&camera->jc, 2),  z2,  
            VECTOR_AT(&camera->kc, 0), VECTOR_AT(&camera->kc, 1), VECTOR_AT(&camera->kc, 2),  z3,
            0.0, 0.0, 0.0, 1.0
        };

        matrix_set(wc_dest, elements);  
    }
   

    VECTOR_TYPE elements[16] = {
            VECTOR_AT(&camera->ic, 0), VECTOR_AT(&camera->jc, 0), VECTOR_AT(&camera->kc, 0),  VECTOR_AT(&camera->eye, 0),    
            VECTOR_AT(&camera->ic, 1), VECTOR_AT(&camera->jc, 1), VECTOR_AT(&camera->kc, 1),  VECTOR_AT(&camera->eye, 1),  
            VECTOR_AT(&camera->ic, 2), VECTOR_AT(&camera->jc, 2), VECTOR_AT(&camera->kc, 2),  VECTOR_AT(&camera->eye, 2),
            0.0, 0.0, 0.0, 1.0
    };

    matrix_set(cw_dest, elements);
}



#endif