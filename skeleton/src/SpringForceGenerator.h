#pragma once
#include "ForceGenerator.h"
#include "Particle.h"
// TODO cambiar lo de pxvec3
class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double k, double resting_length, Particle* other); // particle
	SpringForceGenerator(double k, double resting_length, physx::PxRigidActor* other); //solid

	~SpringForceGenerator() = default;

	virtual void updateForce(Particle* p, double t) override; // particle 
	virtual void updateForce(physx::PxRigidDynamic* s, double t) override; // solid

	inline void setK(double k) { _k = k; }
	
protected:
	double _k; // Elastic Coeff.
	double _resting_length;

	Particle* _otherParticle = nullptr; // particle
	physx::PxRigidActor* _otherSolid = nullptr; // solid
	// IMPORTANTE RIGIDACTOR ES LA CLASE PADRE DE LA QUE HEREDAN STATIC Y DYNAMIC PARA LO DEDL ANCHOR
};

