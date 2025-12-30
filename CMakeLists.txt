cmake_minimum_required(VERSION 4.0)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)

include_directories(Dev_SDL/include)
link_directories(Dev_SDL/lib)

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
        PointLight.cpp
        PointLight.h
        Plane.cpp
        Plane.h
        NullObject.cpp
        NullObject.h
        Renderer.cpp
        Renderer.h
        Scene.cpp
        Scene.h
        Sphere.cpp
        Sphere.h
        SceneLoader.cpp
        SceneLoader.h
        rapidxml-1.13/rapidxml.hpp
        rapidxml-1.13/rapidxml_iterators.hpp
        rapidxml-1.13/rapidxml_print.hpp
        rapidxml-1.13/rapidxml_utils.hpp
)
target_link_libraries(RayTracing SDL3)
