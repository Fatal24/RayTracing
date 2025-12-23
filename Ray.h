//
// Created by adyan on 03/12/2025.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H
#include "Vector3.h"


class Ray {

    // Ray parameters

private:
    Vector3 origin, direction;

public:
    Ray(const Vector3 &origin, const Vector3 &direction):origin(origin), direction(direction) {}

    [[nodiscard]] Vector3 getOrigin() const {return origin;}

    [[nodiscard]] Vector3 getDirection() const {return direction;}

    // Determine position for certain scalar parameter distance i.e. (origin + direction * distance)
    [[nodiscard]] Vector3 evaluateAt(const double distance) const {return origin.add(direction.scale(distance));}
};


#endif //RAYTRACING_RAY_H