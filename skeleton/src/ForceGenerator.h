#pragma once
#include "Particle.h"
#include <PxPhysicsAPI.h>

// Clase ABSTRACTA (interfaz) para para generar fuerzas.
// - Gravitatoria.
// - Viento.
// - ...
class ForceGenerator {
public:
	virtual ~ForceGenerator() {}
	virtual void updateForce(Particle* p, double t) = 0;
};