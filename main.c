#include <stdio.h>
#include "vector/vector.h"

int main(){

    vector* vec = vector3d_create(2, 1, 3);
    vector* vec2 = vector3d_create(4, 3, 5);
    vector* dest = vector3d_create_empty();

    printf("about to add \n");
    vector3d_add(dest, vec, vec2);
    printf("%f %f %f\n", VECTOR_AT(dest, 0), VECTOR_AT(dest, 1), VECTOR_AT(dest, 2));
    
    printf("about to sub \n");
    vector3d_sub(dest, vec, vec2);
    printf("%f %f %f\n", VECTOR_AT(dest, 0), VECTOR_AT(dest, 1), VECTOR_AT(dest, 2));
    
    printf("about to scale \n");
    vector3d_scale(dest, vec, 3);
    printf("%f %f %f\n", VECTOR_AT(dest, 0), VECTOR_AT(dest, 1), VECTOR_AT(dest, 2));
    
    printf("about to mul \n");
    vector3d_mul(dest, vec, vec2);
    printf("%f %f %f\n", VECTOR_AT(dest, 0), VECTOR_AT(dest, 1), VECTOR_AT(dest, 2));
    
    printf("about to div \n");
    vector3d_div(dest, vec, vec2);
    printf("%f %f %f\n", VECTOR_AT(dest, 0), VECTOR_AT(dest, 1), VECTOR_AT(dest, 2));
   
    printf("about to norm \n");
    vector3d_normalize(dest, vec);
    printf("%f %f %f\n", VECTOR_AT(dest, 0), VECTOR_AT(dest, 1), VECTOR_AT(dest, 2));
   
    vector_delete(dest);
    vector_delete(vec);
    vector_delete(vec2);
  
    return 0;
}