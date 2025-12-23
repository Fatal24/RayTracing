//
// Created by adyan on 22/12/2025.
//

#ifndef RAYTRACING_POINTLIGHT_H
#define RAYTRACING_POINTLIGHT_H
#include "ColorRGB.h"
#include "Vector3.h"
#include <cmath>


class PointLight {

    // Point light parameters
    Vector3 position;
    ColorRGB colour;
    double intensity;

public:
    PointLight(const Vector3 &position, const ColorRGB &colour, const double intensity) : position(position),
    colour(colour), intensity(intensity) {}

    [[nodiscard]] Vector3 getPosition() const {return position;}

    [[nodiscard]] ColorRGB getColour() const {return colour;}

    [[nodiscard]] double getIntensity() const {return intensity;}

    // Get colour of light at a certain distance away
    [[nodiscard]] ColorRGB getIlluminationAt(const double distance) const {
    return colour.scale(intensity / (M_PI * 4 * pow(distance, 2)));
    }
};

#endif //RAYTRACING_POINTLIGHT_H