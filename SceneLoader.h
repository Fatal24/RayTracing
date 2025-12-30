//
// Created by adyan on 27/12/2025.
//

#ifndef RAYTRACING_SCENELOADER_H
#define RAYTRACING_SCENELOADER_H
#include <cassert>
#include <string>

#include "Plane.h"
#include "Scene.h"
#include "Sphere.h"
#include "tinyxml2-11.0.0/tinyxml2.h"

class SceneLoader {
	// Loads our scene from an XML file
	Scene *scene;
	static Vector3 getPosition(const tinyxml2::XMLElement& tag) {
		double x = getDouble(tag, "x", 0);
		double y = getDouble(tag, "y", 0);
		double z = getDouble(tag, "z", 0);
		return {x, y, z};
	}

	static Vector3 getNormal(const tinyxml2::XMLElement& tag) {
		double x = getDouble(tag, "nx", 0);
		double y = getDouble(tag, "ny", 0);
		double z = getDouble(tag, "nz", 0);
		const Vector3 n = {x, y, z};
		return n.normalised();
	}

	static ColorRGB getColour(const tinyxml2::XMLElement& tag) {
		const std::string hexString = tag.Attribute("colour");
		double red = stoi(hexString.substr(1, 3), nullptr,16) / 255.0;
		double green = stoi(hexString.substr(3, 5), nullptr,16) / 255.0;
		double blue = stoi(hexString.substr(5, 7), nullptr,16) / 255.0;
		return {red, green, blue};
	}

	static ColorRGB getTransmittance(const tinyxml2::XMLElement& tag) {
		double tr = getDouble(tag, "tr", 0);
		double tg = getDouble(tag, "tg", 0);
		double tb = getDouble(tag, "tb", 0);
		return {tr, tg, tb};
	}


	static double getDouble(const tinyxml2::XMLElement& tag, const std::string& attribute, const double fallback) {
			return std::stod(tag.Attribute(attribute.c_str())); //will return 0 or something on failure.
	}

	static std::string getString(const tinyxml2::XMLElement &tag, const std::string& attribute){return tag.Attribute(attribute.c_str());}

public:
	explicit SceneLoader(const std::string& filename) {
		scene = new Scene();

		tinyxml2::XMLElement document{};
		try {
			document = DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(new File(filename))
					.getDocumentElement();
		} catch (ParserConfigurationException e) {
			assert(false);
		} catch (IOException e) {
			throw new RuntimeException("error reading file:\n" + e.getMessage());
		} catch (SAXException e) {
			throw new RuntimeException("error loading XML.");
		}

		if (!document.getNodeName().equals("scene"))
			throw new RuntimeException("scene file does not contain a scene element");

		NodeList elements = document.getElementsByTagName("*");
		for (int i = 0; i < elements.getLength(); ++i) {
			tinyxml2::XMLElement element = (tinyxml2::XMLElement) elements.item(i);
			switch (element.getNodeName()) {
			case "sphere":
				Sphere sphere = {
				getPosition(element), getDouble(element, "radius", 1), getColour(element),
	   getDouble(element, "kD", 0.8), getDouble(element, "kS", 1.2),
	   getDouble(element, "alphaS", 10), getDouble(element, "reflectivity", 0.3),
	   getTransmittance(element)};
				scene->addObject(sphere);
				break;

		/*	case "cone":
				Cone cone = new Cone(getPosition(element), getDouble(element, "radius", 1), getDouble(element, "height", 1), getColour(element),
						getDouble(element, "kD", 0.8), getDouble(element, "kS", 1.2),
						getDouble(element, "alphaS", 10), getDouble(element, "reflectivity", 0.3)
				);
				scene.addObject(cone);
				break;

			case "cylinder":
					Cylinder cylinder = new Cylinder(getPosition(element), getDouble(element, "radius", 1), getDouble(element, "height", 1), getColour(element),
							getDouble(element, "kD", 0.8), getDouble(element, "kS", 1.2),
							getDouble(element, "alphaS", 10), getDouble(element, "reflectivity", 0.3)
					);
					scene.addObject(cylinder);
					break;

			case "bumpy-sphere":
				BumpySphere bumpySphere = new BumpySphere(getPosition(element), getDouble(element, "radius", 1), getColour(element), getString(element, "bump-map"));
				scene.addObject(bumpySphere);
				break;*/

			case "plane":
				Plane plane = {
				getPosition(element), getNormal(element), getColour(element),
		 getDouble(element, "kD", 0.8), getDouble(element, "kS", 1.2),
		 getDouble(element, "alphaS", 10), getDouble(element, "reflectivity", 0.3)};
				scene->addObject(plane);
				break;

			case "point-light":
				PointLight light = {
				getPosition(element), getColour(element),getDouble(element, "intensity", 100)};
				scene->addPointLight(light);
				break;

			case "ambient-light":
				scene->setAmbientLight(getColour(element).scale(getDouble(element, "intensity", 1)));
				break;

			default:
				throw new RuntimeException("unknown object tag: " + element.getNodeName());
			}
		}
	}

	[[nodiscard]] Scene getScene() const {return *scene;}

};


#endif //RAYTRACING_SCENELOADER_H