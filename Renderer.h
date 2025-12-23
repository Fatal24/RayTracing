//
// Created by adyan on 23/12/2025.
//

#ifndef RAYTRACING_RENDERER_H
#define RAYTRACING_RENDERER_H

#include <iostream>
#include <ostream>

#include "Camera.h"
#include "ColorRGB.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "Scene.h"

class Renderer {

	// The width and height of the image in pixels
private:
	int width, height;

	// Bias factor for reflected and shadow rays
	const double EPSILON = 0.0001;

	// The number of times a ray can bounce for reflection
	int bounces;

	// Background colour of the image
	ColorRGB backgroundColor = ColorRGB(0.001);

public:
	Renderer(int width, int height, int bounces) : width(width), height(height), bounces(bounces) {}

	// Render an image from the scene, with the camera at the origin
	BufferedImage render(Scene scene) {

		// Set up image
		BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);

		// Set up camera
		const Camera camera = {width, height};

		// Loop over all pixels
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				Ray ray = camera.castRay(x, y); // Cast ray through pixel
				ColorRGB linearRGB = trace(scene, ray, bounces); // Trace path of cast ray and determine colour
				ColorRGB gammaRGB = tonemap(linearRGB);
				image.setRGB(x, y, gammaRGB.toRGB()); // Set image colour to traced colour
			}
			// Display progress every 10 lines
			if(y%10==9||y==height-1) {
				printf("%.2f", 100 * y / static_cast<double>(height-1));
				std::cout << "% completed" << std::endl;
			}
		}
		return image;
	}


	// Combined tone mapping and display encoding
	static ColorRGB tonemap(const ColorRGB& linearRGB) {
		constexpr double invGamma = 1./2.2;
		constexpr double a = 2;  // controls brightness
		constexpr double b = 1.3; // controls contrast
		// Sigmoidal tone mapping
		const ColorRGB powRGB = linearRGB.power(b);
		const ColorRGB displayRGB = powRGB.scale(powRGB.add(pow(0.5/a,b)).inv());
		// Display encoding - gamma
		const ColorRGB gammaRGB = displayRGB.power(invGamma);
		return gammaRGB;
	}

	/*
	 * Trace the ray through the supplied scene, returning the colour to be rendered.
	 * The bouncesLeft parameter is for rendering reflective surfaces.
	 */
protected:
	ColorRGB trace(const Scene& scene, const Ray &ray, const int bouncesLeft) {

        // Find closest intersection of ray in the scene
		RaycastHit* closestHit = scene.findClosestIntersection(ray);
		// If no object has been hit, return a background colour
		if (closestHit->getDistance() == std::numeric_limits<double>::infinity()) {return backgroundColor;}

        const SceneObject object = closestHit->getObjectHit();

        // Otherwise calculate colour at intersection and return
        // Get properties of surface at intersection - location, surface normal
        const Vector3 P = closestHit->getLocation();
        const Vector3 N = closestHit->getNormal();
        const Vector3 O = ray.getOrigin();

        ColorRGB directIllumination = this->illuminate(scene, object, P, N, O);
        if (const double reflectivity = object.getReflectivity(); bouncesLeft == 0 || reflectivity == 0) {return directIllumination;}
        else { // Recursive case
            const Vector3 R = ray.getDirection().normalised().reflectIn(N.normalised()).normalised().scale(-1);
            const Ray reflectedRay =  {P.add(N.scale(EPSILON)), R};
            ColorRGB reflectedIllumination = trace(scene, reflectedRay, bouncesLeft-1);
            directIllumination = directIllumination.scale(1.0 - reflectivity);
            reflectedIllumination = reflectedIllumination.scale(reflectivity);
            // Return total illumination
            return directIllumination.add(reflectedIllumination);
        }
    }
	/*
	 * Illuminate a surface on and object in the scene at a given position P and surface normal N,
	 * relative to ray originating at O
	 */
	ColorRGB illuminate(Scene scene, SceneObject object, Vector3 P, Vector3 N, Vector3 O) {

        Vector3 normal = N.normalised();
		auto colourToReturn = ColorRGB(0);

		ColorRGB I_a = scene.getAmbientLighting(); // Ambient illumination intensity
        Vector3 V = O.subtract(P).normalised();
		ColorRGB C_diff = object.getColour(); // Diffuse colour defined by the object

		// Get Phong reflection model coefficients
		double k_d = object.getPhong_kD();
		double k_s = object.getPhong_kS();
		double alpha = object.getPhong_alpha();

        colourToReturn = colourToReturn.add(C_diff.scale(I_a));
		// Loop over each point light source
		std::list<PointLight> pointLights = scene.getPointLights();
		int len = pointLights.size();
		for (int i = 0; i < len; i++) {
            auto diffuse = ColorRGB(0);
            auto specular = ColorRGB(0);
			PointLight light = pointLights.front();
			pointLights.pop_front();

			// Calculate point light constants
			double distanceToLight = light.getPosition().subtract(P).magnitude();
			ColorRGB C_spec = light.getColour();
			ColorRGB I = light.getIlluminationAt(distanceToLight);

            Vector3 L = light.getPosition().subtract(P).normalised();
            Vector3 R = L.reflectIn(normal).normalised();

            Ray shadowRay = {P.add(N.scale(EPSILON)), L};
            if (RaycastHit* shadowcheck = scene.findClosestIntersection(shadowRay); shadowcheck->getDistance() > distanceToLight) {
                diffuse = C_diff.scale(I.scale(k_d * std::ranges::max(static_cast<double>(0), normal.dot(L))));
                specular = C_spec.scale(I.scale(k_s * pow(std::ranges::max(static_cast<double>(0), R.dot(V)), alpha)));
            }
            colourToReturn = colourToReturn.add(diffuse).add(specular);
		}
		return colourToReturn;
	}
};


#endif //RAYTRACING_RENDERER_H