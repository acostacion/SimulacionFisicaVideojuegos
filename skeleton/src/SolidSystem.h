#pragma once
#include <PxRigidDynamic.h>
#include "SolidGen.h"
#include <vector>

// nos basamos en la clase particlesystem para crear esta.
class SolidSystem {
public:
	virtual ~SolidSystem();

	// vector de solidgenerators. TODO
	std::vector<SolidGen*> solidGenerators;

	void update(double t);
};

