//
// Created by adyan on 03/12/2025.
//

#ifndef RAYTRACING_SCENEOBJECT_H
#define RAYTRACING_SCENEOBJECT_H
#include "ColorRGB.h"
#include "Ray.h"
#include "RaycastHit.h"
class SceneObject {
// The diffuse colour of the object
protected:
    ColorRGB colour;

    // Coefficients for calculating Phong illumination
    double phong_kD, phong_kS, phong_alpha;

    // How reflective this object is
    double reflectivity;

    // How much light is transmitted through the object (between 0 and 1)
    ColorRGB transmittance;
    double refractive_index;

    SceneObject() :
        colour(ColorRGB(1)),phong_kD(0),phong_kS(0),phong_alpha(0),reflectivity(0),transmittance(ColorRGB(0)),
        refractive_index(1.5) {}

    // Intersect this object with ray
public:
    virtual ~SceneObject() = default;

    virtual RaycastHit intersectionWith(Ray ray);

    // Get normal to object at position
    virtual Vector3 getNormalAt(Vector3 position);

    [[nodiscard]] ColorRGB getColour() const {return colour;}

    void setColour(const ColorRGB colour) {this->colour = colour;}

    [[nodiscard]] double getPhong_kD() const {return phong_kD;}

    [[nodiscard]] double getPhong_kS() const {return phong_kS;}

    [[nodiscard]] double getPhong_alpha() const {return phong_alpha;}

    [[nodiscard]] double getReflectivity() const {return reflectivity;}

    [[nodiscard]] bool isTransmissive() const {return !transmittance.isZero();}

    [[nodiscard]] ColorRGB getTransmittance() const { return transmittance; }
    [[nodiscard]] double getRefractiveIndex() const {return refractive_index;}

    void setReflectivity(double reflectivity) {this->reflectivity = reflectivity;}
};



#endif //RAYTRACING_SCENEOBJECT_H