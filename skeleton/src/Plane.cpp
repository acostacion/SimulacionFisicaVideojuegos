#include "Plane.h"

Plane::Plane(physx::PxVec3 pos, double size, Vector4 color)
	: _tf(new physx::PxTransform(pos, physx::PxQuat(physx::PxPi / 4.0f, physx::PxVec3(0, 1, 0)))),
	  _size(size), _color(color) { // TODO inicialization order
	physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(_size, 0.25, _size));
	_renderItem = new RenderItem(shape, _tf, _color);
	RegisterRenderItem(_renderItem);
}

Plane::~Plane() {
	DeregisterRenderItem(_renderItem);

	delete _renderItem;
	_renderItem = nullptr;

	delete _tf;
	_tf = nullptr;
}
