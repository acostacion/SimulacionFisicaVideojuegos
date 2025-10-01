#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
public:
	enum integrateMode{
		EULER,
		SEMIEULER,
		VERLET
	};

	Particle(
		Vector3D pos, 
		Vector3D vel, 
		integrateMode i = EULER,
		double size = 1.0, 
		Vector4 color = { 1.0, 0.0, 0.0, 1.0 }
	);

	~Particle();

	void integrate(double t);
private:
	RenderItem* _renderItem;
	physx::PxTransform _tf;  // transform
	Vector3D _pos; // position
	Vector3D _vel;  // velocity
	Vector3D _a;    // acceleration
	double _damping; // en cada frame la velocidad se decrementara en funcion del valor de damping
	double _size;
	Vector4 _color;
	integrateMode _i;

	bool _firstVerlet; // primera vuelta de Verlet en Euler.

	// metodos integrar
	void integrateEuler(double t);
	void integrateSemiEuler(double t); 
	void integrateVerlet(double t);
	

	// getters
	inline RenderItem* getRenderItem() { return _renderItem; }
	inline Vector3D getPos() { return _pos; }
	inline Vector3D getVel() { return _vel; }
	inline Vector3D getAccel() { return _a; }
	inline double getDamping() { return _damping; }
	inline double getSize() { return _size; }
	inline Vector4 getColor() { return _color; }

	// setters
	inline void setPos(Vector3D pos) { _pos = pos; }
	inline void setVel(Vector3D vel) { _vel = vel; }
	inline void setAccel(Vector3D acc) { _a = acc; }
	inline void setDamping(double damp) { _damping = damp; }
	inline void setSize(double size) { _size = size; }
	inline void setColor(Vector4 color) { _color = color; }
};

