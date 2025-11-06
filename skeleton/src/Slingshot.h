#pragma once
#include <PxPhysicsAPI.h>
#include "../Render/RenderUtils.hpp"
#include "../Vector3D.h"

class Slingshot {
	// TODO cambiar todos los PxVec3 a Vector3D
public:
	Slingshot(
		physx::PxVec3 pos,
		double size = 1.0,
		Vector4 color = { 0.55, 0.27, 0.07, 1.0 } // marron
	);

	virtual ~Slingshot();
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