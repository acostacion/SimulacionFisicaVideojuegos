#include "GaussianGen.h"

GaussianGen::GaussianGen(physx::PxVec3 p, physx::PxVec3 v, physx::PxVec3 d) : ParticleGen(p, v, d){
	_tf = new physx::PxTransform(p); // inicializa transform
}

// se llama a esto en cada iteracion
void GaussianGen::generateP(std::vector<Particle*>& particles){
	// para n_particles...
	for (int i = 0; i < N_PARTICLES; i++) { // por cada iteracion genera una particula.
		// probabilidad de generar la particula. -> ¿TODO con lo de la normal vale, no, lo de _d(_mt)?
		// pos = pos + _d(_mt) * distPos
		_tf->p = _tf->p + physx::PxVec3(_d(_mt) * 0.1f);

		// vel = vel + _d(_mt) * distVel
		_vel = _vel + physx::PxVec3(_d(_mt) * 0.1f);

		// dir = dir + _d(_mt) * distDir
		_dir = _dir + physx::PxVec3(_d(_mt) * 0.1f);

		// clona PModel y asigna valores -> ¿TODO? que es este comentario que lo puso la profe??

		// modifica por referencia el vector de particulas del system
		particles.push_back(new Particle(_tf->p, _vel, Particle::SEMIEULER));
	}
}
