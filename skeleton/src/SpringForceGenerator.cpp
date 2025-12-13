#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other)
	: _k(k), _resting_length(resting_length), _other(other){
}

void SpringForceGenerator::updateForce(Particle* p, double t) {
	// Particle is the particle to apply the force.
	physx::PxVec3 relative_pos_vector = _other->getPos() - p->getPos();
	physx::PxVec3 force;

	// normalize: Normalize the relative_pos_vector and returns its length.
	const float length = relative_pos_vector.normalize();

	// si se tira del muelle...
	if (length > _resting_length) {
		const float delta_x = length - _resting_length;

		force = relative_pos_vector * delta_x * _k;

		// esto es por lo de que haya varias fuerzas a la vez.
		p->setForce(p->getForce() + force);
	}
}
