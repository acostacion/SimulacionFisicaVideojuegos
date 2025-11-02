#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(physx::PxVec3 g)
	: _gravity(g) {
}

void GravityForceGenerator::updateForce(Particle* p, double t) {
	p->addForce(_gravity * p->getMass()); // F = m * g
}
