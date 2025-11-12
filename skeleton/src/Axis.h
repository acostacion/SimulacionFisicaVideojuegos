#pragma once
#include <PxPhysicsAPI.h>
#include "../Render/RenderUtils.hpp"
#include <vector>
#include "../Vector3D.h"

class Axis {
	// TODO cambiar todos los PxVec3 a Vector3D
public:
	Axis();
	virtual ~Axis();
private:
	std::vector<RenderItem*> _renderItems;
	std::vector<physx::PxTransform*> _tfs;
};