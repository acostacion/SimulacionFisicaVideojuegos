#pragma once
#include "SolidGen.h"
#include "../Render/RenderUtils.hpp"

class SolidSphereGen : public SolidGen {
public:
	SolidSphereGen(physx::PxPhysics* physics, physx::PxScene* scene, physx::PxTransform spawnPos);

	void generateS() override;
};

