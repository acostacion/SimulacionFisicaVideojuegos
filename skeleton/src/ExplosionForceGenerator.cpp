#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator(physx::PxVec3 force, double k, physx::PxVec3 center)
	: _explosionSpeed(force), _k(k), _center(center) {
}

void ExplosionForceGenerator::updateForce(Particle* p) {
	// distancias del centro a la particula a cada componente.
	float dx = p->getPos().x - _center.x;
	float dy = p->getPos().y - _center.y;
	float dz = p->getPos().z - _center.z;

	// distancia a la explosion.
	double r = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));

	//if (esta en el radio)
	//{
	//	// hace cosas
	//}
	//else fuerza 0

	// TODO incompleta
	physx::PxVec3 Fe = physx::PxVec3(
		(_k / pow(r,2)) * dx,
		(_k / pow(r,2)) * dy,
		(_k / pow(r,2)) * dz
	);
}
