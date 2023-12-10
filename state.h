#ifndef STATE_H
#define STATE_H

#include "vector/vector.h"
#include "scene/scene.h"
#include "camera/camera.h"

typedef struct state {

    Scene* scene;
    Camera* camera;
    double vp_h;
    double vp_w;
    double vp_z;
    vector* background_color;
    vector* eye;
    matrix* cw;
    matrix* wc;
} State; 

#endif