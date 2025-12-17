#pragma once
#include "SolidGen.h"
#include "../Render/RenderUtils.hpp"

class SolidBoxGen : public SolidGen {
public:
	SolidBoxGen(physx::PxPhysics* physics, physx::PxScene* scene, physx::PxTransform spawnPos);

	void generateS() override;
};

