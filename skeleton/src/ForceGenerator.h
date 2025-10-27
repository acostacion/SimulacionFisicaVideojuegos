#pragma once
#include "Particle.h"
#include <PxPhysicsAPI.h>

// Clase ABSTRACTA para para generar fuerzas.
// - Gravitatoria.
// - Viento.
// - ...
class ForceGenerator {
public:
	virtual ~ForceGenerator() {}

protected:
	virtual void addForce(float force) = 0;
	virtual void clearForce() = 0;
};