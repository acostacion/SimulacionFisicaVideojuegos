#pragma once
#include <vector>
#include "Particle.h"
#include "ParticleGen.h"

// Sistema que gestiona los diferentes Particle Generators.
class ParticleSystem { // TODO arreglarlo que se ha roto.
public:
	~ParticleSystem();

	// GENERATORS: todos los generadores de particulas que existan.
	std::vector<ParticleGen*> particleGenerators;

	void update(double t);

private:
	const physx::PxVec3 ACTION_ZONE = { 0.0f, 50.0f, 0.0f };

	void deleteParticle(Particle* p);
};

