#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator(physx::PxVec3 speed, double k1)
	:_windSpeed(speed), _k1(k1) {
}

void WindForceGenerator::updateForce(Particle* p){
	// Fviento = k1 (Vviento - Vp) + ... (0)
	physx::PxVec3 fuerzaViento = _k1 * (_windSpeed - p->getVel());

	// esto es por lo de que haya varias fuerzas a la vez.
	p->setForce(p->getForce() + fuerzaViento);
}
