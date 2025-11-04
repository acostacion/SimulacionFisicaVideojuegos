#pragma once
#include <PxPhysicsAPI.h>
#include "../Render/RenderUtils.hpp"
#include "../Vector3D.h"

class GravityForceGenerator;
class WindForceGenerator;

class Particle{
	friend class GravityForceGenerator;
	friend class WindForceGenerator;
	// TODO cambiar todos los PxVec3 a Vector3D
public:
	enum integrateMode{
		EULER,
		SEMIEULER,
		VERLET
	};

	Particle(
		physx::PxVec3 pos,
		physx::PxVec3 vel,
		double mass = 1.0,
		double size = 1.0, 
		Vector4 color = { 1.0, 0.0, 0.0, 1.0 },
		integrateMode i = EULER
	);

	~Particle();

	virtual void integrate(double t);

private:
	RenderItem* _renderItem;

	physx::PxTransform* _tf;  // transform (pos)
	physx::PxVec3 _vel;		  // velocity
	integrateMode _i;
	double _size;
	Vector4 _color;

	double _mass;			  // masa
	physx::PxVec3 _force;

	physx::PxVec3 _a;		  // acceleration
	double _damping;		  // en cada frame la velocidad se decrementara en funcion del valor de damping
	double _lifeTime;

	bool _firstVerlet; // primera vuelta de Verlet en Euler.

	// metodos integrar
	void integrateEuler(double t);
	void integrateSemiEuler(double t); 
	void integrateVerlet(double t);
	
	inline void addForce(physx::PxVec3 f) { _force += f; }
	inline void setForce(physx::PxVec3 f) { _force = f; }
	inline void clearForce() { _force = physx::PxVec3(0.0f); }
public:
	// getters
	inline RenderItem* getRenderItem() { return _renderItem; }
	inline physx::PxVec3 getPos() { return _tf->p; }
	inline physx::PxVec3 getVel() { return _vel; }
	inline double getIntegrateMode() { return _i; }
	inline double getSize() { return _size; }
	inline Vector4 getColor() { return _color; }
	inline double getMass() { return _mass; }
	inline physx::PxVec3 getForce() { return _force; }
	inline physx::PxVec3 getAccel() { return _a; }
	inline double getDamping() { return _damping; }
	inline double getLifeTime() { return _lifeTime; }

	// setters
	inline void setPos(physx::PxVec3 pos) { _tf->p = pos; }
	inline void setVel(physx::PxVec3 vel) { _vel = vel; }
	inline void setSize(double size) { _size = size; }
	inline void setColor(Vector4 color) { _color = color; }
	inline void setMass(double mass) { _mass = mass; }
	inline void setAccel(physx::PxVec3 acc) { _a = acc; }
	inline void setDamping(double damp) { _damping = damp; }
};

