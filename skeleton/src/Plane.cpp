#include "Plane.h"

Plane::Plane(physx::PxVec3 pos, double size, physx::PxPhysics* physics, physx::PxScene* scene, Vector4 color)
	: _tf(physx::PxTransform(pos, physx::PxQuat(physx::PxQuat(physx::PxPi/4.5, physx::PxVec3(0, 1, 0))))),
	  _size(size), _pxphysics(physics), _pxscene(scene), _color(color) { // TODO inicialization order

	physx::PxRigidStatic* suelo = _pxphysics->createRigidStatic(_tf);
	physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(_size, 0.25, _size));
	suelo->attachShape(*shape);
	_pxscene->addActor(*suelo);
	_renderItem = new RenderItem(shape, suelo, _color);
	RegisterRenderItem(_renderItem);
}

Plane::~Plane() {
	DeregisterRenderItem(_renderItem);

	delete _renderItem;
	_renderItem = nullptr;
}
