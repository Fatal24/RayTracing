//
// Created by adyan on 03/12/2025.
//

#ifndef RAYTRACING_RAYCASTHIT_H
#define RAYTRACING_RAYCASTHIT_H
#include "Vector3.h"
#include <limits>

#include "NullObject.h"
#include "SceneObject.h"
static auto NO_COLLISION_VEC = Vector3(std::numeric_limits<double>::infinity(),
    std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
class RaycastHit {

    // The distance the ray travelled before hitting an object
private:
    double distance;

    // The object that was hit by the ray
    const SceneObject objectHit;

    // The location that the ray hit the object
    const Vector3 location;

    // The normal of the object at the location hit by the ray
    const Vector3 normal;

public:
    RaycastHit() : distance(std::numeric_limits<double>::infinity()), objectHit(static_cast<SceneObject>(NullObject())),
    location(NO_COLLISION_VEC), normal(NO_COLLISION_VEC) {}

    RaycastHit(const SceneObject& objectHit, const double distance, const Vector3& location, const Vector3& normal) :
        distance(distance),objectHit(objectHit),location(location),normal(normal) {}

    [[nodiscard]] SceneObject getObjectHit() const {return objectHit;}

    [[nodiscard]] Vector3 getLocation() const {return location;}

    [[nodiscard]] Vector3 getNormal() const {return  normal;}

    [[nodiscard]] double getDistance() const {return distance;}
};



#endif //RAYTRACING_RAYCASTHIT_H