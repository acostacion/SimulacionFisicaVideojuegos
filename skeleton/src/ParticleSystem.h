#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGen.h"

class ParticleSystem
{
public:
	std::list<Particle*> _particles;
	std::list<ParticleGen*> _generators;

	void update(double t);
};

