cmake_minimum_required(VERSION 4.0)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)

add_executable(RayTracing main.cpp
        Vector3.cpp
        Vector3.h
        Camera.cpp
        Camera.h
        Ray.cpp
        Ray.h
        RaycastHit.cpp
        RaycastHit.h
        SceneObject.cpp
        SceneObject.h
        ColorRGB.cpp
        ColorRGB.h
)
