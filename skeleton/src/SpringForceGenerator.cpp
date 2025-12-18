#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other)
	: _k(k), _resting_length(resting_length), _otherParticle(other){
}

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, physx::PxRigidActor* other)
	: _k(k), _resting_length(resting_length), _otherSolid(other) {
}

void SpringForceGenerator::updateForce(Particle* p, double t) {

	if (_otherSolid == nullptr) {
		// Particle is the particle to apply the force.
		physx::PxVec3 relative_pos_vector = _otherParticle->getPos() - p->getPos();


		// normalize: Normalize the relative_pos_vector and returns its length.
		const float length = relative_pos_vector.normalize();

		// si se tira del muelle...
		if (length > _resting_length) {
			const float delta_x = length - _resting_length;

			physx::PxVec3 force = relative_pos_vector * delta_x * _k;

			// esto es por lo de que haya varias fuerzas a la vez.
			p->setForce(p->getForce() + force);
		}
	}
}

void SpringForceGenerator::updateForce(physx::PxRigidDynamic* s, double t) {
	if (_otherParticle == nullptr) {
		// Particle is the particle to apply the force.
		physx::PxVec3 relative_pos_vector = _otherSolid->getGlobalPose().p - s->getGlobalPose().p;

		// normalize: Normalize the relative_pos_vector and returns its length.
		const float length = relative_pos_vector.normalize();

		// si se tira del muelle...
		if (length > _resting_length) {
			const float delta_x = length - _resting_length;

			physx::PxVec3 force = relative_pos_vector * delta_x * _k;

			s->addForce(force);
		}
	}
}
