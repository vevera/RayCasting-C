#include "vector/vector3d.h" 
#include "vector/vector4d.h"
#include "vector/matrix.h"


int main(void) {

    printf("ola mundo!\n");

    vector3d vec1 = vector3d_create(1, 2, 3);
    vector3d vec2 = vector3d_create(3, 4, 5);

    vector3d vec3 = vector3d_create_empty();
    vector4d vec55 = vector4d_create(1, 2, 3, 4);


    VECTOR_TYPE max = VECTOR3D_MAX(vec1);
    printf("The max value is: %f\n", max);

    VECTOR_TYPE a[] = {2, 3, 3};
    vector3d_add(&vec3, (vector3d* )&vec55, &vec2);

    printf("sum: \n ");
    vector3d_print(&vec3);

    printf("matrix tests: \n");

    vector4d vec4 = vector4d_create(1, 2, 3, 4);

    VECTOR_TYPE elements[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    matrix4d matrix = matrix_create(elements);
    matrix4d matrix1 = matrix_create_empty();
    vector4d vec5 = vector4d_create_empty();

    matrix_vec_mul(&vec5, &matrix, &vec4);
    matrix_print(&matrix);

    vector4d_print(&vec5);


    // matrix4d matrix_create_empty();
    // matrix4d matrix_create(VECTOR_TYPE initializer_elements[16]);
    // void matrix_print(matrix4d* matrix);
    // void matrix_set(matrix4d* matrix, VECTOR_TYPE elements[16]);
    // void matrix_mul(matrix4d* dest, matrix4d* src_1, matrix4d* src_2);
    // void matrix_vec_mul(vector4d* dest, matrix4d* src_m, vector4d* src_v);

    // vector4d vec5 = vector4d_create(5, 6, 7, 8);

    // vector4d vec6 = vector4d_create_empty();

    // vector4d_add(&vec6, &vec4, &vec5);
    // vector4d_print(&vec6);
    // vector4d_sub(&vec6, &vec4, &vec5);
    // vector4d_print(&vec6);
    // vector4d_mul(&vec6, &vec4, &vec5);
    // vector4d_print(&vec6);
    // vector4d_div(&vec6, &vec4, &vec5);
    // vector4d_print(&vec6);
    // vector4d_scale(&vec6, &vec4, 2);
    // vector4d_print(&vec6);
    // vector4d_normalize(&vec6, &vec4);
    // vector4d_print(&vec6);

    // void vector4d_set(vector4d* vec, VECTOR_TYPE* elements);
    // void vector4d_reset(vector4d* vector4d);
    // void vector4d_print(vector4d* vector);
    // void vector4d_add(vector4d* dest, vector4d* source1, vector4d* source2);
    // void vector4d_sub(vector4d* dest, vector4d* source1, vector4d* source2);
    // void vector4d_mul(vector4d* dest, vector4d* source1, vector4d* source2);
    // void vector4d_scale(vector4d* dest, vector4d* source1, double source2);
    // void vector4d_div(vector4d* dest, vector4d* source1, vector4d* source2);
    // void vector4d_normalize(vector4d* dest, vector4d* source);
    // double vector4d_lenght(vector4d* source1);
    // VECTOR_TYPE vector4d_dot(vector4d* source1, vector4d* source2);



    return 0;


}