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

	void update();
};