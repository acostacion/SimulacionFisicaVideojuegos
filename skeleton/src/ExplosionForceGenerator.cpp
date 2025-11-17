#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator(double k, physx::PxVec3 center, float radius, double t)
	: _K(k), _center(center), _R(radius), _t(t), _isExploding(false) {
}

void ExplosionForceGenerator::updateForce(Particle* p, double t) {
	if (_isExploding) {

		// gestion de tiempo
		_currentTime += t;
		if (_currentTime >= EXPLOSION_DURATION) _isActive = false;

		// distancias del centro a la particula a cada componente.
		physx::PxVec3 d = p->getPos() - _center;

		// distancia a la explosion.
		double r = sqrt(pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2));

		// fuerza de la explosion.
		physx::PxVec3 explosionForce;

		// si esta dentro del radio, la otra comprobacion es pa k no divida por cero
		if (r < _R && r > 0) {
			// formula
			explosionForce = (_K / pow(r, 2)) * physx::PxVec3(d.x, d.y, d.z) * exp(-t / _t);
		}
		else {
			explosionForce = physx::PxVec3(0.0);
		}

		// lo aplica.
		p->setForce(p->getForce() + explosionForce);
	}
}


