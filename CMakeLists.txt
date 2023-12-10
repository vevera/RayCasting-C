cmake_minimum_required(VERSION 3.7)
project(raycasting_c VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall")

find_package(SDL2 REQUIRED)

set(HEADER_FILES 

    camera/camera.h
    canvas/canvas.h
    light/light.h
    light/ambient_light.h
    light/point_light.h
    raytracing/ray_tracing.h
    scene/scene.h
    shapes/shape.h
    shapes/sphere.h
    vector/vector.h
    utils.h
)

include_directories(${SDL2_INCLUDE_DIRS})


add_executable(raycasting_c ${HEADER_FILES} main.c)
target_link_libraries(raycasting_c ${SDL2_LIBRARIES} m)