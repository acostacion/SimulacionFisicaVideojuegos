#include "WhirlwindForceGenerator.h"

WhirlwindForceGenerator::WhirlwindForceGenerator(physx::PxVec3 speed, double k, physx::PxVec3 center)
	:WindForceGenerator(speed), _center(center), _k(k) {
}

void WhirlwindForceGenerator::updateForce(Particle* p) {
	if (isInActionZone(p)) { // TODO me he quedado por aqui
		physx::PxVec3 velTorbellino =
			physx::PxVec3(
				-(p->getPos().z - _center.z),
				50 - (p->getPos().y - _center.y),
				p->getPos().x - _center.x
			);
	}
}

bool WhirlwindForceGenerator::isInActionZone(Particle* p){
	return p->getPos().x < ACTION_ZONE.x + _center.x
		&& p->getPos().y < ACTION_ZONE.y + _center.y
		&& p->getPos().z < ACTION_ZONE.z + _center.z;
}
