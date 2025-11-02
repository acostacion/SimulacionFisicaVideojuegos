#pragma once
#include <vector>
#include "ForceGenerator.h"
#include "Particle.h"

// Sistema que gestiona como afectan los ForceGenerators a las particulas.
class ParticleForceRegistry {
public:
	~ParticleForceRegistry();

	// GENERATORS: todos los generadores de fuerzas que existan.
	std::vector<ForceGenerator*> forceGenerators;
	// PARTICLES: se encarga de almacenar todas las particulas que sean afectadas por una fuerza.
	std::vector<Particle*> particles; 

	void update(double t);
};