#ifndef RAYTRACING_VECTOR3_H
#define RAYTRACING_VECTOR3_H
#include <cmath>

class Vector3 {
public:
	 double x, y, z;
	 explicit Vector3(const double uniform):Vector3(uniform, uniform, uniform) {};

	 Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

	// Add two vectors together
	 [[nodiscard]] Vector3 add(Vector3 other) const {return {x + other.x, y + other.y, z + other.z};}

	// Add a scalar to a vector
	[[nodiscard]] Vector3 add(double other) const {return {x + other, y + other, z + other};}

	// Subtract two vectors
	[[nodiscard]] Vector3 subtract(Vector3 other) const {return {x - other.x, y - other.y, z - other.z};}

	[[nodiscard]] Vector3 subtract(double other) const {return {x - other, y - other, z - other};}

	// Scale a vector by a scalar
	[[nodiscard]] Vector3 scale(double scalar) const {return {scalar * x, scalar * y, scalar * z};}

	// Hadamard product, scales the vector in an element-wise fashion
	[[nodiscard]] Vector3 scale(Vector3 other) const {return {x * other.x, y * other.y, z * other.z};}

	// Dot product of two vectors
	[[nodiscard]] double dot(Vector3 other) const {return x * other.x + y * other.y + z * other.z;}

	// Cross product of two vectors
	[[nodiscard]] Vector3 cross(Vector3 other) const {
		return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
	}

	// Element-wise power function
	[[nodiscard]] Vector3 power(double e) const {return {pow(x,e), pow(y,e), pow(z,e)};}

	// Element-wise inverse (1/v)
	[[nodiscard]] Vector3 inv() const {return {1/x, 1/y, 1/z};}


	// Magnitude of a vector
	[[nodiscard]] double magnitude() const {return sqrt(x * x + y * y + z * z);}

	// Normalise a vector
	[[nodiscard]] Vector3 normalised() const {
		const double magnitude = this->magnitude();
		return {x / magnitude, y / magnitude, z / magnitude};
	}

	// Calculate mirror-like reflection
	[[nodiscard]] Vector3 reflectIn(Vector3 N) const {return N.scale(2 * this->dot(N)).subtract(*this);}

	// Creates a random vector inside the unit sphere
	static Vector3 randomInsideUnitSphere() {
		const double r = rand();
		const double theta = rand() * M_PI;
		const double phi = rand() * M_PI * 2;
		double x = r * sin(theta) * cos(phi);
		double y = r * sin(theta) * sin(phi);
		double z = r * cos(theta);
		return {x, y, z};
	}

	// Determine if two vectors are equal
	[[nodiscard]] bool equals(Vector3 other) const {return x == other.x && y == other.y && z == other.z;}

	[[nodiscard]] bool isZero() const {return (x==0 && y==0 && z==0);}
};


#endif //RAYTRACING_VECTOR3_H