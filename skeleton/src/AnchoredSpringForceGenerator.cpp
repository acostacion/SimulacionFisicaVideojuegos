#include "AnchoredSpringForceGenerator.h"

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double resting, const physx::PxVec3& anchor_pos)
	: SpringForceGenerator(k, resting, nullptr) {

	// anclaje.
	_other = new Particle(
		anchor_pos, 
		physx::PxVec3(0.0f), 
		1.0, 
		1.0, 
		Vector4(0.5, 0.5, 0.5, 1.0),
		Particle::SEMIEULER, 
		Particle::CUBE
	);
}

AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator() {
	delete _other;
	_other = nullptr;
}
