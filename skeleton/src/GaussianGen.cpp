#include "GaussianGen.h"

// el transform se crea en el padre.
GaussianGen::GaussianGen(physx::PxVec3 p, physx::PxVec3 v, physx::PxVec3 d) : ParticleGen(p, v, d){}

// se llama a esto en cada iteracion
void GaussianGen::generateP(std::vector<Particle*>& particles){
	// num aleatorio rango [0, 100]
	double rnd = _u(_mt) * 100.0;

	// si entra dentro de la probabilidad de generar la particula...
	if (rnd <= PROB_GEN)
	{
		// para n_particles...
		for (int i = 0; i < N_PARTICLES; i++) { // por cada iteracion genera una particula.
			// pos = pos + _d(_mt) * distPos
			_tf->p = _tf->p + physx::PxVec3(_d(_mt) * 0.1f);

			// vel = vel + _d(_mt) * distVel
			_vel = _vel + physx::PxVec3(_d(_mt) * 0.1f);

			// dir = dir + _d(_mt) * distDir
			_dir = _dir + physx::PxVec3(_d(_mt) * 0.1f);

			// modifica por referencia el vector de particulas del system
			particles.push_back(new Particle(_tf->p, _vel, Particle::SEMIEULER));
		}
	}
}
