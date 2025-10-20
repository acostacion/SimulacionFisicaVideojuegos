#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGen.h"

// Sistema que gestiona los diferentes Particle Generators.
class ParticleSystem {
public:
	~ParticleSystem();

	// PARTICLES: se encarga de almacenar todas las particulas que se generen, TODAS.
	std::vector<Particle*> particles;

	// GENERATORS: todos los generadores de particulas que existan.
	std::vector<ParticleGen*> generators;

	void update(double t);

private:
	// TIEMPO DE VIDA maximo que puede vivir una particula.
	const int MAX_LIFE_TIME = 200; // cada x llamadas al update...

	// GRAVEDAD que indica el enunciado.
	const float GRAVITY = -10.0f;
};

