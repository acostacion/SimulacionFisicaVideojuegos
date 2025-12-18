#pragma once
#include "SpringForceGenerator.h"

class AnchoredSpringForceGenerator : public SpringForceGenerator {
public:
	AnchoredSpringForceGenerator(double k, double resting, const physx::PxVec3& anchor_pos); // particle
	AnchoredSpringForceGenerator(double k, double resting, const physx::PxVec3& anchor_pos, 
		physx::PxPhysics* physics, physx::PxScene* scene); // solidorigido

	void setAnchor(physx::PxVec3 pos);

private:
	physx::PxPhysics* _pxphysics;
	physx::PxScene* _pxscene;
};

