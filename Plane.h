//
// Created by adyan on 22/12/2025.
//

#ifndef RAYTRACING_PLANE_H
#define RAYTRACING_PLANE_H
#include <functional>

#include "RaycastHit.h"
#include "SceneObject.h"
//Plane Defaults
static double DEFAULT_PLANE_KD = 0.6;
static double DEFAULT_PLANE_KS = 0.0;
static double DEFAULT_PLANE_ALPHA = 0.0;
static double DEFAULT_PLANE_REFLECTIVITY = 0.1;

class Plane : public SceneObject {

    // A point in the plane
    Vector3 point;
    // The normal of the plane
    Vector3 normal;

public:
    Plane(const Vector3 &point, const Vector3 &normal, const ColorRGB &colour) :
    SceneObject(colour, DEFAULT_PLANE_KD, DEFAULT_PLANE_KS, DEFAULT_PLANE_ALPHA, DEFAULT_PLANE_REFLECTIVITY),
    point(point), normal(normal) {}

    Plane(const Vector3 &point, const Vector3 &normal, const ColorRGB &colour, double kD, double kS, double alphaS, double reflectivity) :
        point(point), normal(normal), SceneObject(colour, kD, kS, alphaS, reflectivity) {}

    // Intersect this plane with a ray
    RaycastHit* intersectionWith(const Ray ray) override {
        // Get ray parameters
        const Vector3 O = ray.getOrigin();
        const Vector3 D = ray.getDirection();

        // Get plane parameters
        const Vector3 Q = this->point;
        const Vector3 N = this->normal;
        if (const double scaling = D.dot(N); scaling == 0) {return new RaycastHit();}
        else {
            if (const double s = Q.subtract(O).dot(N) / scaling; s < 0) {return new RaycastHit();}
            else {
                const Vector3 loc = ray.evaluateAt(s);
                return new RaycastHit(*this, s, loc, N);
            }
        }
    }

    // Get normal to the plane
    Vector3 getNormalAt(Vector3 position) override {return normal;}
};

#endif //RAYTRACING_PLANE_H