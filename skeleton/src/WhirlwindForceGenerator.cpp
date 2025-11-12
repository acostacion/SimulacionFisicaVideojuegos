#include "WhirlwindForceGenerator.h"

WhirlwindForceGenerator::WhirlwindForceGenerator(physx::PxVec3 speed, double k, physx::PxVec3 center)
	:WindForceGenerator(speed), _center(center), _k(k) {
}

void WhirlwindForceGenerator::updateForce(Particle* p) {
	if (isInActionZone(p)) {
		// distancias del centro a la particula a cada componente.
		float dx = p->getPos().x - _center.x;
		float dy = p->getPos().y - _center.y;
		float dz = p->getPos().z - _center.z;

		// formula velocidad del torbellino del enunciado.
		physx::PxVec3 fuerzaTorbellino = _k * physx::PxVec3(-dz, 50 - dy, dx);

		// se asigna a la velocidad del viento de la clase padre.
		_windSpeed = fuerzaTorbellino;

		// calcula la fuerza del viento.
		WindForceGenerator::updateForce(p);
	}
}

bool WhirlwindForceGenerator::isInActionZone(Particle* p){
	return p->getPos().x < ACTION_ZONE.x + _center.x
		&& p->getPos().y < ACTION_ZONE.y + _center.y
		&& p->getPos().z < ACTION_ZONE.z + _center.z;
}
