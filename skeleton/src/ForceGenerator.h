#pragma once
#include "Particle.h"
#include <PxPhysicsAPI.h>

// Clase ABSTRACTA para para generar fuerzas.
class ForceGenerator {
public:
	~ForceGenerator() = default;

protected:
	void addForce(float force);
	void clearForce();

	double _mass;
};