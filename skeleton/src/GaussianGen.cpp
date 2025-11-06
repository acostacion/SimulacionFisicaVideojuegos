#include "GaussianGen.h"

// el transform se crea en el padre.
GaussianGen::GaussianGen(Particle* modelP, physx::PxVec3 p)
: ParticleGen(modelP,p){}

// se llama a esto en cada iteracion
void GaussianGen::generateP(){
	// num aleatorio rango [0, 100)
	double rnd = rand() % 100;

	// si entra dentro de la probabilidad de generar la particula...
	if (rnd <= PROB_GEN)
	{
		// para n_particles...
		for (int i = 0; i < N_PARTICLES; i++) { // por cada iteracion genera una particula.
			// pos = pos + _d(_mt) * distPos
			_tf->p = _tf->p + physx::PxVec3(_d(_mt) * 0.1f);

			// vel = vel + _d(_mt) * distVel
			_vel = _vel + physx::PxVec3(_d(_mt) * 0.1f);

			// modifica el vector de particulas
			particles.push_back(new Particle(
				_modelParticle->getPos(), _modelParticle->getVel(), _modelParticle->getMass(), 
				_modelParticle->getSize(), _modelParticle->getColor(), _modelParticle->getIntegrateMode())
			);
		}
	}
}
