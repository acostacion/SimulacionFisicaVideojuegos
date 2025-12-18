#include "WhirlwindForceGenerator.h"

WhirlwindForceGenerator::WhirlwindForceGenerator(physx::PxVec3 speed, double k, physx::PxVec3 center)
	:WindForceGenerator(speed), _center(center), _k(k) {
}

void WhirlwindForceGenerator::updateForce(Particle* p, double t) {
	if (isInActionZone(p->getPos())) {
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

void WhirlwindForceGenerator::updateForce(physx::PxRigidDynamic* s, double t) {
	if (isInActionZone(s->getGlobalPose().p)) {
		// distancias del centro a la particula a cada componente.
		physx::PxVec3 d = s->getGlobalPose().p - _center;

		// formula velocidad del torbellino del enunciado.
		physx::PxVec3 fuerzaTorbellino = _k * physx::PxVec3(-d.z, 50 - d.y, d.x);

		// se asigna a la velocidad del viento de la clase padre.
		_windSpeed = fuerzaTorbellino;

		// calcula la fuerza del viento.
		WindForceGenerator::updateForce(s, t);
	}
}

bool WhirlwindForceGenerator::isInActionZone(physx::PxVec3 p) {
	return p.x < ACTION_ZONE.x + _center.x
		&& p.y < ACTION_ZONE.y + _center.y
		&& p.z < ACTION_ZONE.z + _center.z;
}
