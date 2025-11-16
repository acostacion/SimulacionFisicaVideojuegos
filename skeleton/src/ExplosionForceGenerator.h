#pragma once
#include "ForceGenerator.h"

class ExplosionForceGenerator : public ForceGenerator {
public:
	ExplosionForceGenerator(physx::PxVec3 force, double k = 1.0, physx::PxVec3 center = physx::PxVec3(0.0));

protected:
	void updateForce(Particle* p) override;

private:
	physx::PxVec3 _explosionSpeed; // velocidad de la explosion
	physx::PxVec3 _center;		   // centro de la explosion
	double _k;					   // intensidad de la explosion


	const physx::PxVec3 ACTION_ZONE = { 50.0, 50.0, 50.0 };

	bool isInActionZone(Particle* p);
};
