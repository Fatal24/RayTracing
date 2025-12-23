//
// Created by adyan on 23/12/2025.
//

#ifndef RAYTRACING_SCENE_H
#define RAYTRACING_SCENE_H
#include <list>

#include "PointLight.h"
#include "RaycastHit.h"
#include "SceneObject.h"

class Scene {

    // A list of 3D objects to be rendered
private:
    std::list<SceneObject> objects;

    // A list of point light sources
    std::list<PointLight> pointLights;

    // The color of the ambient light in the scene
    ColorRGB ambientLight;

public:
    Scene() : ambientLight(ColorRGB(1)) {}

    void addObject(const SceneObject& object) {objects.push_back(object);}

    // Find the closest intersection of given ray with an object in the scene
    [[nodiscard]] RaycastHit* findClosestIntersection(const Ray &ray) const {
    auto* closestHit = new RaycastHit(); // initially no intersection

    // Loop over objects and find closest intersection
    for (SceneObject object : objects) {
        if (RaycastHit* trialHit = object.intersectionWith(ray); trialHit->getDistance() < closestHit->getDistance()) {
            closestHit = trialHit;
        }
    }
    return closestHit;
}

    [[nodiscard]] ColorRGB getAmbientLighting() const {return ambientLight;}

    void setAmbientLight(ColorRGB ambientLight) {this->ambientLight = ambientLight;}

    [[nodiscard]] PointLight getPointLight() const {return pointLights.front();}

    std::list<PointLight> getPointLights() {return pointLights;}

    void addPointLight(const PointLight &pointLight) {pointLights.push_back(pointLight);}

};

#endif //RAYTRACING_SCENE_H