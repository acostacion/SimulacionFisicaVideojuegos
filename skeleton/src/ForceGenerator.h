#pragma once
#include "Particle.h"
#include <PxPhysicsAPI.h>

class ParticleForceRegistry;

// Clase ABSTRACTA (interfaz) para para generar fuerzas.
// - Gravitatoria.
// - Viento.
// - Torbellino.
// - ...
class ForceGenerator {
	friend class ParticleForceRegistry;
public:
	ForceGenerator(bool active = true) : _isActive(active) {}
	virtual ~ForceGenerator() {}

	// PARTICLES: particulas a las que afecta la fuerza aplicada.
	std::vector<Particle*> particles;

	bool isActive() const { return _isActive; }
	void setActive(bool active) { _isActive = active; }

protected:
	bool _isActive; // para ver si esta activa ahora mismo o no.
	virtual void updateForce(Particle* p) = 0;
};