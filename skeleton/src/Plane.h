#pragma once
#include <PxPhysicsAPI.h>
#include "../Render/RenderUtils.hpp"
#include "../Vector3D.h"

class Plane {
	// TODO cambiar todos los PxVec3 a Vector3D
public:
	Plane(
		physx::PxVec3 pos,
		double size,
		Vector4 color = { 0.34, 0.49, 0.27, 1.0 } // cesped
	);

	virtual ~Plane();
private:
	RenderItem* _renderItem;

	physx::PxTransform* _tf;  // transform (pos)
	double _size;
	Vector4 _color;

public:
	// getters
	inline RenderItem* getRenderItem() const { return _renderItem; }
	inline physx::PxVec3 getPos() const { return _tf->p; }
	inline double getSize() const { return _size; }
	inline Vector4 getColor() const { return _color; }

	// setters
	inline void setPos(physx::PxVec3 pos) { _tf->p = pos; }
	inline void setSize(double size) { _size = size; }
	inline void setColor(Vector4 color) { _color = color; }
};