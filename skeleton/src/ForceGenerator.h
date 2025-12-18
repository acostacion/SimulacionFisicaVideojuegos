#pragma once
#include "Particle.h"
#include <PxPhysicsAPI.h>

class ParticleForceRegistry;

// Clase ABSTRACTA (interfaz) para para generar fuerzas.
// - Gravitatoria.
// - Viento.
// - Torbellino.
// - Explosion.
// - Muelle.
// - Muelle (anchored).
// - Flotacion
// - ...
class ForceGenerator {
	friend class ParticleForceRegistry;
public:
	ForceGenerator(bool active = true) : _isActive(active) {}
	virtual ~ForceGenerator() {}

	
	std::vector<Particle*> particles; // PARTICLES: particulas a las que afecta la fuerza aplicada.
	std::vector<physx::PxRigidDynamic*> solids; // SOLIDOS RIGIDOS: solidos a los k les afecta dicha fuerza.

	bool isActive() const { return _isActive; }
	void setActive(bool active) { _isActive = active; }

protected:
	bool _isActive; // para ver si esta activa ahora mismo o no.

	virtual void updateForce(Particle* p, double t) = 0; // particulas
	virtual void updateForce(physx::PxRigidDynamic* s, double t) = 0; // solidos rigidos
};