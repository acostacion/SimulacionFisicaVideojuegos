#pragma once
#include <cmath>
class Vector3D {
public:
	inline Vector3D() : _x(0), _y(0), _z(0) {} // (0, 0, 0)
	inline Vector3D(float a) : _x(a), _y(a), _z(a) {} // (a, a, a)
	inline Vector3D(float x, float y, float z) : _x(x), _y(y), _z(z) {} // (x, y, z)

	// modulo
	inline float magnitudeSquared() const { return (_x * _x) + (_y * _y) + (_z * _z); }
	inline float magnitude() const { return std::sqrt(magnitudeSquared()); } 

	// normaliza el vector
	inline void normalize() {
		float m = magnitude();
		_x /= m; // x = x/m
		_y /= m; // y = y/m
		_z /= m; // z = z/m
	}

	// producto escalar de este vector por otro: TODO
	// A * B = (a1 * b1) + (a2 * b2) + (a3 * b3)
	inline float scalarProduct(Vector3D v) {
		return (_x * v.getX()) + (_y * v.getY()) + (_z * v.getZ());
	}

	// multiplicar el vector por un escalar TODO
	inline Vector3D scalarMultiplication(float k) {
		return *this* k;
	}

	// sobrecargar los operadores =, +, -, *
	inline Vector3D& operator=(Vector3D& v){ // u = v (asignacion)
		return Vector3D(v.getX(), v.getY(), v.getZ());
	}

	inline Vector3D& operator+(Vector3D& v) { // u + v
		return Vector3D(_x + v.getX(), _y + v.getY(), _z + v.getZ());
	}

	inline Vector3D& operator-(Vector3D& v) { // u - v
		return Vector3D(_x - v.getX(), _y - v.getY(), _z - v.getZ());
	}

	inline Vector3D& operator-() { // (a,b,c) -> (-a,-b,-c)
		return Vector3D(-_x, -_y, -_z);
	}

	// vector por escalar TODO
	inline Vector3D& operator*(float k) { // (a,b,c) -> (ka,kb,kc)
		return Vector3D(_x * k, _y * k, _z * k);
	}

	// producto vectorial (lo del determinante) TODO
	inline Vector3D& operator*(Vector3D& v) { // (a,b,c) -> (ka,kb,kc)
		return Vector3D(_x * v.getX(), _y * v.getY(), _z * v.getZ());
	}

	// getters
	inline float getX() { return _x; }
	inline float getY() { return _y; }
	inline float getZ() { return _z; }

	// setters
	inline void setX(float x) { _x = x; }
	inline void setY(float y) { _y = y; }
	inline void setZ(float z) { _z = z; }
	inline void set(float x, float y, float z) {
		_x = x;
		_y = y;
		_z = z;
	}

private:
	float _x, _y, _z;
};


