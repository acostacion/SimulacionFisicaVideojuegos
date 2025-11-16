#pragma once
#include <PxPhysicsAPI.h>
#include "../Render/RenderUtils.hpp"
#include "../Vector3D.h"

class GravityForceGenerator;
class WindForceGenerator;
class WhirlwindForceGenerator;
class ExplosionForceGenerator;

class Particle{
	friend class GravityForceGenerator;
	friend class WindForceGenerator;
	friend class WhirlwindForceGenerator;
	friend class ExplosionForceGenerator;
	// TODO cambiar todos los PxVec3 a Vector3D
public:
	enum integrateMode {
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

	// TODO ver por que no funciona lo del deregister...
	virtual ~Particle();

	void integrate(double t);

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

	// TIEMPO DE VIDA maximo que puede vivir una particula.
	const int MAX_LIFE_TIME = 1000; // cada x llamadas al update...MAX_LIFE_TIME)
public:
	// getters
	inline RenderItem* getRenderItem() const { return _renderItem; }
	inline physx::PxVec3 getPos() const { return _tf->p; }
	inline physx::PxVec3 getVel() const { return _vel; }
	inline integrateMode getIntegrateMode() const { return _i; }
	inline double getSize() const { return _size; }
	inline Vector4 getColor() const { return _color; }
	inline double getMass() const { return _mass; }
	inline physx::PxVec3 getForce() const { return _force; }
	inline physx::PxVec3 getAccel() const { return _a; }
	inline double getDamping() const { return _damping; }
	inline bool isDead() const { return _lifeTime > MAX_LIFE_TIME; }

	// setters
	inline void setPos(physx::PxVec3 pos) { _tf->p = pos; }
	inline void setVel(physx::PxVec3 vel) { _vel = vel; }
	inline void setSize(double size) { _size = size; }
	inline void setColor(Vector4 color) { _color = color; }
	inline void setMass(double mass) { _mass = mass; }
	inline void setAccel(physx::PxVec3 acc) { _a = acc; }
	inline void setDamping(double damp) { _damping = damp; }
};

