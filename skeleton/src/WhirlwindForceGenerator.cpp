#include "WhirlwindForceGenerator.h"

WhirlwindForceGenerator::WhirlwindForceGenerator(physx::PxVec3 speed, double k, physx::PxVec3 center)
	:WindForceGenerator(speed), _center(center), _k(k) {
}

void WhirlwindForceGenerator::updateForce(Particle* p, double t) {
	if (isInActionZone(p)) {
		// distancias del centro a la particula a cada componente.
		physx::PxVec3 d = p->getPos() - _center;

		// formula velocidad del torbellino del enunciado.
		physx::PxVec3 fuerzaTorbellino = _k * physx::PxVec3(-d.z, 50 - d.y, d.x);

		// se asigna a la velocidad del viento de la clase padre.
		_windSpeed = fuerzaTorbellino;

		// calcula la fuerza del viento.
		WindForceGenerator::updateForce(p, t);
	}
}

bool WhirlwindForceGenerator::isInActionZone(Particle* p){
	return p->getPos().x < ACTION_ZONE.x + _center.x
		&& p->getPos().y < ACTION_ZONE.y + _center.y
		&& p->getPos().z < ACTION_ZONE.z + _center.z;
}
