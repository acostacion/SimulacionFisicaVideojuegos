#include "Slingshot.h"

Slingshot::Slingshot(physx::PxVec3 pos, double size, Vector4 color) : _tf(new physx::PxTransform(pos)), _size(size), _color(color) { // TODO inicialization order
	physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(_size, _size, _size));
	_renderItem = new RenderItem(shape, _tf, _color);
	RegisterRenderItem(_renderItem);
}

Slingshot::~Slingshot() {
	DeregisterRenderItem(_renderItem);

	delete _renderItem;
	_renderItem = nullptr;

	delete _tf;
	_tf = nullptr;
}
