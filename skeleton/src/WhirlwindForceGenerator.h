#pragma once
#include "WindForceGenerator.h"
class WhirlwindForceGenerator : public WindForceGenerator
{
public:
	// TODO no se aun k tendra la constructora.
	WhirlwindForceGenerator(physx::PxVec3 speed, double k = 1.0, physx::PxVec3 center = physx::PxVec3(0.0)); 

protected:
	void updateForce(Particle* p) override;

private:
	// centro del torbellino.
	physx::PxVec3 _center;
	double _k; // lo de la formula.

	constexpr physx::PxVec3 ACTION_ZONE = { 50.0, 50.0, 50.0 };

	bool isInActionZone(Particle* p);
};

