#pragma once
#include "Particle.h"
#include <cstdlib>
#include <PxPhysicsAPI.h>
#include <random>

// Clase padre ABSTRACTA para los Particle Generators hijos:
// - Gaussian Generator.
// - Normal Generator.
// - ...
class ParticleGen{
public:
	ParticleGen(Particle* modelP, physx::PxVec3 p, bool active = true)
		: _modelParticle(modelP), _isActive(active), _vel(modelP->getVel()){
		_tf = new physx::PxTransform(p);
	}

	std::vector<Particle*> particles; // particulas de cada generador.

	virtual ~ParticleGen() {
		delete _modelParticle;
		delete _tf;
	}

	virtual void generateP() = 0;

	// getters
	physx::PxVec3 getPos() const { return _tf->p; }
	physx::PxVec3 getVel() const { return _vel; }
	bool isActive() const { return _isActive; }

	// setters
	void setPos(physx::PxVec3 p) { _tf->p = p; }
	void setVel(physx::PxVec3 v) { _vel = v; }
	void setActive(bool active) { _isActive = active; }

protected:
	// particula modelo de la que generaran nuevas particulas...
	Particle* _modelParticle;

	physx::PxTransform* _tf; // TRANSFORM, del particlegen (POS).
	physx::PxVec3 _vel; // a que velocidad se emiten las particulas (TODO: no podria haber algunas con mayor velocidad que otras. Ej.: fuego).

	bool _isActive; // para ver si esta activa ahora mismo o no.

	const int PROB_GEN = 5; // probabilidad de generar una particula 

	// Numero de particulas que genera en cada llamada
	const int N_PARTICLES = 1;

	/* Se usa como el motor de numeros aleatorios para alimentar a las distribuciones.
	 * Su rango es [0, 2^32) */
	std::mt19937 _mt;
};

