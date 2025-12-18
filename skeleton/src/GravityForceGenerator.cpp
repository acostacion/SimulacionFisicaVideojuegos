#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(physx::PxVec3 g)
	: _gravity(g) {
}

void GravityForceGenerator::updateForce(Particle* p, double t) {

	physx::PxVec3 fuerzaGravedad = _gravity * p->getMass();

	// esto es por lo de que haya varias fuerzas a la vez.
	//physx::PxVec3 fuerzaTotal = p->getForce() + fuerzaGravedad;

	p->setForce(fuerzaGravedad); // F = m * g
}

void GravityForceGenerator::updateForce(physx::PxRigidDynamic* s, double t) {
	physx::PxVec3 fuerzaGravedad = _gravity * s->getMass();

	s->addForce(fuerzaGravedad);
}
