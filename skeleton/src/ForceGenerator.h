#pragma once
#include "Particle.h"
#include <PxPhysicsAPI.h>

class ParticleForceRegistry;

// Clase ABSTRACTA (interfaz) para para generar fuerzas.
// - Gravitatoria.
// - Viento.
// - ...
class ForceGenerator {
	friend class ParticleForceRegistry;
public:
	virtual ~ForceGenerator() {}

	// PARTICLES: particulas a las que afecta la fuerza aplicada.
	std::vector<Particle*> particles;

private:
	virtual void updateForce(Particle* p) = 0;
};