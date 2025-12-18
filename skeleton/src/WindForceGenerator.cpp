#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator(physx::PxVec3 speed, double k1)
	:_windSpeed(speed), _k1(k1) {
}

void WindForceGenerator::updateForce(Particle* p, double t){
	// Fviento = k1 (Vviento - Vp) + ... (0)
	physx::PxVec3 fuerzaViento = _k1 * (_windSpeed - p->getVel());

	// esto es por lo de que haya varias fuerzas a la vez.
	p->setForce(p->getForce() + fuerzaViento);
}

void WindForceGenerator::updateForce(physx::PxRigidDynamic* s, double t) {
	// Fviento = k1 (Vviento - Vp) + ... (0)
	physx::PxVec3 fuerzaViento = _k1 * (_windSpeed - s->getLinearVelocity());

	// esto es por lo de que haya varias fuerzas a la vez.
	s->addForce(fuerzaViento);
}
