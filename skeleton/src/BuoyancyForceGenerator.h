#pragma once
#include "ForceGenerator.h"
class BuoyancyForceGenerator : public ForceGenerator {
public:
	BuoyancyForceGenerator(float h, float V, float d);

	virtual void updateForce(Particle* p, double t) override;

	virtual ~BuoyancyForceGenerator();

protected:
	float _height; 
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;

	Particle* _liquid_particle; // For representation
};

