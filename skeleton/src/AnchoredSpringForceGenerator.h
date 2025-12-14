#pragma once
#include "SpringForceGenerator.h"

class AnchoredSpringForceGenerator : public SpringForceGenerator {
public:
	AnchoredSpringForceGenerator(double k, double resting, const physx::PxVec3& anchor_pos);
	~AnchoredSpringForceGenerator();
};

