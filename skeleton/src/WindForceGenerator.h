#pragma once
#include "ForceGenerator.h"

class WindForceGenerator : public ForceGenerator {
public:
	WindForceGenerator(physx::PxVec3 speed, double k1 = 1.0);

private:
	physx::PxVec3 _windSpeed; // la velocidad del viento.
	double _k1; // lo de la formula.

	void updateForce(Particle* p) override;
};
