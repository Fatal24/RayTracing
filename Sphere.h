//
// Created by adyan on 26/12/2025.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H
#include "RaycastHit.h"
#include "SceneObject.h"

// Phong's reflection model coefficients
static double SPHERE_KD = 0.8;
static double SPHERE_KS = 1.2;
static double SPHERE_ALPHA = 10;
static double SPHERE_REFLECTIVITY = 0.3;

class Sphere : public SceneObject {
	// The radius of the sphere in world units
	double radius;
	// The world-space position of the sphere
protected: Vector3 position;
public:
	[[nodiscard]] Vector3 getPosition() const {return position;}
	Sphere(const Vector3 &position, double radius, const ColorRGB &colour) : SceneObject(colour, SPHERE_KD,
		SPHERE_KS, SPHERE_ALPHA, SPHERE_REFLECTIVITY), radius(radius), position(position)  {}

	Sphere(const Vector3 &position, double radius, const ColorRGB &colour, double kD, double kS, double alphaS, double reflectivity, double transmittance) :
	SceneObject(colour, kD, kS, alphaS, reflectivity, transmittance), radius(radius), position(position)  {}

	/*
	 * Calculate intersection of the sphere with the ray. If the ray starts inside the sphere,
	 * intersection with the surface is also found.
	 */
	RaycastHit* intersectionWith(const Ray ray) override {

        // Get ray parameters
        const Vector3 O = ray.getOrigin();
        const Vector3 D = ray.getDirection();

        // Calculate quadratic coefficients
        const double a = D.dot(D);
        const double b = 2 * D.dot(O.subtract(position));
        const double c = O.subtract(position).dot(O.subtract(position)) - pow(radius, 2);
        double disc = pow(b, 2) - 4 * a * c;
        double sol1 = 0;
        double sol2 = 0;
        double sol = 0;
        if (disc > 0) {
            sol1 = (-1 * b + sqrt(disc)) / (2 * a);
            sol2 = (-1 * b - sqrt(disc)) / (2 * a);
        } else if (disc == 0) { sol = -1 * b/ (2 * a); }
        if (disc < 0 || (sol1 < 0 && sol2 < 0) || (disc == 0 && sol < 0)) { return new RaycastHit(); }
        if (disc == 0 && sol > 0) {
	        return new RaycastHit(*this, sol, ray.evaluateAt(sol) ,getNormalAt(ray.evaluateAt(sol)));
        }
        if ((sol1 > 0 && sol2 < 0) || (sol1 > 0 && sol2 > 0 && sol1 < sol2)) {
	        return new RaycastHit(*this, sol1, ray.evaluateAt(sol1) ,getNormalAt(ray.evaluateAt(sol1)));
        }
        if ((sol2 > 0 && sol1 < 0) || (sol1 > 0 && sol2 > 0 && sol1 > sol2)) {
	        return new RaycastHit(*this, sol2, ray.evaluateAt(sol2), getNormalAt(ray.evaluateAt(sol2)));
        }
        return new RaycastHit();
    }

	// Get normal to surface at position
	Vector3 getNormalAt(Vector3 position) override {return position.subtract(this->position).normalised();}
};
#endif //RAYTRACING_SPHERE_H