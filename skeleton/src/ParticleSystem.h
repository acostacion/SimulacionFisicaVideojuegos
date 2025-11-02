#pragma once
#include <vector>
#include "Particle.h"
#include "ParticleGen.h"

// Sistema que gestiona los diferentes Particle Generators.
class ParticleSystem {
public:
	~ParticleSystem();

	// GENERATORS: todos los generadores de particulas que existan.
	std::vector<ParticleGen*> particleGenerators;

	void update(double t);

private:
	// PARTICLES: se encarga de almacenar todas las particulas que se generen, TODAS.
	std::vector<Particle*> _particles;

	// TIEMPO DE VIDA maximo que puede vivir una particula.
	const int MAX_LIFE_TIME = 200; // cada x llamadas al update...

	// GRAVEDAD que indica el enunciado.
	const float GRAVITY = -10.0f;

	const physx::PxVec3 ACTION_ZONE = { 0.0f, 50.0f, 0.0f };
};

