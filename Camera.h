//
// Created by adyan on 03/12/2025.
//

#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H
#include "Ray.h"
#include "Vector3.h"


class Camera {
public:
    // Horizontal field of view in degrees
    double fov = 45;

    // Aspect ration of image - ratio of width to height
    double aspectRatio;

    //Dimensions of image plane in pixels (px) - i.e. screen units
private:
        int width_px, height_px;

    // Dimensions of image plane in metres (m) - i.e. world units
        double width_m, height_m;
        // The distance in world units between each screen-space pixel
        double x_step_m, y_step_m;

public:
    Camera(const int width, const int height) :
        aspectRatio(static_cast<double>(width) / static_cast<double>(height)),width_px(width),height_px(height),
        width_m(tan(fov * M_PI/ 360)),height_m(width_m / aspectRatio),
        x_step_m(width_m/width_px),y_step_m(height_m/height_px) {}

    // Casts a ray through a supplied pixel coordinate
    [[nodiscard]] Ray castRay(int x, int y) const {
        const double x_pos = (x_step_m - width_m) / 2 + x * x_step_m;
        const double y_pos = (y_step_m + height_m) / 2 - y * y_step_m;
        return { Vector3(0, 0, 0), (new Vector3(x_pos, y_pos, 1))->normalised()};
    }
};



#endif //RAYTRACING_CAMERA_H