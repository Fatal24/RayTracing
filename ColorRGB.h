//
// Created by adyan on 03/12/2025.
//

#ifndef RAYTRACING_COLORRGB_H
#define RAYTRACING_COLORRGB_H
#include <algorithm>

#include "Vector3.h"

class ColorRGB {

    // Vector3 member field
private:
    Vector3 v;
    ColorRGB(Vector3 vec) : // Private constructor
    v(vec),r(v.x),g(v.y),b(v.z) {}
    static int convertToByte(double value) { // Private method
        return 255 * std::max(static_cast<double>(0), std::ranges::min( static_cast<double>(1), value));}

    // RGB Colour components
public :
    const double r;
    const double g;
    const double b;

    ColorRGB(double uniform) : v(uniform), r(v.x), g(v.y), b(v.z) {    }

    ColorRGB(double red, double green, double blue) {
    v = new Vector3(red, green, blue);
    r = v.x;
    g = v.y;
    b = v.z;
}

    /*
     *  Add, subtract, scale, equals methods as in Vector3
     */
    [[nodiscard]] ColorRGB add(ColorRGB other) const {return {v.add(other.v)};}

    [[nodiscard]] ColorRGB add(double other) const {return {v.add(other)};}

    [[nodiscard]] ColorRGB subtract(ColorRGB other) const {return {v.subtract(other.v)};}

    [[nodiscard]] ColorRGB subtract(double other) const {return {v.subtract(other)};}

    [[nodiscard]] ColorRGB scale(double scalar) const {return {v.scale(scalar)};}

    [[nodiscard]] ColorRGB scale(ColorRGB other) const {return {v.scale(other.v)};}

    [[nodiscard]] ColorRGB power(double e) const { return {v.power(e)}; }

    [[nodiscard]] ColorRGB inv() const {return{v.inv()};}


    [[nodiscard]] bool equals(ColorRGB other) const {return v.equals(other.v);}

    [[nodiscard]] bool isZero() const {return (r==0 && g==0 && b==0);}

    /*
     * Conversion to RGB value
     */

    [[nodiscard]] int toRGB() const {
    return convertToByte(r) << 16 | convertToByte(g) << 8 | convertToByte(b) << 0;}
};

#endif //RAYTRACING_COLORRGB_H