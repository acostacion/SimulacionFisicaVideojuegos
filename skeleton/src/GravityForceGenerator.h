#pragma once
#include "ForceGenerator.h"

class GravityForceGenerator : public ForceGenerator {
public:
	GravityForceGenerator(physx::PxVec3 g = {0.0f, -9.8f, 0.0f}); // de base la de la tierra

private:
	physx::PxVec3 _gravity; // la gravedad que le pongas.

	void updateForce(Particle* p, double t) override;
	void updateForce(physx::PxRigidDynamic* s, double t) override;
};

