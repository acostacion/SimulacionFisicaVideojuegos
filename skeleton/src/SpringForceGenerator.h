#pragma once
#include "ForceGenerator.h"
#include "Particle.h"
// TODO cambiar lo de pxvec3
class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);
	virtual ~SpringForceGenerator() = default;

	virtual void updateForce(Particle* p, double t) override;

	inline void setK(double k) { _k = k; }
	
protected:
	double _k; // Elastic Coeff.
	double _resting_length;
	Particle* _other;
};

