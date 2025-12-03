//
// Created by adyan on 03/12/2025.
//

#ifndef RAYTRACING_RAYCASTHIT_H
#define RAYTRACING_RAYCASTHIT_H
#include "Vector3.h"

class RaycastHit {

    // The distance the ray travelled before hitting an object
private:
    double distance;

    // The object that was hit by the ray
    SceneObject objectHit;

    // The location that the ray hit the object
    Vector3 location;

    // The normal of the object at the location hit by the ray
    Vector3 normal;

public:
    RaycastHit() {distance = POSITIVE_INFINITY;}

    RaycastHit(SceneObject objectHit, double distance, Vector3 location, Vector3 normal) :
        distance(distance),objectHit(objectHit),location(location),normal(normal) {}

    SceneObject getObjectHit() {return objectHit;}

    [[nodiscard]] Vector3 getLocation() const {return location;}

    [[nodiscard]] Vector3 getNormal() const {return normal;}

    [[nodiscard]] double getDistance() const {return distance;}
};



#endif //RAYTRACING_RAYCASTHIT_H