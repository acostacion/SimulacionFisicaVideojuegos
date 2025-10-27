#pragma once
#include <vector>
#include "ForceGenerator.h"
#include "Particle.h"

// Sistema que gestiona como afectan los ForceGenerators a las particulas.
class ParticleSystem {
public:
	~ParticleSystem();

	// GENERATORS: todos los generadores de fuerzas que existan.
	std::vector<ForceGenerator*> generators;

	void update(double t);

private:
	// PARTICLES: se encarga de almacenar todas las particulas que sean afectadas por una fuerza.
	//std::vector<Particle*> _particles; TODO aun no se si esto es asi
};